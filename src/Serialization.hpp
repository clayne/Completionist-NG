
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
		[[nodiscard]] void AddForm(RE::TESForm* a_form) noexcept
		{
			if (!a_form || !a_form->GetFormID()) {
				return;
			}

			data.try_emplace(a_form->GetFormID());
		}
		[[nodiscard]] void AddForm(RE::FormID a_form) noexcept
		{
			if (!a_form) {
				return;
			}

			data.try_emplace(a_form);
		}
		[[nodiscard]] void AddForm(RE::FormID a_form, std::string_view a_filename) noexcept
		{
			auto* handler = RE::TESDataHandler::GetSingleton();
			if (!handler) {
				return;
			}

			auto form = handler->LookupFormID(a_form, a_filename);
			data.try_emplace(form);
		}
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
		[[nodiscard]] void RemoveForm(RE::FormID a_form) noexcept
		{
			if (!HasForm(a_form)) {
				return;
			}

			data.erase(a_form);
		}

		// accessor
		[[nodiscard]] bool HasForm(RE::FormID a_form) const noexcept
		{
			return data.contains(a_form);
		}

		[[nodiscard]] RE::TESForm* GetForm(RE::FormID a_form) noexcept
		{
			return HasForm(a_form) ? RE::TESForm::LookupByID(a_form) : nullptr;
		}

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

		void Populate(std::vector<std::string>& a_names, std::vector<RE::TESForm*>& a_forms, std::vector<bool>& a_bools, bool a_isMarker = false)
		{
			a_names.clear();
			a_forms.clear();
			a_bools.clear();

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
						INFO("{} is a MapMarker", name);
					}
				}

				name[0] = std::toupper(name[0]);  // in case some mod forms have lower case name
				return std::make_pair(std::move(name), std::make_pair(GetForm(f), false));
					});

			// instantiate the zipped view for sorting
			std::vector<zipped_t> zipped = { std::ranges::begin(bases), std::ranges::end(bases) };
			std::ranges::sort(zipped);  // why can't we just sort views directly lol

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