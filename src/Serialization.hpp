#pragma once

#undef GetForm
#undef AddForm

namespace Serialization
{
	enum : std::uint32_t
	{
		kHeader = 'COMP',
		kVersion = 1000,
	};

#define DEFAULT_VARIATION_MAX 12
	using FormArray = RE::FormID[];
	using Variation = std::pair<RE::FormID, std::array<RE::FormID, DEFAULT_VARIATION_MAX>>;


	struct CompletionistData
	{
		// modifier

		//-------------------------------------------
		//-------------------------------------------

		[[nodiscard]] static bool IsModInstalled(std::string_view a_modname) noexcept
		{
			auto* handler = RE::TESDataHandler::GetSingleton();
			return
				handler->LookupLoadedModByName(a_modname) != nullptr ||
				handler->LookupLoadedLightModByName(a_modname) != nullptr;
		}

		//-------------------------------------------
		//-------------------------------------------

		[[nodiscard]] void AddForm(RE::TESForm* a_form) noexcept
		{
			if (!a_form || !a_form->GetFormID()) {
				return;
			}

			data.try_emplace(a_form->GetFormID());
		}

		//-------------------------------------------
		//-------------------------------------------

		[[nodiscard]] void AddForm(RE::FormID a_form) noexcept
		{
			if (!a_form) {
				return;
			}

			data.try_emplace(a_form);
		}

		//-------------------------------------------
		//-------------------------------------------

		[[nodiscard]] void AddForm(RE::FormID a_form, std::string_view a_filename) noexcept
		{
			auto* handler = RE::TESDataHandler::GetSingleton();
			if (!handler) {
				return;
			}

			auto form = handler->LookupFormID(a_form, a_filename);
			data.try_emplace(form);
		}

		//-------------------------------------------
		//-------------------------------------------

		[[nodiscard]] void AddForm(RE::FormID a_base, std::string_view a_filename, RE::FormID a_variation) noexcept
		{
			auto* handler = RE::TESDataHandler::GetSingleton();
			if (!handler) {
				return;
			}

			auto base = handler->LookupFormID(a_base, a_filename);
			auto variation = handler->LookupFormID(a_variation, a_filename);

			if (!base || !variation || (HasForm(base) && HasForm(variation))) {
				return;
			}
			else {
				data.try_emplace(base);
				data.try_emplace(variation, base);
			}
		}

		//-------------------------------------------
		//-------------------------------------------

		[[nodiscard]] void AddForm(RE::FormID a_base, std::string_view a_basefilename, RE::FormID a_variation, std::string a_modfilename) noexcept
		{
			auto* handler = RE::TESDataHandler::GetSingleton();
			if (!handler) {
				return;
			}

			auto base = handler->LookupFormID(a_base, a_basefilename);
			auto variation = handler->LookupFormID(a_variation, a_modfilename);

			if (!base || !variation || (HasForm(base) && HasForm(variation))) {
				return;
			}
			else {
				data.try_emplace(base);
				data.try_emplace(variation, base);
			}
		}

		//-------------------------------------------
		//-------------------------------------------

		[[nodiscard]] void RemoveForm(RE::FormID a_form) noexcept
		{
			if (!HasForm(a_form)) {
				return;
			}

			data.erase(a_form);
		}

		//-------------------------------------------
		//-------------------------------------------

		[[nodiscard]] bool HasForm(RE::FormID a_form) const noexcept
		{
			return data.contains(a_form);
		}

		//-------------------------------------------
		//-------------------------------------------

		[[nodiscard]] RE::TESForm* GetForm(RE::FormID a_form) noexcept
		{
			return HasForm(a_form) ? RE::TESForm::LookupByID(a_form) : nullptr;
		}

		//-------------------------------------------
		//-------------------------------------------

		template <typename T>
		[[nodiscard]] T* GetForm(RE::FormID a_form) noexcept
		{
			auto* form = GetForm(a_form);
			return form ? static_cast<T*>(form) : nullptr;
		}

		[[nodiscard]] RE::FormID GetBase(RE::FormID a_variation) const noexcept
		{	// get base form that it's variation of, return 0 if not variation
			return HasForm(a_variation) ? data.at(a_variation) : 0;
		}

		[[nodiscard]] bool IsVariation(RE::FormID a_form) const noexcept
		{
			return GetBase(a_form);
		}

		[[nodiscard]] std::string_view GetFileName(RE::FormID a_form) noexcept
		{
			return HasForm(a_form) ? GetForm(a_form)->GetFile()->GetFilename() : "";
		}

		[[nodiscard]] auto GetAllForms() noexcept
		{
			return std::views::keys(data);
		}

		[[nodiscard]] auto GetAllBases() noexcept
		{
			return std::views::keys(data) | std::views::filter([&](auto f) { return !IsVariation(f); });
		}

		[[nodiscard]] auto GetAllVariations() noexcept
		{
			return std::views::keys(data) | std::views::filter([&](auto f) { return IsVariation(f); });
		}

		[[nodiscard]] constexpr auto& get() noexcept { return data; }

		// generator
		template <std::size_t N>
		void CompileFormArray(const RE::FormID(&a_array)[N], std::string_view a_filename) noexcept
		{
			auto* handler = RE::TESDataHandler::GetSingleton();
			if (!handler) {
				ERROR("Failed to obtain TESDataHandler*, maybe too early?");
			}

			for (auto idx = 0; idx < N; ++idx) {
				auto form = handler->LookupFormID(a_array[idx], a_filename);
				if (!form) {
					continue;
				}
				data.try_emplace(form);
			}
		}

		template <std::size_t N>
		void CompileVariation(const Variation(&a_variation)[N], std::string_view a_filename) noexcept
		{
			auto* handler = RE::TESDataHandler::GetSingleton();
			if (!handler) {
				ERROR("Failed to obtain TESDataHandler*, maybe too early?");
			}

			for (auto idx = 0; idx < N; ++idx) {
				if (a_variation[idx].second.empty()) {
					continue;
				}

				auto baseID = handler->LookupFormID(a_variation[idx].first, a_filename);
				if (!baseID) {
					continue;
				}

				data.try_emplace(baseID);
				for (auto var : a_variation[idx].second) {
					if (var) {
						auto varID = handler->LookupFormID(var, a_filename);
						data.try_emplace(varID, baseID);
					}
					else {
						break;
					}
				}
			}
		}

		// API
		void Save([[maybe_unused]] SKSE::SerializationInterface* a_intfc) noexcept
		{
			std::size_t total = data.size();
			if (!a_intfc->WriteRecordData(&total, sizeof(total))) {
				ERROR("Failed to write serialized data");
			}

			for (auto& m : data) {
				if (!a_intfc->WriteRecordData(&m, sizeof(m))) {
					ERROR("Failed to write serialized data");
				}
			}

			INFO("...Saved skse file, size: {}", total);
		}

		void Load([[maybe_unused]] SKSE::SerializationInterface* a_intfc) noexcept
		{
			std::size_t total;
			if (!a_intfc->ReadRecordData(&total, sizeof(total))) {
				ERROR("Failed to read serialized data");
			}

			for (auto i : std::views::iota(static_cast<std::size_t>(0), total)) {
				RE::FormID form, base;
				if (!a_intfc->ReadRecordData(&form, sizeof(form))) {
					continue;
				}

				if (!form || !a_intfc->ResolveFormID(form, form)) {
					continue;
				}

				if (!a_intfc->ReadRecordData(&base, sizeof(base))) {
					continue;
				}

				if (base && !a_intfc->ResolveFormID(base, base)) {
					continue;
				}

				data.try_emplace(form, base);
			}

			INFO("...Loaded skse file, size: {}", data.size());
		}

		void Revert([[maybe_unused]] SKSE::SerializationInterface* a_intfc) noexcept
		{
			INFO("Swapping skse files...");
			data.clear();
		}

		static RE::ExtraMapMarker* GetMapMarkerInternal(RE::TESObjectREFR* ref)
		{
			if (!ref) { return nullptr; }
			if (!ref->extraList.HasType<RE::ExtraMapMarker>()) { return nullptr; }

			return ref->extraList.GetByType<RE::ExtraMapMarker>();
		}

		void SetAsSerializable() noexcept
		{
			CompletionistData::ManagedData.emplace_back(this);
		}

		void MergeAsCollectable() noexcept
		{
			CompletionistData::NewItemData.emplace_back(this);
		}

		static bool CheckIsCollectable(RE::TESForm* a_form) noexcept
		{
			return a_form ? CheckIsCollectable(a_form->GetFormID()) : false;
		}

		static bool CheckIsCollectable(RE::FormID a_form) noexcept
		{
			for (auto* data : CompletionistData::NewItemData) {
				if (data && data->HasForm(a_form)) {
					return true;
				}
			}
			return false;
		}

		void Populate(std::vector<std::string>& a_names, std::vector<RE::TESForm*>& a_forms, std::vector<bool>& a_bools, std::vector<std::string>& a_texts, bool a_isMarker = false, bool a_nosort = false)
		{
			a_names.clear();
			a_forms.clear();
			a_bools.clear();
			a_texts.clear();
			
			// zip for parallel sorting by name, alphabetical
			using zipped_t = std::pair<std::string, std::pair<RE::TESForm*, bool>>;
			// construct zip view from formID;
			auto bases = GetAllBases() |
				std::views::filter([&](auto f) { return GetForm(f) && GetForm(f)->GetName(); }) |
				std::views::transform([&](auto f) {
				std::string name = GetForm(f)->GetName();

				if (auto marker = GetForm<RE::TESObjectREFR>(f); marker && a_isMarker) {
					if (auto extraMapMarker = GetMapMarkerInternal(GetForm<RE::TESObjectREFR>(f)); extraMapMarker && extraMapMarker->mapData) {
						name = extraMapMarker->mapData->locationName.fullName.c_str();
					}
				}

				name[0] = std::toupper(name[0]);  // in case some mod forms have lower case name
				return std::make_pair(std::move(name), std::make_pair(GetForm(f), false));
					});

			// instantiate the zipped view for sorting
			std::vector<zipped_t> zipped = { std::ranges::begin(bases), std::ranges::end(bases) };
			if (!a_nosort) {
				std::ranges::sort(zipped);
			}

			// unzip
			for (auto& [name, data] : zipped) {
				auto& [form, status] = data;
				a_names.emplace_back(name);
				a_forms.emplace_back(form);
				a_bools.emplace_back(status);
			}

			// assertions can be removed
			assert(a_names.size() == zipped.size());
			assert(a_names.size() == a_forms.size());
			assert(a_bools.size() == a_forms.size());

			a_texts = std::vector<std::string>(a_names.size(), "NO_HIGHLIGHT");
		}

		// members
		std::unordered_map<RE::FormID, RE::FormID> data;
		inline static std::vector<CompletionistData*> ManagedData = {};
		inline static std::vector<CompletionistData*> NewItemData = {};
	};

	static void SaveCallback([[maybe_unused]] SKSE::SerializationInterface* a_intfc) noexcept
	{
		if (!a_intfc->OpenRecord(kHeader, kVersion)) {
			ERROR("Failed to open record");
		}

		for (auto* data : CompletionistData::ManagedData) {
			if (data) {
				data->Save(a_intfc);
			}
		}
	}

	static void LoadCallback([[maybe_unused]] SKSE::SerializationInterface* a_intfc) noexcept
	{
		std::uint32_t type, version, length;
		while (a_intfc->GetNextRecordInfo(type, version, length)) {
			if (type != kHeader || version > kVersion) {
				break;
			}

			if (version < kVersion) {
				// if somehow the serialized data structure changed, thus resulting a kVersion change
				// it must be able to patch/regress the backward compatibility or it will ERROR
			}

			for (auto* data : CompletionistData::ManagedData) {
				if (data) {
					data->Load(a_intfc);
				}
			}
		}
	}

	static void RevertCallback([[maybe_unused]] SKSE::SerializationInterface* a_intfc) noexcept
	{
		for (auto* data : CompletionistData::ManagedData) {
			if (data) {
				data->Revert(a_intfc);
			}
		}
	}
}

namespace FrameworkHandler
{
	using namespace Serialization;

	enum class FrameworkID
	{
		kArmor = 0,
		kJewelry = 1,
		kDragonClaws_V = 2,
		kDragonClaws_P = 3,
		kLiquor = 4,
		kDragonMasks_V = 5,
		kDragonMasks_P = 6,
		kWeapons = 7,
		kItems = 8,

		kBooks_AG = 10,
		kBooks_HS = 11,
		kBooks_TY = 12,
		kBooks_SB = 13,
		kBooks_ST = 14,

		kBooks_DG = 15,
		kBooks_DGS = 16,

		kBooks_DB = 17,
		kBooks_DBS = 18,

		kLocations_DG = 20,
		kLocations_DB = 21,
		kLocations_AG = 23,
		kLocations_HR = 24,
		kLocations_SZ = 25,

		kDoomstones = 26,
		kShrines_V = 27,
		kShrines_P = 28,
		kBarenziah = 29,

		kAEnchantments_V = 30,
		kAEnchantments_P = 31,
		kWEnchantments_V = 32,
		kWEnchantments_P = 33,

		kFishing_I = 50,
		kFishing_B = 51,
		kFishing_A = 52,
		kFishing_C = 53,
		kFishing_L = 54,
		kFishing_S = 55,

		kCreationClub_L = 90,
		kCreationClub_B = 91,
		kCreationClub_S = 92,
		kCreationClub_A = 93,
		kCreationClub_W = 94,
		kCreationClub_I = 95,

		// leave this one at end
		kTotal,
	};

	static std::unordered_map<FrameworkID, std::vector<std::string>*> NameSet;
	static std::unordered_map<FrameworkID, std::vector<std::string>*> TextSet;
	static std::unordered_map<FrameworkID, std::vector<bool>*> BoolSet;

	static std::unordered_map<FrameworkID, std::vector<RE::TESForm*>*> FormSet;
	static std::unordered_map<FrameworkID, std::vector<uint32_t>*> FoundSet;
	static std::unordered_map<FrameworkID, std::vector<uint32_t>*> TotalSet;
	static std::unordered_map<FrameworkID, std::vector<CompletionistData>*> CDataSet;

	static auto& HandleNameSet(FrameworkID a_cat) noexcept
	{
		return *NameSet.at(a_cat);
	}

	static auto& HandleTextSet(FrameworkID a_cat) noexcept
	{
		return *TextSet.at(a_cat);
	}

	static auto& HandleBoolSet(FrameworkID a_cat) noexcept
	{
		return *BoolSet.at(a_cat);
	}

	static auto& HandleFormSet(FrameworkID a_cat) noexcept
	{
		return *FormSet.at(a_cat);
	}

	static auto& HandleFoundSet(FrameworkID a_cat) noexcept
	{
		return *FoundSet.at(a_cat);
	}

	static auto& HandleTotalSet(FrameworkID a_cat) noexcept
	{
		return *TotalSet.at(a_cat);
	}

	static auto& HandleDataSet(FrameworkID a_cat) noexcept
	{
		return *CDataSet.at(a_cat);
	}

	template <FrameworkID a_id>
	static void RegisterAs(std::vector<std::string>* a_names, std::vector<RE::TESForm*>* a_forms, std::vector<bool>* a_bools, std::vector<std::string>* a_texts) noexcept
		requires(a_id != FrameworkID::kTotal) // so no overflow/out of bound access
	{
		NameSet.try_emplace(a_id, a_names);
		FormSet.try_emplace(a_id, a_forms);
		BoolSet.try_emplace(a_id, a_bools);
		TextSet.try_emplace(a_id, a_texts);

	}
} // namespace FrameworkHandler


//static void RegisterAs(std::vector<std::string>* a_names, std::vector<RE::TESForm*>* a_forms, std::vector<bool>* a_bools, std::vector<std::string>* a_texts, uint32_t* a_found, uint32_t* a_total, CompletionistData* a_data) noexcept