#include "FrameworkMaster.hpp"
#include "Internal Utility/ScriptObject.hpp"

//Item Frameworks
#include "Items/CFramework_Armor.hpp"
#include "Items/CFramework_Claws.hpp"
#include "Items/CFramework_Items.hpp"
#include "Items/CFramework_Jewelry.hpp"
#include "Items/CFramework_Liquor.hpp"
#include "Items/CFramework_Masks.hpp"
#include "Items/CFramework_Weapons.hpp"

//Misc Frameworks
#include "Books/CFramework_Books.hpp"
#include "Locations/CFramework_Locations.hpp"

//Creation Club
#include "Creation Club/CFramework_CreationClub.hpp"

namespace CFramework_Master {

	inline Serialization::CompletionistData FoundItemData;

	std::vector<RE::TESForm*> EmptyFormArray;
	std::vector<std::string> EmptyNameArray;
	std::vector<std::string> EmptyTextArray;
	std::vector<bool> EmptyBoolArray;

	ScriptObjectPtr MCMScript2;

	//---------------------------------------------------
	//-- Framework Functions ( Master Registration ) ----
	//---------------------------------------------------

	void FrameworkAPI::Register() {

		FoundItemData.SetAsSerializable();

		auto papyrus = SKSE::GetPapyrusInterface();
		papyrus->Register(FrameworkAPI::RegisterFunctions);

		CFramework_CCManager::CHandler::InstallFramework();

		CFramework_Armor::CHandler::InstallFramework();
		CFramework_Jewelry::CHandler::InstallFramework();
		CFramework_Liquor::CHandler::InstallFramework();
		CFramework_Weapons::CHandler::InstallFramework();

		CFramework_DragonClaws_V::CHandler::InstallFramework();
		CFramework_DragonClaws_P::CHandler::InstallFramework();
		CFramework_DragonMasks_V::CHandler::InstallFramework();
		CFramework_DragonMasks_P::CHandler::InstallFramework();

		CFramework_BooksManager::CHandler::InstallFramework();
		CFramework_LocationsManager::CHandler::InstallFramework();
		RE::DebugMessageBox("Finished Installing Frameworks");
	}
	
	//---------------------------------------------------
	//-- Framework Functions ( Papyrus Registrations ) --
	//---------------------------------------------------

	auto FrameworkAPI::RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm) -> bool
	{
		a_vm->RegisterFunction("Framework_GetFormArrayByID", "Completionist_Native", Framework_GetFormArrayByID);
		a_vm->RegisterFunction("Framework_GetNameArrayByID", "Completionist_Native", Framework_GetNameArrayByID);
		a_vm->RegisterFunction("Framework_GetBoolArrayByID", "Completionist_Native", Framework_GetBoolArrayByID);
		a_vm->RegisterFunction("Framework_GetTextArrayByID", "Completionist_Native", Framework_GetTextArrayByID);

		a_vm->RegisterFunction("Framework_GetEntries_TotalByID", "Completionist_Native", Framework_GetEntries_TotalByID);
		a_vm->RegisterFunction("Framework_GetEntries_FoundByID", "Completionist_Native", Framework_GetEntries_FoundByID);

		a_vm->RegisterFunction("Framework_CCItemsInstalled", "Completionist_Native", Framework_CCItemsInstalled);
		a_vm->RegisterFunction("Framework_CCBooksInstalled", "Completionist_Native", Framework_CCBooksInstalled);
		a_vm->RegisterFunction("Framework_CCLocationsInstalled", "Completionist_Native", Framework_CCLocationsInstalled);

		a_vm->RegisterFunction("Framework_IsOptionCompleted", "Completionist_Native", Framework_IsOptionCompleted);
		a_vm->RegisterFunction("Framework_SetOptionCompleted", "Completionist_Native", Framework_SetOptionCompleted);
		return true;
	}

	//---------------------------------------------------
	//-- Framework Functions ( CC Variable Setter ) -----
	//---------------------------------------------------

	bool FrameworkAPI::Framework_CCLocationsInstalled(RE::StaticFunctionTag*) {

		return 
			bool(CFramework_CreationClub_L::Data.data.size());
	}

	bool FrameworkAPI::Framework_CCBooksInstalled(RE::StaticFunctionTag*) {

		return 
			bool(CFramework_CreationClub_B::Data.data.size());;
	}

	bool FrameworkAPI::Framework_CCItemsInstalled(RE::StaticFunctionTag*) {

		return
			bool(CFramework_CreationClub_A::Data.data.size()) || 
			bool(CFramework_CreationClub_W::Data.data.size()) ||
			bool(CFramework_CreationClub_I::Data.data.size());
	}

	//---------------------------------------------------
	//-- Framework Functions ( Load Frameworks ) --------
	//---------------------------------------------------

	void FrameworkAPI::Framework_Load() {

		CFramework_CCManager::CHandler::UpdateFoundForms();

		CFramework_Armor::CHandler::UpdateFoundForms();
		CFramework_Weapons::CHandler::UpdateFoundForms();

		CFramework_Jewelry::CHandler::UpdateFoundForms();
		CFramework_Liquor::CHandler::UpdateFoundForms();

		CFramework_DragonClaws_V::CHandler::UpdateFoundForms();
		CFramework_DragonClaws_P::CHandler::UpdateFoundForms();

		CFramework_DragonMasks_V::CHandler::UpdateFoundForms();
		CFramework_DragonMasks_P::CHandler::UpdateFoundForms();

		CFramework_BooksManager::CHandler::UpdateFoundForms();
		CFramework_LocationsManager::CHandler::UpdateFoundForms();
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Total ) ---------
	//---------------------------------------------------

	uint32_t FrameworkAPI::Framework_GetEntries_TotalByID(RE::StaticFunctionTag*, uint32_t a_ID) {

		switch (a_ID) {

			//-------------------------------------------- Items

		case 00:
			return CFramework_Armor::EntriesTotal;

		case 01:
			return CFramework_Jewelry::EntriesTotal;

		case 02:
			return CFramework_DragonClaws_V::EntriesTotal;

		case 03:
			return CFramework_DragonClaws_P::EntriesTotal;

		case 04:
			return CFramework_Liquor::EntriesTotal;

		case 05:
			return CFramework_DragonMasks_V::EntriesTotal;

		case 06:
			return CFramework_DragonMasks_P::EntriesTotal;

		case 07:
			return CFramework_Weapons::EntriesTotal;

			//-------------------------------------------- Books

		case 10:
			return CFramework_Books_AG::EntriesTotal;

		case 11:
			return CFramework_Books_HS::EntriesTotal;

		case 12:
			return CFramework_Books_TY::EntriesTotal;

		case 13:
			return CFramework_Books_SB::EntriesTotal;

		case 14:
			return CFramework_Books_ST::EntriesTotal;

			//-------------------------------------------- Locations

		case 20:
			return CFramework_Locations_DG::EntriesTotal;

		case 21:
			return CFramework_Locations_DB::EntriesTotal;

		case 23:
			return CFramework_Locations_AG::EntriesTotal;

		case 24:
			return CFramework_Locations_HR::EntriesTotal;

		case 25:
			return CFramework_Locations_SZ::EntriesTotal;

			//-------------------------------------------- Creation CLub

		case 90:
			return CFramework_CreationClub_L::EntriesTotal;

		case 91:
			return CFramework_CreationClub_B::EntriesTotal;

		case 92:
			return CFramework_CreationClub_S::EntriesTotal;

		case 93:
			return CFramework_CreationClub_A::EntriesTotal;

		case 94:
			return CFramework_CreationClub_W::EntriesTotal;

		case 95:
			return CFramework_CreationClub_I::EntriesTotal;

		default:
			return -1;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Found ) ---------
	//---------------------------------------------------

	uint32_t FrameworkAPI::Framework_GetEntries_FoundByID(RE::StaticFunctionTag*, uint32_t a_ID) {

		switch (a_ID) {

		//-------------------------------------------- Items

	case 00:
		return CFramework_Armor::EntriesFound;

	case 01:
		return CFramework_Jewelry::EntriesFound;

	case 02:
		return CFramework_DragonClaws_V::EntriesFound;

	case 03:
		return CFramework_DragonClaws_P::EntriesFound;

	case 04:
		return CFramework_Liquor::EntriesFound;

	case 05:
		return CFramework_DragonMasks_V::EntriesFound;

	case 06:
		return CFramework_DragonMasks_P::EntriesFound;

	case 07:
		return CFramework_Weapons::EntriesFound;

		//-------------------------------------------- Books

	case 10:
		return CFramework_Books_AG::EntriesFound;

	case 11:
		return CFramework_Books_HS::EntriesFound;

	case 12:
		return CFramework_Books_TY::EntriesFound;

	case 13:
		return CFramework_Books_SB::EntriesFound;

	case 14:
		return CFramework_Books_ST::EntriesFound;

		//-------------------------------------------- Locations

	case 20:
		return CFramework_Locations_DG::EntriesFound;

	case 21:
		return CFramework_Locations_DB::EntriesFound;

	case 23:
		return CFramework_Locations_AG::EntriesFound;

	case 24:
		return CFramework_Locations_HR::EntriesFound;

	case 25:
		return CFramework_Locations_SZ::EntriesFound;

		//-------------------------------------------- Creation CLub

	case 90:
		return CFramework_CreationClub_L::EntriesFound;

	case 91:
		return CFramework_CreationClub_B::EntriesFound;

	case 92:
		return CFramework_CreationClub_S::EntriesFound;

	case 93:
		return CFramework_CreationClub_A::EntriesFound;

	case 94:
		return CFramework_CreationClub_W::EntriesFound;

	case 95:
		return CFramework_CreationClub_I::EntriesFound;

		default:
			return -1;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Forms ) ---------
	//---------------------------------------------------

	std::vector<RE::TESForm*> FrameworkAPI::Framework_GetFormArrayByID(RE::StaticFunctionTag*, uint32_t a_ID) {

		switch (a_ID) {

			//-------------------------------------------- Items

		case 00:
			return CFramework_Armor::FormArray;

		case 01:
			return CFramework_Jewelry::FormArray;

		case 02:
			return CFramework_DragonClaws_V::FormArray;

		case 03:
			return CFramework_DragonClaws_P::FormArray;

		case 04:
			return CFramework_Liquor::FormArray;

		case 05:
			return CFramework_DragonMasks_V::FormArray;

		case 06:
			return CFramework_DragonMasks_P::FormArray;

		case 07:
			return CFramework_Weapons::FormArray;

			//-------------------------------------------- Books

		case 10:
			return CFramework_Books_AG::FormArray;

		case 11:
			return CFramework_Books_HS::FormArray;

		case 12:
			return CFramework_Books_TY::FormArray;

		case 13:
			return CFramework_Books_SB::FormArray;

		case 14:
			return CFramework_Books_ST::FormArray;

			//-------------------------------------------- Locations

		case 20:
			return CFramework_Locations_DG::FormArray;

		case 21:
			return CFramework_Locations_DB::FormArray;

		case 23:
			return CFramework_Locations_AG::FormArray;

		case 24:
			return CFramework_Locations_HR::FormArray;

		case 25:
			return CFramework_Locations_SZ::FormArray;

			//-------------------------------------------- Creation CLub

		case 90:
			return CFramework_CreationClub_L::FormArray;

		case 91:
			return CFramework_CreationClub_B::FormArray;

		case 92:
			return CFramework_CreationClub_S::FormArray;

		case 93:
			return CFramework_CreationClub_A::FormArray;

		case 94:
			return CFramework_CreationClub_W::FormArray;

		case 95:
			return CFramework_CreationClub_I::FormArray;

		default:
			return EmptyFormArray;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Names ) ---------
	//---------------------------------------------------

	std::vector<std::string> FrameworkAPI::Framework_GetNameArrayByID(RE::StaticFunctionTag*, uint32_t a_ID) {

		switch (a_ID) {

			//-------------------------------------------- Items

		case 00:
			return CFramework_Armor::NameArray;

		case 01:
			return CFramework_Jewelry::NameArray;

		case 02:
			return CFramework_DragonClaws_V::NameArray;

		case 03:
			return CFramework_DragonClaws_P::NameArray;

		case 04:
			return CFramework_Liquor::NameArray;

		case 05:
			return CFramework_DragonMasks_V::NameArray;

		case 06:
			return CFramework_DragonMasks_P::NameArray;

		case 07:
			return CFramework_Weapons::NameArray;

			//-------------------------------------------- Books

		case 10:
			return CFramework_Books_AG::NameArray;

		case 11:
			return CFramework_Books_HS::NameArray;

		case 12:
			return CFramework_Books_TY::NameArray;

		case 13:
			return CFramework_Books_SB::NameArray;

		case 14:
			return CFramework_Books_ST::NameArray;

			//-------------------------------------------- Locations

		case 20:
			return CFramework_Locations_DG::NameArray;

		case 21:
			return CFramework_Locations_DB::NameArray;

		case 23:
			return CFramework_Locations_AG::NameArray;

		case 24:
			return CFramework_Locations_HR::NameArray;

		case 25:
			return CFramework_Locations_SZ::NameArray;

			//-------------------------------------------- Creation CLub

		case 90:
			return CFramework_CreationClub_L::NameArray;

		case 91:
			return CFramework_CreationClub_B::NameArray;

		case 92:
			return CFramework_CreationClub_S::NameArray;

		case 93:
			return CFramework_CreationClub_A::NameArray;

		case 94:
			return CFramework_CreationClub_W::NameArray;

		case 95:
			return CFramework_CreationClub_I::NameArray;

		default:
			return EmptyNameArray;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Texts ) ---------
	//---------------------------------------------------

	std::vector<std::string> FrameworkAPI::Framework_GetTextArrayByID(RE::StaticFunctionTag*, uint32_t a_ID) {

		switch (a_ID) {

			//-------------------------------------------- Items

		case 00:
			return CFramework_Armor::TextArray;

		case 01:
			return CFramework_Jewelry::TextArray;

		case 02:
			return CFramework_DragonClaws_V::TextArray;

		case 03:
			return CFramework_DragonClaws_P::TextArray;

		case 04:
			return CFramework_Liquor::TextArray;

		case 05:
			return CFramework_DragonMasks_V::TextArray;

		case 06:
			return CFramework_DragonMasks_P::TextArray;

		case 07:
			return CFramework_Weapons::TextArray;

			//-------------------------------------------- Books

		case 10:
			return CFramework_Books_AG::TextArray;

		case 11:
			return CFramework_Books_HS::TextArray;

		case 12:
			return CFramework_Books_TY::TextArray;

		case 13:
			return CFramework_Books_SB::TextArray;

		case 14:
			return CFramework_Books_ST::TextArray;

			//-------------------------------------------- Locations

		case 20:
			return CFramework_Locations_DG::TextArray;

		case 21:
			return CFramework_Locations_DB::TextArray;

		case 23:
			return CFramework_Locations_AG::TextArray;

		case 24:
			return CFramework_Locations_HR::TextArray;

		case 25:
			return CFramework_Locations_SZ::TextArray;

			//-------------------------------------------- Creation CLub

		case 90:
			return CFramework_CreationClub_L::TextArray;

		case 91:
			return CFramework_CreationClub_B::TextArray;

		case 92:
			return CFramework_CreationClub_S::TextArray;

		case 93:
			return CFramework_CreationClub_A::TextArray;

		case 94:
			return CFramework_CreationClub_W::TextArray;

		case 95:
			return CFramework_CreationClub_I::TextArray;

		default:
			return EmptyTextArray;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Bools ) ---------
	//---------------------------------------------------

	std::vector<bool> FrameworkAPI::Framework_GetBoolArrayByID(RE::StaticFunctionTag*, uint32_t a_ID) {

		switch (a_ID) {

			//-------------------------------------------- Items

		case 00:
			return CFramework_Armor::BoolArray;

		case 01:
			return CFramework_Jewelry::BoolArray;

		case 02:
			return CFramework_DragonClaws_V::BoolArray;

		case 03:
			return CFramework_DragonClaws_P::BoolArray;

		case 04:
			return CFramework_Liquor::BoolArray;

		case 05:
			return CFramework_DragonMasks_V::BoolArray;

		case 06:
			return CFramework_DragonMasks_P::BoolArray;

		case 07:
			return CFramework_Weapons::BoolArray;

			//-------------------------------------------- Books

		case 10:
			return CFramework_Books_AG::BoolArray;

		case 11:
			return CFramework_Books_HS::BoolArray;

		case 12:
			return CFramework_Books_TY::BoolArray;

		case 13:
			return CFramework_Books_SB::BoolArray;

		case 14:
			return CFramework_Books_ST::BoolArray;

			//-------------------------------------------- Locations

		case 20:
			return CFramework_Locations_DG::BoolArray;

		case 21:
			return CFramework_Locations_DB::BoolArray;

		case 23:
			return CFramework_Locations_AG::BoolArray;

		case 24:
			return CFramework_Locations_HR::BoolArray;

		case 25:
			return CFramework_Locations_SZ::BoolArray;

			//-------------------------------------------- Creation CLub

		case 90:
			return CFramework_CreationClub_L::BoolArray;

		case 91:
			return CFramework_CreationClub_B::BoolArray;

		case 92:
			return CFramework_CreationClub_S::BoolArray;

		case 93:
			return CFramework_CreationClub_A::BoolArray;

		case 94:
			return CFramework_CreationClub_W::BoolArray;

		case 95:
			return CFramework_CreationClub_I::BoolArray;

		default:
			return EmptyBoolArray;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Getter - Status ) ----
	//---------------------------------------------------

	bool FrameworkAPI::Framework_IsOptionCompleted(RE::StaticFunctionTag*, uint32_t a_ID, std::string a_name) {

		switch (a_ID) {

			//-------------------------------------------- Items

		case 00:
			return CFramework_Armor::CHandler::IsOptionCompleted(a_name);

		case 01:
			return CFramework_Jewelry::CHandler::IsOptionCompleted(a_name);

		case 02:
			return CFramework_DragonClaws_V::CHandler::IsOptionCompleted(a_name);

		case 03:
			return CFramework_DragonClaws_P::CHandler::IsOptionCompleted(a_name);

		case 04:
			return CFramework_Liquor::CHandler::IsOptionCompleted(a_name);

		case 05:
			return CFramework_DragonMasks_V::CHandler::IsOptionCompleted(a_name);

		case 06:
			return CFramework_DragonMasks_P::CHandler::IsOptionCompleted(a_name);

		case 07:
			return CFramework_Weapons::CHandler::IsOptionCompleted(a_name);

			//-------------------------------------------- Books

		case 10:
			return CFramework_Books_AG::BookHandler::IsOptionCompleted(a_name);

		case 11:
			return CFramework_Books_HS::BookHandler::IsOptionCompleted(a_name);

		case 12:
			return CFramework_Books_TY::BookHandler::IsOptionCompleted(a_name);

		case 13:
			return CFramework_Books_SB::BookHandler::IsOptionCompleted(a_name);

		case 14:
			return CFramework_Books_ST::BookHandler::IsOptionCompleted(a_name);

		//-------------------------------------------- Creation CLub

		case 91:
			return CFramework_CreationClub_B::BookHandler::IsOptionCompleted(a_name);

		case 92:
			return CFramework_CreationClub_S::BookHandler::IsOptionCompleted(a_name);

		case 93:
			return CFramework_CreationClub_A::CHandler::IsOptionCompleted(a_name);

		case 94:
			return CFramework_CreationClub_W::CHandler::IsOptionCompleted(a_name);

		case 95:
			return CFramework_CreationClub_I::CHandler::IsOptionCompleted(a_name);

		default:
			return false;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Setter - Status ) ----
	//---------------------------------------------------

	void FrameworkAPI::Framework_SetOptionCompleted(RE::StaticFunctionTag*, uint32_t a_ID, std::string a_name) {

		switch (a_ID) {

			//-------------------------------------------- Items

		case 00:
			CFramework_Armor::CHandler::SetOptionCompleted(a_name);
			break;

		case 01:
			CFramework_Jewelry::CHandler::SetOptionCompleted(a_name);
			break;

		case 02:
			CFramework_DragonClaws_V::CHandler::SetOptionCompleted(a_name);
			break;

		case 03:
			CFramework_DragonClaws_P::CHandler::SetOptionCompleted(a_name);
			break;

		case 04:
			CFramework_Liquor::CHandler::SetOptionCompleted(a_name);
			break;

		case 05:
			CFramework_DragonMasks_V::CHandler::SetOptionCompleted(a_name);
			break;

		case 06:
			CFramework_DragonMasks_P::CHandler::SetOptionCompleted(a_name);
			break;

		case 07:
			CFramework_Weapons::CHandler::CHandler::SetOptionCompleted(a_name);
			break;

			//-------------------------------------------- Books

		case 10:
			CFramework_Books_AG::BookHandler::SetOptionCompleted(a_name);
			break;

		case 11:
			CFramework_Books_HS::BookHandler::SetOptionCompleted(a_name);
			break;

		case 12:
			CFramework_Books_TY::BookHandler::SetOptionCompleted(a_name);
			break;

		case 13:
			CFramework_Books_SB::BookHandler::SetOptionCompleted(a_name);
			break;

		case 14:
			CFramework_Books_ST::BookHandler::SetOptionCompleted(a_name);
			break;

			//-------------------------------------------- Creation CLub

		case 91:
			CFramework_CreationClub_B::BookHandler::SetOptionCompleted(a_name);
			break;

		case 92:
			CFramework_CreationClub_S::BookHandler::SetOptionCompleted(a_name);
			break;

		case 93:
			CFramework_CreationClub_A::CHandler::SetOptionCompleted(a_name);
			break;

		case 94:
			CFramework_CreationClub_W::CHandler::SetOptionCompleted(a_name);
			break;

		case 95:
			CFramework_CreationClub_I::CHandler::SetOptionCompleted(a_name);
			break;

		default:
			break;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Show Message - Main ) ----
	//---------------------------------------------------

	void FrameworkAPI::ShowMessageMainMCM(RE::BSFixedString a_msg) {

		auto papyrusVM = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		RE::VMHandle questHandle;

		if (GetQuestHandle(papyrusVM, std::string("Completionist_Main"), questHandle)) {

			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> funcReturn;
			auto args = RE::MakeFunctionArguments(RE::BSFixedString(a_msg));
			papyrusVM->DispatchMethodCall2(questHandle, "Completionist_MCMScript", "_ShowMessage", args, funcReturn);
			return;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Show Message - Misc ) ----
	//---------------------------------------------------

	void FrameworkAPI::ShowMessageMiscMCM(RE::BSFixedString a_msg) {

		auto papyrusVM = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		RE::VMHandle questHandle;

		if (GetQuestHandle(papyrusVM, std::string("Completionist_Misc"), questHandle)) {

			RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> funcReturn;
			auto args = RE::MakeFunctionArguments(RE::BSFixedString(a_msg));
			papyrusVM->DispatchMethodCall2(questHandle, "Completionist_MCMScript2", "_ShowMessage", args, funcReturn);
			return;
		}

	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Quest Handle ) -------
	//---------------------------------------------------

	bool FrameworkAPI::GetQuestHandle(RE::BSScript::IVirtualMachine* a_vm, std::string ScriptName, RE::VMHandle& handleOut) {

		auto handlePolicy = a_vm->GetObjectHandlePolicy();
		if (!handlePolicy) { return false; }

		auto quest = RE::TESForm::LookupByEditorID(ScriptName);
		if (!quest) { return false; }

		handleOut = handlePolicy->GetHandleForObject(static_cast<RE::VMTypeID>(quest->GetFormType()), quest);
		if (!handleOut) { return false; }

		return true;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Skill Book AVal ) ----
	//---------------------------------------------------

	std::string FrameworkAPI::GetBookSkill(RE::ActorValue a_val){

		switch (a_val) {

		case RE::ActorValue::kOneHanded:
			return "One-Handed";

		case RE::ActorValue::kTwoHanded:
			return "Two-Handed";

		case RE::ActorValue::kArchery:
			return "Marksman";

		case RE::ActorValue::kBlock:
			return "Block";

		case RE::ActorValue::kSmithing:
			return "Smithing";

		case RE::ActorValue::kHeavyArmor:
			return "Heavy Armor";

		case RE::ActorValue::kLightArmor:
			return "Light Armor";

		case RE::ActorValue::kPickpocket:
			return "Pickpocket";

		case RE::ActorValue::kLockpicking:
			return "LockPicking";

		case RE::ActorValue::kSneak:
			return "Sneak";

		case RE::ActorValue::kAlchemy:
			return "Alchemy";

		case RE::ActorValue::kSpeech:
			return "SpeechCraft";

		case RE::ActorValue::kAlteration:
			return "Alteration";

		case RE::ActorValue::kConjuration:
			return "Conjuration";

		case RE::ActorValue::kDestruction:
			return "Destruction";

		case RE::ActorValue::kIllusion:
			return "Illusion";

		case RE::ActorValue::kRestoration:
			return "Restoration";

		case RE::ActorValue::kEnchanting:
			return "Enchanting";

		default:
			return "";
		}
	}
}
