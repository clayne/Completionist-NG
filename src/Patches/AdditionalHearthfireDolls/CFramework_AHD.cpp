#include "Serialization.hpp"
#include "CFramework_AHD.hpp"
#include "Patches/PatchMaster.hpp"
#include "Frameworks/FrameworkMaster.hpp"
#include "Internal Utility/ScriptObject.hpp"

#undef AddForm

namespace CPatch_AHD_Items {
	Serialization::CompletionistData Data;
}

namespace CPatch_AHD_Books {
	Serialization::CompletionistData Data;
}

namespace CPatch_AHD_MapMa {
	Serialization::CompletionistData Data;
}

namespace CPatch_AHD {

	using namespace CFramework_Master;
	using namespace CPatch_Master;

	// clang-format off

	constexpr Serialization::FormArray Items = {
	0x000814,0x000809,0x000D62,0x000D6A,0x000D63,0x00081D,0x00080A,0x000D64,
	0x000815,0x000816,0x000817,0x000818,0x00080B,0x00081E,0x000819,0x00081A,
	0x00083E,0x00081B,0x00081C,0x00081F,0x000826,0x00080C,0x000D65,0x000D66,
	0x000820,0x00080D,0x000827,0x00080E,0x000D67,0x000829,0x000D68,0x000821,
	0x000822,0x000810,0x000828,0x00080F,0x000811,0x000D69,0x000823,0x000824,
	0x000825,
	};

	constexpr Serialization::FormArray Books = {
	0,
	};

	constexpr Serialization::FormArray MapMa = {
	0,
	};
	// clang-format on

	inline std::vector<std::string> Items_NameArray;
	inline std::vector<std::string> Items_TextArray;
	inline std::vector<RE::TESForm*> Items_FormArray;
	inline std::vector<bool> Items_BoolArray;
	inline uint32_t Items_EntriesTotal;
	inline uint32_t Items_EntriesFound;

	inline std::vector<std::string> Books_NameArray;
	inline std::vector<std::string> Books_TextArray;
	inline std::vector<RE::TESForm*> Books_FormArray;
	inline std::vector<bool> Books_BoolArray;
	inline uint32_t Books_EntriesTotal;
	inline uint32_t Books_EntriesFound;

	inline std::vector<std::string> MapMa_NameArray;
	inline std::vector<std::string> MapMa_TextArray;
	inline std::vector<RE::TESForm*> MapMa_FormArray;
	inline std::vector<bool> MapMa_BoolArray;
	inline uint32_t MapMa_EntriesTotal;
	inline uint32_t MapMa_EntriesFound;

	inline std::string_view modname = "AdditionalHearthfireDolls.esp";

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		if (const auto Mod = Serialization::CompletionistData::IsModInstalled(modname); !Mod) {
			return;
		}

		CHandler::SinkEvents();
		CHandler::InjectAndCompileData();
		PatchesInstalled += 1;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void CHandler::SinkEvents() {
		RE::BooksRead::GetEventSource()->AddEventSink(CHandler::GetSingleton());

		auto UserInterface = RE::UI::GetSingleton();
		UserInterface->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(CHandler::GetSingleton()));

		auto ESourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
		ESourceHolder->AddEventSink(static_cast<RE::BSTEventSink<RE::TESContainerChangedEvent>*>(CHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Item Added ) -------------
	//---------------------------------------------------

	EventResult CHandler::ProcessEvent(const RE::TESContainerChangedEvent* a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*) {

		if (!a_event || a_event->newContainer != 0x00014 || !CPatch_AHD_Items::Data.HasForm(a_event->baseObj)) { return EventResult::kContinue; }

		auto base = CPatch_AHD_Items::Data.GetBase(a_event->baseObj) ? CPatch_AHD_Items::Data.GetBase(a_event->baseObj) : a_event->baseObj;
		CHandler::ProcessFoundForm(base, a_event->baseObj, "NotifyItems");
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Events ( Books Read ) ----------------
	//---------------------------------------------------

	EventResult CHandler::ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) {

		if (!a_event || !CPatch_AHD_Books::Data.HasForm(a_event->book->GetFormID())) { return RE::BSEventNotifyControl::kContinue; }

		auto base = CPatch_AHD_Books::Data.GetBase(a_event->book->GetFormID()) ? CPatch_AHD_Books::Data.GetBase(a_event->book->GetFormID()) : a_event->book->GetFormID();
		CHandler::ProcessFoundForm(base, a_event->book->GetFormID(), "NotifyBooks");
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Events ( On Menu Open ) --------------
	//---------------------------------------------------

	EventResult CHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) {

		if (!a_event) { return RE::BSEventNotifyControl::kContinue; }

		if (a_event->menuName == RE::BookMenu::MENU_NAME && a_event->opening && CPatch_AHD_Books::Data.HasForm(RE::BookMenu::GetTargetForm()->GetFormID())) {
			if (auto target = RE::BookMenu::GetTargetForm()->GetFormID(); target) {
				auto base = CPatch_AHD_Books::Data.GetBase(target) ? CPatch_AHD_Books::Data.GetBase(target) : target;
				CHandler::ProcessFoundForm(base, target, "NotifyBooks");
				return EventResult::kContinue;
			}
			return EventResult::kContinue;
		}

		if (a_event->menuName == RE::MapMenu::MENU_NAME && a_event->opening) {

			for (auto i = 0; i < MapMa_FormArray.size(); i++) {
				CHandler::ProcessMapMarker(MapMa_FormArray[i], i);
			}
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Process Found Form ) -----
	//---------------------------------------------------

	void CHandler::ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, std::string a_variable) {

		if (a_variable == "NotifyBooks") {

			if (!FoundItemData.HasForm(a_eventID)) {
				auto msg = fmt::format("Completionist: Entry Complete - {:s}!"sv, CPatch_AHD_Books::Data.GetForm(a_eventID)->GetName());
				FrameworkAPI::SendNotification(msg, a_variable);
			}

			FoundItemData.AddForm(a_baseID);
			for (auto var : CPatch_AHD_Books::Data.GetAllVariations()) {
				if (CPatch_AHD_Books::Data.GetBase(var) == a_baseID) {
					FoundItemData.AddForm(var);
				}
			}


			auto t_pos = std::ranges::find(Books_FormArray, CPatch_AHD_Books::Data.GetForm(a_baseID));
			auto b_pos = std::distance(Books_FormArray.begin(), t_pos);
			Books_BoolArray[b_pos] = true;

			Books_EntriesFound = std::ranges::count(Books_BoolArray, true);
			return;
		}

		if (a_variable == "NotifyItems") {

			if (!FoundItemData.HasForm(a_eventID)) {
				auto msg = fmt::format("Completionist: Entry Complete - {:s}!"sv, CPatch_AHD_Items::Data.GetForm(a_eventID)->GetName());
				FrameworkAPI::SendNotification(msg, a_variable);
			}

			FoundItemData.AddForm(a_baseID);
			for (auto var : CPatch_AHD_Items::Data.GetAllVariations()) {
				if (CPatch_AHD_Items::Data.GetBase(var) == a_baseID) {
					FoundItemData.AddForm(var);
				}
			}


			auto t_pos = std::ranges::find(Items_FormArray, CPatch_AHD_Items::Data.GetForm(a_baseID));
			auto b_pos = std::distance(Items_FormArray.begin(), t_pos);
			Items_BoolArray[b_pos] = true;

			Items_EntriesFound = std::ranges::count(Items_BoolArray, true);
			return;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Process Map Marker ) -----
	//---------------------------------------------------

	void CHandler::ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos) {

		auto* a_marker = static_cast<RE::TESObjectREFR*>(a_form);

		if (a_marker) {
			if (auto extraMapMarker = Serialization::CompletionistData::GetMapMarkerInternal(a_marker); extraMapMarker && extraMapMarker->mapData) {
				if (extraMapMarker->mapData->flags.all(RE::MapMarkerData::Flag::kVisible, RE::MapMarkerData::Flag::kCanTravelTo) && !a_marker->IsDisabled()) {
					MapMa_BoolArray[a_pos] = true;
					FoundItemData_NoShow.AddForm(a_marker);
				}
			}
		}
		MapMa_EntriesFound = std::ranges::count(MapMa_BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		CPatch_AHD_Items::Data.CompileFormArray(CPatch_AHD::Items, modname);
		CPatch_AHD_Books::Data.CompileFormArray(CPatch_AHD::Books, modname);
		CPatch_AHD_MapMa::Data.CompileFormArray(CPatch_AHD::MapMa, modname);

		CPatch_AHD_Items::Data.MergeAsCollectable();
		CPatch_AHD_Books::Data.MergeAsCollectable();

		CPatch_AHD_Items::Data.Populate(Items_NameArray, Items_FormArray, Items_BoolArray, Items_TextArray);
		CPatch_AHD_Books::Data.Populate(Books_NameArray, Books_FormArray, Books_BoolArray, Books_TextArray);
		CPatch_AHD_MapMa::Data.Populate(MapMa_NameArray, MapMa_FormArray, MapMa_BoolArray, MapMa_TextArray, true);

		MapMa_TextArray.clear();
		for (auto& name : MapMa_NameArray) {
			MapMa_TextArray.push_back("$AddLocationHighlight{" + name + "}");
		}

		for (auto i = 0; i < Books_FormArray.size(); i++) {
			if (Books_FormArray[i]) {
				auto* book = static_cast<RE::TESObjectBOOK*>(Books_FormArray[i]);
				if (book->GetSpell()) {
					Books_TextArray[i] = "$AddSpellTomeHighlight{" + Books_NameArray[i] + "}{" + book->GetSpell()->GetName() + "}";
				}
				else if (book->TeachesSkill()) {
					Books_TextArray[i] = "$AddSkillBookHighlight{" + Books_NameArray[i] + "}{" + CFramework_Master::FrameworkAPI::GetBookSkill(book->GetSkill()) + "}";
				}
			}
		}

		Items_EntriesTotal = Items_FormArray.size();
		Items_EntriesFound = std::ranges::count(Items_BoolArray, true);

		Books_EntriesTotal = Books_FormArray.size();
		Books_EntriesFound = std::ranges::count(Books_BoolArray, true);

		MapMa_EntriesTotal = MapMa_FormArray.size();
		MapMa_EntriesFound = std::ranges::count(MapMa_BoolArray, true);

		for (auto& name : Items_NameArray) {
			INFO(name);
		}

		for (auto& name : Books_NameArray) {
			INFO(name);
		}

		for (auto& name : MapMa_NameArray) {
			INFO(name);
		}

		//using namespace FrameworkHandler;
		//RegisterAs<FrameworkID::kAHD_Items>(&Items_NameArray, &Items_FormArray, &Items_BoolArray, &Items_TextArray);
		//RegisterAs<FrameworkID::kAHD_Books>(&Books_NameArray, &Books_FormArray, &Books_BoolArray, &Books_TextArray);
		//RegisterAs<FrameworkID::kAHD_MapMa>(&MapMa_NameArray, &MapMa_FormArray, &MapMa_BoolArray, &MapMa_TextArray);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		if (const auto Mod = Serialization::CompletionistData::IsModInstalled(modname); !Mod) {
			return;
		}

		for (auto i = 0; i < Items_FormArray.size(); i++) {
			if (FoundItemData.HasForm(Items_FormArray[i]->GetFormID())) {
				Items_BoolArray[i] = true;
			}
		}

		for (auto i = 0; i < Books_FormArray.size(); i++) {
			if (FoundItemData.HasForm(Books_FormArray[i]->GetFormID())) {
				Books_BoolArray[i] = true;
			}
		}

		for (auto i = 0; i < MapMa_FormArray.size(); i++) {
			if (FoundItemData_NoShow.HasForm(MapMa_FormArray[i]->GetFormID())) {
				MapMa_BoolArray[i] = true;
			}
		}

		Items_EntriesTotal = Items_FormArray.size();
		Items_EntriesFound = std::ranges::count(Items_BoolArray, true);

		Books_EntriesTotal = Books_FormArray.size();
		Books_EntriesFound = std::ranges::count(Books_BoolArray, true);

		MapMa_EntriesTotal = MapMa_FormArray.size();
		MapMa_EntriesFound = std::ranges::count(MapMa_BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM is Entry Complete ) --
	//---------------------------------------------------

	uint32_t CHandler::IsOptionCompleted(std::string a_name) {

		if (auto t_pos = std::ranges::find(Items_NameArray, a_name); t_pos != Items_NameArray.end()) {
			return uint32_t(Items_BoolArray[std::distance(Items_NameArray.begin(), t_pos)]);
		}

		//---------------------------------------------------
		//---------------------------------------------------

		if (auto t_pos = std::ranges::find(Books_NameArray, a_name); t_pos != Books_NameArray.end()) {
			return uint32_t(Books_BoolArray[std::distance(Books_NameArray.begin(), t_pos)]);
		}
		return -1;
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Set Entry Complete ) -
	//---------------------------------------------------

	void CHandler::SetOptionCompleted(std::string a_name) {

		if (auto t_pos = std::ranges::find(Items_NameArray, a_name); t_pos != Items_NameArray.end()) {
			auto b_pos = std::distance(Items_NameArray.begin(), t_pos);

			if (Items_BoolArray.at(b_pos)) {
				Items_BoolArray.at(b_pos) = false;

				FoundItemData.RemoveForm(Items_FormArray.at(b_pos)->GetFormID());
				for (auto var : CPatch_AHD_Items::Data.GetAllVariations()) {
					if (CPatch_AHD_Items::Data.GetBase(var) == Items_FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.RemoveForm(var);
					}
				}
			}
			else {
				Items_BoolArray.at(b_pos) = true;
				FoundItemData.AddForm(Items_FormArray.at(b_pos)->GetFormID());
				for (auto var : CPatch_AHD_Items::Data.GetAllVariations()) {
					if (CPatch_AHD_Items::Data.GetBase(var) == Items_FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.AddForm(var);
					}
				}
			}

			Items_EntriesTotal = Items_FormArray.size();
			Items_EntriesFound = std::ranges::count(Items_BoolArray, true);
			return;
		}

		//---------------------------------------------------
		//---------------------------------------------------

		if (auto t_pos = std::ranges::find(Books_NameArray, a_name); t_pos != Books_NameArray.end()) {
			auto b_pos = std::distance(Books_NameArray.begin(), t_pos);

			if (Books_BoolArray.at(b_pos)) {
				Books_BoolArray.at(b_pos) = false;

				FoundItemData.RemoveForm(Books_FormArray.at(b_pos)->GetFormID());
				for (auto var : CPatch_AHD_Books::Data.GetAllVariations()) {
					if (CPatch_AHD_Books::Data.GetBase(var) == Books_FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.RemoveForm(var);
					}
				}
			}
			else {
				Books_BoolArray.at(b_pos) = true;
				FoundItemData.AddForm(Books_FormArray.at(b_pos)->GetFormID());
				for (auto var : CPatch_AHD_Books::Data.GetAllVariations()) {
					if (CPatch_AHD_Books::Data.GetBase(var) == Books_FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.AddForm(var);
					}
				}
			}

			Books_EntriesTotal = Books_FormArray.size();
			Books_EntriesFound = std::ranges::count(Books_BoolArray, true);
			return;
		}
	}
}