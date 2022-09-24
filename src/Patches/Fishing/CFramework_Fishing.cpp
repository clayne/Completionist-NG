#include "Serialization.hpp"
#include "CFramework_Fishing.hpp"
#include "Frameworks/FrameworkMaster.hpp"
#include "Internal Utility/ScriptObject.hpp"

#undef AddForm

namespace CPatchManager_Fishing {

	RE::Actor* Player;

	const char* pname = "ccbgssse001-fish.esm";

	void CHandler::InstallFramework() {
		
		if (const auto* Mod = RE::TESDataHandler::GetSingleton()->LookupLoadedModByName(pname); !Mod) {
			if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_FishingEnabled"); global) {
				global->value = 0;
			}
			return;
		}

		Player = static_cast<RE::Actor*>(RE::TESForm::LookupByID(0x00000014));
		CPatch_FishingItems::CHandler::InstallFramework();
		CPatch_FishingBooks::BHandler::InstallFramework();
		CPatch_FishingSpots_A::CHandler::InstallFramework();
		CPatch_FishingSpots_C::CHandler::InstallFramework();
		CPatch_FishingSpots_L::CHandler::InstallFramework();
		CPatch_FishingSpots_S::CHandler::InstallFramework();
	}

	void CHandler::UpdateFoundForms() {

		if (const auto* Mod = RE::TESDataHandler::GetSingleton()->LookupLoadedModByName(pname); !Mod) {
			if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_FishingEnabled"); global) {
				global->value = 0;
			}
			return;
		}

		Player = static_cast<RE::Actor*>(RE::TESForm::LookupByID(0x00000014));
		CPatch_FishingItems::CHandler::UpdateFoundForms();
		CPatch_FishingBooks::BHandler::UpdateFoundForms();
		CPatch_FishingSpots_A::CHandler::UpdateFoundForms();
		CPatch_FishingSpots_C::CHandler::UpdateFoundForms();
		CPatch_FishingSpots_L::CHandler::UpdateFoundForms();
		CPatch_FishingSpots_S::CHandler::UpdateFoundForms();
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Items
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingItems {

	using namespace CFramework_Master;

	// clang-format off
	constexpr Serialization::FormArray FishingForms = {
	0x000ED3,0x000A6F,0x000C66,0x000B2B,0x000B29,0x000B94,0x0EA5CC,
	0x0008E3,0x000BC0,0x000BA0,0x000C07,0x000F07,0x000B2A,
	};

	constexpr Serialization::Variation FishingVariations[] = {
	{ 0x07AED6, { 0x0009D9,0x04D05E } },
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	uint32_t EntriesFound;
	uint32_t EntriesTotal;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		CHandler::RegisterEvents();
		CHandler::InjectAndCompileData();
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CPatch_FishingItems::FishingForms, CPatchManager_Fishing::pname);
		Data.CompileVariation(CPatch_FishingItems::FishingVariations, CPatchManager_Fishing::pname);
		Data.MergeAsCollectable();

		CPatch_FishingItems::Data.Populate(NameArray, FormArray, BoolArray, TextArray);
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Events ( On Item Added ) -------------
	//---------------------------------------------------

	EventResult CHandler::ProcessEvent(const RE::TESContainerChangedEvent* a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*) {

		if (!a_event || a_event->newContainer != 0x00014 || !Data.HasForm(a_event->baseObj)) { return EventResult::kContinue; }

		auto base = Data.GetBase(a_event->baseObj) ? Data.GetBase(a_event->baseObj) : a_event->baseObj;
		CHandler::ProcessFoundForm(base, a_event->baseObj);
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Process Found Form ) -----
	//---------------------------------------------------

	void CHandler::ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID) {

		if (!FoundItemData.HasForm(a_eventID)) {
			auto msg = fmt::format("Completionist: {:s} Acquired!"sv, Data.GetForm(a_eventID)->GetName());
			CHandler::SendNotification(msg);
		}

		FoundItemData.AddForm(a_baseID);
		for (auto var : Data.GetAllVariations()) {
			if (Data.GetBase(var) == a_baseID) {
				FoundItemData.AddForm(var);
			}
		}

		auto t_pos = std::find(FormArray.begin(), FormArray.end(), Data.GetForm(a_baseID));
		auto b_pos = std::distance(FormArray.begin(), t_pos);
		BoolArray[b_pos] = true;

		EntriesFound = std::ranges::count(BoolArray, true);
		INFO("FOUND ITEMS LIST = {}", FoundItemData.data.size());
	}

	//---------------------------------------------------
	//-- Framework Functions ( Send Notification ) ------
	//---------------------------------------------------

	void CHandler::SendNotification(std::string a_msg) {

		if (!MCMScript->GetProperty("NotifyItems")->GetBool()) { return; }

		auto message = fmt::format("<font color='{:s}'>{:s}</font>"sv, MCMScript->GetProperty("ColourString")->GetString(), a_msg);
		if (!MCMScript->GetProperty("NotificationColourEnabled")->GetBool()) { RE::DebugNotification(a_msg.c_str()); return; }
		RE::DebugNotification(message.c_str());
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (FoundItemData.HasForm(FormArray[i]->GetFormID())) {
				BoolArray[i] = true;
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM is Entry Complete ) --
	//---------------------------------------------------

	uint32_t CHandler::IsOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			return uint32_t(BoolArray[std::distance(NameArray.begin(), t_pos)]);
		}
		return -1;
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Set Entry Complete ) -
	//---------------------------------------------------

	void CHandler::SetOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			auto b_pos = std::distance(NameArray.begin(), t_pos);

			if (BoolArray.at(b_pos)) {
				BoolArray.at(b_pos) = false;

				FoundItemData.RemoveForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.RemoveForm(var);
					}
				}
			}
			else {
				BoolArray.at(b_pos) = true;
				FoundItemData.AddForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.AddForm(var);
					}
				}
			}

			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Books
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingBooks {

	using namespace CFramework_Master;

	// clang-format off

	constexpr Serialization::FormArray FishingForms = {
	0x000E7F,0x0009AE,0x0009AF,0x000ABA,0x000ABC,0x070CCC,0x070CCD,
	0x070CCE,0x070CCF,0x070CD0,0x070CD1,0x070CD2,0x070CD3,0x070CD4,
	0x070CD5,0x0008E5,
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	inline uint32_t EntriesTotal;
	inline uint32_t EntriesFound;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void BHandler::InstallFramework() {

		BHandler::Sink();
		MHandler::Sink();

		BHandler::InjectAndCompileData();
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Singleton ) ----------
	//---------------------------------------------------

	auto BHandler::GetSingleton() -> BHandler* {
		static BHandler singleton;
		return std::addressof(singleton);
	}

	auto MHandler::GetSingleton() -> MHandler* {
		static MHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void BHandler::Sink() {
		RE::BooksRead::GetEventSource()->AddEventSink(BHandler::GetSingleton());
	}

	void MHandler::Sink() {
		auto UserInterface = RE::UI::GetSingleton();
		UserInterface->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(MHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Item Added ) -------------
	//---------------------------------------------------

	auto BHandler::ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event == nullptr || !Data.HasForm(a_event->book->GetFormID())) { return RE::BSEventNotifyControl::kContinue; }

		auto base = Data.GetBase(a_event->book->GetFormID()) ? Data.GetBase(a_event->book->GetFormID()) : a_event->book->GetFormID();
		BHandler::ProcessFoundForm(base, a_event->book->GetFormID(), false);
		return EventResult::kContinue;
	}

	auto MHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (!a_event) { return RE::BSEventNotifyControl::kContinue; }

		if (a_event->menuName == RE::BookMenu::MENU_NAME && a_event->opening && Data.HasForm(RE::BookMenu::GetTargetForm()->GetFormID())) {
			if (auto target = RE::BookMenu::GetTargetForm()->GetFormID(); target) {
				auto base = Data.GetBase(target) ? Data.GetBase(target) : target;
				BHandler::ProcessFoundForm(base, target, false);
				return EventResult::kContinue;
			}
			return EventResult::kContinue;
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Process Map Marker ) -----
	//---------------------------------------------------

	void BHandler::ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress) {

		if (!FoundItemData.HasForm(a_eventID) && !a_supress) {
			auto msg = fmt::format("Completionist: Entry Complete - {:s}!"sv, Data.GetForm(a_eventID)->GetName());
			BHandler::SendNotification(msg);
		}

		FoundItemData.AddForm(a_baseID);
		for (auto var : Data.GetAllVariations()) {
			if (Data.GetBase(var) == a_baseID) {
				FoundItemData.AddForm(var);
			}
		}

		auto t_pos = std::find(FormArray.begin(), FormArray.end(), Data.GetForm(a_baseID));
		auto b_pos = std::distance(FormArray.begin(), t_pos);
		BoolArray.at(b_pos) = true;

		EntriesFound = std::ranges::count(BoolArray, true);
		INFO("FOUND ITEMS LIST = {}", FoundItemData.data.size());
	}

	//---------------------------------------------------
	//-- Framework Functions ( Send Notification ) ------
	//---------------------------------------------------

	void BHandler::SendNotification(std::string a_msg) {

		if (!MCMScript->GetProperty("NotifyItems")->GetBool()) { return; }

		auto message = fmt::format("<font color='{:s}'>{:s}</font>"sv, MCMScript->GetProperty("ColourString")->GetString(), a_msg);
		if (!MCMScript->GetProperty("NotificationColourEnabled")->GetBool()) { RE::DebugNotification(a_msg.c_str()); return; }
		RE::DebugNotification(message.c_str());
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void BHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");
		Data.CompileFormArray(CPatch_FishingBooks::FishingForms, CPatchManager_Fishing::pname);
		Data.MergeAsCollectable();

		CPatch_FishingBooks::Data.Populate(NameArray, FormArray, BoolArray, TextArray);
		for (auto i = 0; i < FormArray.size(); i++) {
			if (FormArray[i]) {
				auto* book = static_cast<RE::TESObjectBOOK*>(FormArray[i]);
				if (book->GetSpell()) {
					TextArray[i] = "$AddSpellTomeHighlight{" + NameArray[i] + "}{" + book->GetSpell()->GetName() + "}";
				}
				else if (book->TeachesSkill()) {
					TextArray[i] = "$AddSkillBookHighlight{" + NameArray[i] + "}{" + CFramework_Master::FrameworkAPI::GetBookSkill(book->GetSkill()) + "}";
				}
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void BHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (auto* book = static_cast<RE::TESObjectBOOK*>(FormArray[i]); book) {
				if (book->IsRead() || (book->GetSpell() && CPatchManager_Fishing::Player->HasSpell(book->GetSpell())) || FoundItemData.HasForm(book->GetFormID())) {
					auto base = Data.GetBase(book->GetFormID()) ? Data.GetBase(book->GetFormID()) : book->GetFormID();
					BHandler::ProcessFoundForm(base, FormArray[i]->GetFormID(), true);
				}
			}
		}

		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM is Entry Complete ) --
	//---------------------------------------------------

	uint32_t BHandler::IsOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			return uint32_t(BoolArray[std::distance(NameArray.begin(), t_pos)]);
		}
		return -1;
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Set Entry Complete ) -
	//---------------------------------------------------

	void BHandler::SetOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			auto b_pos = std::distance(NameArray.begin(), t_pos);

			if (BoolArray.at(b_pos)) {
				BoolArray.at(b_pos) = false;

				FoundItemData.RemoveForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.RemoveForm(var);
					}
				}
			}
			else {
				BoolArray.at(b_pos) = true;
				FoundItemData.AddForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.AddForm(var);
					}
				}
			}

			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Locations - Arctic
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingSpots_A {

	using namespace CFramework_Master;

	// clang-format off

	constexpr Serialization::FormArray MapMarkers = {
	0x000956,0x00093C,0x000964,0x000951,0x00095A,0x000961,0x00095F,0x000962,
	0x000963,0x000959,0x000958,0x000965,0x000950,0x000957,0x000966,0x00095B,
	0x000953,0x000967,0x000955,0x000954,0x000952,
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	inline uint32_t EntriesTotal;
	inline uint32_t EntriesFound;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		CHandler::Sink();
		CHandler::InjectAndCompileData();
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Singleton ) ----------
	//---------------------------------------------------

	auto CHandler::GetSingleton() -> CHandler* {
		static CHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void CHandler::Sink() {
		auto ui = RE::UI::GetSingleton();
		ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(CHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Item Added ) -------------
	//---------------------------------------------------

	auto CHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event->menuName == RE::MapMenu::MENU_NAME && a_event->opening) {

			for (auto i = 0; i < FormArray.size(); i++) {
				CHandler::ProcessMapMarker(FormArray[i], i);
			}
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Process Map Marker ) -----
	//---------------------------------------------------

	void CHandler::ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos) {

		auto* a_marker = static_cast<RE::TESObjectREFR*>(a_form);

		if (a_marker) {
			if (auto extraMapMarker = Serialization::CompletionistData::GetMapMarkerInternal(a_marker); extraMapMarker && extraMapMarker->mapData) {
				if (extraMapMarker->mapData->flags.any(RE::MapMarkerData::Flag::kVisible) && !a_marker->IsDisabled()) {
					BoolArray[a_pos] = true;
					FoundItemData.AddForm(a_marker);
				}
			}
		}

		EntriesFound = std::ranges::count(BoolArray, true);
		INFO("FOUND ITEMS LIST = {}", FoundItemData.data.size());
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CPatch_FishingSpots_A::MapMarkers, "Completionist_ITP.esp");
		CPatch_FishingSpots_A::Data.Populate(NameArray, FormArray, BoolArray, TextArray, true);

		for (auto& name : NameArray) {
			TextArray.push_back("$AddLocationHighlight{" + name + "}");
		}

		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (FoundItemData.HasForm(FormArray[i]->GetFormID())) {
				BoolArray[i] = true;
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Locations - Caves
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingSpots_C {

	using namespace CFramework_Master;

	// clang-format off

	constexpr Serialization::FormArray MapMarkers = {
	0x00095E,0x000960,
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	inline uint32_t EntriesTotal;
	inline uint32_t EntriesFound;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		CHandler::Sink();
		CHandler::InjectAndCompileData();
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Singleton ) ----------
	//---------------------------------------------------

	auto CHandler::GetSingleton() -> CHandler* {
		static CHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void CHandler::Sink() {
		auto ui = RE::UI::GetSingleton();
		ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(CHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Item Added ) -------------
	//---------------------------------------------------

	auto CHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event->menuName == RE::MapMenu::MENU_NAME && a_event->opening) {

			for (auto i = 0; i < FormArray.size(); i++) {
				CHandler::ProcessMapMarker(FormArray[i], i);
			}
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Process Map Marker ) -----
	//---------------------------------------------------

	void CHandler::ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos) {

		auto* a_marker = static_cast<RE::TESObjectREFR*>(a_form);

		if (a_marker) {
			if (auto extraMapMarker = Serialization::CompletionistData::GetMapMarkerInternal(a_marker); extraMapMarker && extraMapMarker->mapData) {
				if (extraMapMarker->mapData->flags.any(RE::MapMarkerData::Flag::kVisible) && !a_marker->IsDisabled()) {
					BoolArray[a_pos] = true;
					FoundItemData.AddForm(a_marker);
				}
			}
		}

		EntriesFound = std::ranges::count(BoolArray, true);
		INFO("FOUND ITEMS LIST = {}", FoundItemData.data.size());
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CPatch_FishingSpots_C::MapMarkers, "Completionist_ITP.esp");
		CPatch_FishingSpots_C::Data.Populate(NameArray, FormArray, BoolArray, TextArray, true);

		for (auto& name : NameArray) {
			TextArray.push_back("$AddLocationHighlight{" + name + "}");
		}

		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (FoundItemData.HasForm(FormArray[i]->GetFormID())) {
				BoolArray[i] = true;
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Locations - Lakes
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingSpots_L {

	using namespace CFramework_Master;

	// clang-format off

	constexpr Serialization::FormArray MapMarkers = {
	0x000932,0x000937,0x00092F,0x000936,0x000939,0x000935,0x000930,0x000931,
	0x000938,0x000933,
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	inline uint32_t EntriesTotal;
	inline uint32_t EntriesFound;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		CHandler::Sink();
		CHandler::InjectAndCompileData();
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Singleton ) ----------
	//---------------------------------------------------

	auto CHandler::GetSingleton() -> CHandler* {
		static CHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void CHandler::Sink() {
		auto ui = RE::UI::GetSingleton();
		ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(CHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Item Added ) -------------
	//---------------------------------------------------

	auto CHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event->menuName == RE::MapMenu::MENU_NAME && a_event->opening) {

			for (auto i = 0; i < FormArray.size(); i++) {
				CHandler::ProcessMapMarker(FormArray[i], i);
			}
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Process Map Marker ) -----
	//---------------------------------------------------

	void CHandler::ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos) {

		auto* a_marker = static_cast<RE::TESObjectREFR*>(a_form);

		if (a_marker) {
			if (auto extraMapMarker = Serialization::CompletionistData::GetMapMarkerInternal(a_marker); extraMapMarker && extraMapMarker->mapData) {
				if (extraMapMarker->mapData->flags.any(RE::MapMarkerData::Flag::kVisible) && !a_marker->IsDisabled()) {
					BoolArray[a_pos] = true;
					FoundItemData.AddForm(a_marker);
				}
			}
		}

		EntriesFound = std::ranges::count(BoolArray, true);
		INFO("FOUND ITEMS LIST = {}", FoundItemData.data.size());
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CPatch_FishingSpots_L::MapMarkers, "Completionist_ITP.esp");
		CPatch_FishingSpots_L::Data.Populate(NameArray, FormArray, BoolArray, TextArray, true);

		for (auto& name : NameArray) {
			TextArray.push_back("$AddLocationHighlight{" + name + "}");
		}

		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (FoundItemData.HasForm(FormArray[i]->GetFormID())) {
				BoolArray[i] = true;
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Locations - Streams
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingSpots_S {

	using namespace CFramework_Master;

	// clang-format off

	constexpr Serialization::FormArray MapMarkers = {
	0x000934,0x000945,0x00094C,0x000944,0x000948,0x000943,0x00094A,0x00093A,
	0x00093E,0x00094F,0x000941,0x00093F,0x000946,0x00095D,0x000949,0x000940,
	0x00093D,0x00093B,0x00095C,0x00094E,0x00094D,0x000942,0x00094B,0x000947,
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	inline uint32_t EntriesTotal;
	inline uint32_t EntriesFound;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		CHandler::Sink();
		CHandler::InjectAndCompileData();
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Singleton ) ----------
	//---------------------------------------------------

	auto CHandler::GetSingleton() -> CHandler* {
		static CHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void CHandler::Sink() {
		auto ui = RE::UI::GetSingleton();
		ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(CHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Item Added ) -------------
	//---------------------------------------------------

	auto CHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event->menuName == RE::MapMenu::MENU_NAME && a_event->opening) {

			for (auto i = 0; i < FormArray.size(); i++) {
				CHandler::ProcessMapMarker(FormArray[i], i);
			}
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Process Map Marker ) -----
	//---------------------------------------------------

	void CHandler::ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos) {

		auto* a_marker = static_cast<RE::TESObjectREFR*>(a_form);

		if (a_marker) {
			if (auto extraMapMarker = Serialization::CompletionistData::GetMapMarkerInternal(a_marker); extraMapMarker && extraMapMarker->mapData) {
				if (extraMapMarker->mapData->flags.any(RE::MapMarkerData::Flag::kVisible) && !a_marker->IsDisabled()) {
					BoolArray[a_pos] = true;
					FoundItemData.AddForm(a_marker);
				}
			}
		}

		EntriesFound = std::ranges::count(BoolArray, true);
		INFO("FOUND ITEMS LIST = {}", FoundItemData.data.size());
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CPatch_FishingSpots_S::MapMarkers, "Completionist_ITP.esp");
		CPatch_FishingSpots_S::Data.Populate(NameArray, FormArray, BoolArray, TextArray, true);

		for (auto& name : NameArray) {
			TextArray.push_back("$AddLocationHighlight{" + name + "}");
		}

		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (FoundItemData.HasForm(FormArray[i]->GetFormID())) {
				BoolArray[i] = true;
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}
}