#include "Serialization.hpp"
#include "CFramework_Liquor.hpp"
#include "Frameworks/FrameworkMaster.hpp"
#include "Internal Utility/ScriptObject.hpp"

#undef AddForm

namespace CFramework_Liquor {

	using namespace CFramework_Master;

	// clang-format off

	constexpr Serialization::FormArray SkyrimForms = {
	0x107A8A,0x0D055E,0x0DC172,0x065C39,0x036D53,0x0B91D7,
	0x03F4BD,0x0555E8,0x0F257E,0x065C37,0x065C38,0x09380D,
	};

	constexpr Serialization::FormArray DawnguardForms = {
	0x01391D,
	};

	constexpr Serialization::FormArray HearthfireForms = {
	0x003536,0x003535,
	};

	constexpr Serialization::FormArray DragonbornForms = {
	0x03572F,0x024E0B,
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

		CHandler::RegisterEvents();
		CHandler::InjectAndCompileData();
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

		if (auto t_pos = std::find(FormArray.begin(), FormArray.end(), Data.GetForm(a_baseID)); t_pos != FormArray.end()) {
			auto b_pos = std::distance(FormArray.begin(), t_pos);
			BoolArray.at(b_pos) = true;

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

			EntriesFound = std::ranges::count(BoolArray, true);
			INFO("FOUND ITEMS LIST = {}", FoundItemData.data.size());
		}
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
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CFramework_Liquor::SkyrimForms, "Skyrim.esm");
		Data.CompileFormArray(CFramework_Liquor::DawnguardForms, "Dawnguard.esm");
		Data.CompileFormArray(CFramework_Liquor::HearthfireForms, "HearthFires.esm");
		Data.CompileFormArray(CFramework_Liquor::DragonbornForms, "Dragonborn.esm");
		Data.MergeAsCollectable();

		CFramework_Liquor::Data.Populate(NameArray, FormArray, BoolArray);

		for (auto& name : NameArray) {
			TextArray.push_back("NO_HIGHLIGHT");
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

	//---------------------------------------------------
	//-- Framework Functions ( MCM is Entry Complete ) --
	//---------------------------------------------------

	bool CHandler::IsOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			return BoolArray[std::distance(NameArray.begin(), t_pos)];
		}
		return false;
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