#include "Papyrus.hpp"
#include "Internal Utility/ScriptObject.hpp"
#include "Internal Utility/InventoryMode.hpp"
#include "Internal Utility/mainHUD.hpp"

using namespace ScriptObject;

ScriptObjectPtr ConflictManager_Script;

namespace Completionist {

	//---------------------------------------------------
	//-- Script Functions -------------------------------
	//---------------------------------------------------

	void Papyrus::_UpdateVariables(VM* vm, StackID stackId, RE::StaticFunctionTag*) {

		Completionist_Inventory::FunctionHolder::UpdateVariables();
	}

	//---------------------------------------------------
	//-- Script Functions -------------------------------
	//---------------------------------------------------

	uint32_t Papyrus::CheckForConflicts(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESForm* cQuest, std::string cName) {

		ConflictManager_Script = FromForm(cQuest, cName);
		if (!ConflictManager_Script) {return 0; }

		auto IsValid = ConflictManager_Script->GetProperty("bCompletionist");
		if (!IsValid) {return 1; }

		vm->TraceStack("Completionist Script Check Passed", stackId, Severity::kFatal);
		return 2;
	}

	//---------------------------------------------------
	//-- Versioning Functions ---------------------------
	//---------------------------------------------------

	std::string Papyrus::GetVersion(RE::StaticFunctionTag*) {
		
		return std::string(Papyrus::do_replace(Plugin::Version.string(), "-", "."));
	}

	//---------------------------------------------------
	//-- Utility Functions ------------------------------
	//---------------------------------------------------

	RE::TESForm* Papyrus::FormLookUp(RE::StaticFunctionTag*, std::string_view EditorID) {

		auto form = RE::TESForm::LookupByEditorID(EditorID);
		if (!form) { return nullptr; }
		return form;
	}

	//---------------------------------------------------
	//-- Utility Functions ------------------------------
	//---------------------------------------------------

	std::string Papyrus::GetHexValue(RE::StaticFunctionTag*, uint32_t IntVal)
	{
		if (!IntVal) { return ""; }

		return fmt::format("#{:X}", IntVal);
	}

	//---------------------------------------------------
	//-- Utility Functions ------------------------------
	//---------------------------------------------------

	int32_t Papyrus::GetIntValue(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::BSFixedString HexString)
	{

		if (HexString.empty()) {
			return -1; //Return -1 to the MCM and display empty string error.
		}

		char f = HexString[0];
		if (f != '#') {
			return -2; //Return -2 to the MCM and display a formatting error.
		}

		size_t length = strlen(HexString.c_str());
		if (length != 7) {
			return -4; //Return -4 to the MCM and display a Size formatting error.
		}

		std::string s = Papyrus::do_replace(HexString.c_str(), "#", "0x");

		std::int32_t value = -3;
		if (!s.empty()) {
			try {
				value = std::stoi(s, nullptr, 0);
			}
			catch (...) {
				vm->TraceStack("String is out of range - cannot be converted to an integer", stackId); //Return -3 to the MCM and display an out of range error.
			}
		}
		return value;
	}

	//---------------------------------------------------
	//-- Utility Functions ------------------------------
	//---------------------------------------------------

	std::string Papyrus::do_replace(std::string const& in, std::string const& from, std::string const& to)
	{
		return std::regex_replace(in, std::regex(from), to);
	}

	//---------------------------------------------------
	//-- Utility Functions ------------------------------
	//---------------------------------------------------

	void Papyrus::SendNotification(RE::StaticFunctionTag*, std::string Message, std::string Colour, bool ColourEnabled)
	{
		auto message = fmt::format("<font color='{:s}'>{:s}</font>"sv, Colour, Message);

		if (!ColourEnabled) { RE::DebugNotification(Message.c_str()); return; }
		RE::DebugNotification(message.c_str());
	}

	//---------------------------------------------------
	//-- Utility Functions ------------------------------
	//---------------------------------------------------

	std::vector<std::string> Papyrus::SortStringArray(RE::StaticFunctionTag*, const RE::reference_array<std::string> a_strings)
	{
		std::vector<std::string> strings(a_strings);

		strings.erase(std::ranges::remove_if(strings, [](const std::string& str) {return str.empty();}).begin(), strings.end());
		std::ranges::sort(strings);

		return strings;
	}

	//---------------------------------------------------
	//-- Utility Functions ------------------------------
	//---------------------------------------------------

	RE::BSFixedString Papyrus::GetBookSkill(VM* vm, StackID stackId, RE::StaticFunctionTag*, uint32_t SkillVal)
	{
		if (!SkillVal) {
			vm->TraceStack("No Int Value Passed To Function", stackId, Severity::kError);
			return RE::BSFixedString();
		}

		switch (SkillVal) {
		case 6:
			return "One-Handed";
		case 7:
			return "Two-Handed";
		case 8:
			return "Marksman";
		case 9:
			return "Block";
		case 10:
			return "Smithing";
		case 11:
			return "Heavy Armor";
		case 12:
			return "Light Armor";
		case 13:
			return "Pickpocket";
		case 14:
			return "LockPicking";
		case 15:
			return "Sneak";
		case 16:
			return "Alchemy";
		case 17:
			return "SpeechCraft";
		case 18:
			return "Alteration";
		case 19:
			return "Conjuration";
		case 20:
			return "Destruction";
		case 21:
			return "Illusion";
		case 22:
			return "Restoration";
		case 23:
			return "Enchanting";
		default:
			return RE::BSFixedString();
		}
	}

	//---------------------------------------------------
	//-- Map Marker Functions ---------------------------
	//---------------------------------------------------

	RE::BSFixedString Papyrus::GetMarkerName(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESObjectREFR* ref)
	{
		if (!ref) {
			vm->TraceStack("ObjectReference is None", stackId, Severity::kError);
		}

		auto extraMapMarker = GetMapMarkerInternal(ref);

		if (!extraMapMarker) {
			vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
			return RE::BSFixedString();
		}

		if (!extraMapMarker->mapData) {
			vm->TraceStack("the Map Marker data is missing", stackId, Severity::kError);
			return RE::BSFixedString();
		}

		return extraMapMarker->mapData->locationName.fullName;
	}

	//---------------------------------------------------
	//-- Map Marker Functions ---------------------------
	//---------------------------------------------------

	uint32_t Papyrus::GetMarkerType(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESObjectREFR* ref)
	{
		if (!ref) {
			vm->TraceStack("ObjectReference is None", stackId, Severity::kError);
		}

		auto extraMapMarker = GetMapMarkerInternal(ref);

		if (!extraMapMarker) {
			vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
			return 0;
		}

		if (!extraMapMarker->mapData) {
			vm->TraceStack("the Map Marker data is missing", stackId, Severity::kError);
			return 0;
		}

		// Opps, the common library is missed alligned here
		//return static_cast<uint32_t>(extraMapMarker->mapData->type.underlying());
		return static_cast<uint32_t>(extraMapMarker->mapData->pad02);
	}

	//---------------------------------------------------
	//-- Map Marker Functions ---------------------------
	//---------------------------------------------------

	bool Papyrus::CanTravelToMarker(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESObjectREFR* ref)
	{
		if (!ref) {
			vm->TraceStack("ObjectReference is None", stackId, Severity::kError);
		}

		auto extraMapMarker = GetMapMarkerInternal(ref);

		if (!extraMapMarker) {
			vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
			return false;
		}

		if (!extraMapMarker->mapData) {
			vm->TraceStack("the Map Marker data is missing", stackId, Severity::kError);
			return false;
		}

		return CanTravelToInternal(ref);
	}

	//---------------------------------------------------
	//-- Map Marker Functions ---------------------------
	//---------------------------------------------------

	bool Papyrus::IsMarkerVisibleOnMap(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESObjectREFR* ref)
	{
		if (!ref) {
			vm->TraceStack("ObjectReference is None", stackId, Severity::kError);
			return false;
		}

		auto extraMapMarker = GetMapMarkerInternal(ref);

		if (!extraMapMarker) {
			vm->TraceStack("the ObjectReference is not a Map Marker", stackId, Severity::kWarning);
			return false;
		}

		if (!extraMapMarker->mapData) {
			vm->TraceStack("the Map Marker data is missing", stackId, Severity::kError);
			return false;
		}

		// If the reference is disabled, it cannot be seen on the map regardless of the visible flag
		return extraMapMarker->mapData->flags.any(RE::MapMarkerData::Flag::kVisible) && !ref->IsDisabled();
	}

	//---------------------------------------------------
	//-- Map Marker Functions ---------------------------
	//---------------------------------------------------

	RE::ExtraMapMarker* Papyrus::GetMapMarkerInternal(RE::TESObjectREFR* ref)
	{
		if (!ref) { return nullptr; }
		if (!ref->extraList.HasType<RE::ExtraMapMarker>()) { return nullptr; }

		return ref->extraList.GetByType<RE::ExtraMapMarker>();
	}

	//---------------------------------------------------
	//-- Map Marker Functions ---------------------------
	//---------------------------------------------------

	bool Papyrus::CanTravelToInternal(RE::TESObjectREFR* ref)
	{
		if (!ref) { return false; }

		auto mm = GetMapMarkerInternal(ref);
		if (!mm) { return false; }

		/* Also have to check if the object reference is enabled.Certain civil war camp markers, for example, have the "Can Travel To" flag on but they are
		disabled so they cannot be selected on the map*/
		return (mm->mapData->flags.all(RE::MapMarkerData::Flag::kCanTravelTo, RE::MapMarkerData::Flag::kVisible) && !ref->IsDisabled());
	}

	//---------------------------------------------------
	//-- Registration Functions -------------------------
	//---------------------------------------------------

	void Papyrus::Register()
	{
		INFO("Completionist: Registering Papyrus Functions");

		auto papyrus = SKSE::GetPapyrusInterface();

		papyrus->Register(Papyrus::RegisterFunctions);

		INFO("Completionist: Successfully Registered Papyrus Functions");
	}

	auto Papyrus::RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm) -> bool
	{
		a_vm->RegisterFunction("_UpdateVariables", "Completionist_Native", _UpdateVariables);
		
		a_vm->RegisterFunction("GetVersion", "Completionist_Native", GetVersion);
		a_vm->RegisterFunction("CheckForConflicts", "Completionist_Native", CheckForConflicts);

		a_vm->RegisterFunction("GetIntValue", "Completionist_Native", GetIntValue);
		a_vm->RegisterFunction("GetHexValue", "Completionist_Native", GetHexValue);
		a_vm->RegisterFunction("SendNotification", "Completionist_Native", SendNotification);
		a_vm->RegisterFunction("GetBookSkill", "Completionist_Native", GetBookSkill);
		a_vm->RegisterFunction("SortStringArray", "Completionist_Native", SortStringArray);
		a_vm->RegisterFunction("FormLookUp", "Completionist_Native", FormLookUp);

		//Map Marker Functions
		a_vm->RegisterFunction("GetMarkerName", "Completionist_Native", GetMarkerName);
		a_vm->RegisterFunction("GetMarkerType", "Completionist_Native", GetMarkerType);
		a_vm->RegisterFunction("CanTravelToMarker", "Completionist_Native", CanTravelToMarker);
		a_vm->RegisterFunction("IsMarkerVisibleOnMap", "Completionist_Native", IsMarkerVisibleOnMap);
		return true;
	}
}
	//---------------------------------------------------
	//-- End Of Code ------------------------------------
	//---------------------------------------------------
