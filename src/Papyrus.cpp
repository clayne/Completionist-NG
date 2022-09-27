#include "Papyrus.hpp"
#include "Internal Utility/InventoryMode.hpp"

namespace Completionist {

	//---------------------------------------------------
	//-- Script Functions -------------------------------
	//---------------------------------------------------

	void Papyrus::_UpdateVariables(VM* vm, StackID stackId, RE::StaticFunctionTag*) {

		Completionist_Inventory::FunctionHolder::UpdateVariables();
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

	std::string Papyrus::GetHexValue(RE::StaticFunctionTag*, uint32_t IntVal) {
		
		if (!IntVal) { return ""; }

		return fmt::format("#{:X}", IntVal);
	}

	//---------------------------------------------------
	//-- Utility Functions ------------------------------
	//---------------------------------------------------

	int32_t Papyrus::GetIntValue(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::BSFixedString HexString) {

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

	std::string Papyrus::do_replace(std::string const& in, std::string const& from, std::string const& to) {
		
		return std::regex_replace(in, std::regex(from), to);
	}

	//---------------------------------------------------
	//-- Utility Functions ------------------------------
	//---------------------------------------------------

	void Papyrus::SendNotification(RE::StaticFunctionTag*, std::string Message, std::string Colour, bool ColourEnabled) {
	
		auto message = fmt::format("<font color='{:s}'>{:s}</font>"sv, Colour, Message);
		if (!ColourEnabled) { RE::DebugNotification(Message.c_str()); return; }
		RE::DebugNotification(message.c_str());
	}

	//---------------------------------------------------
	//-- Registration Functions -------------------------
	//---------------------------------------------------

	void Papyrus::Register() {

		SKSE::GetPapyrusInterface()->Register(Papyrus::RegisterFunctions);
		INFO("Completionist: Successfully Registered Papyrus Functions");
	}

	auto Papyrus::RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm) -> bool {

		a_vm->RegisterFunction("GetVersion", "Completionist_Native", GetVersion);
		a_vm->RegisterFunction("GetIntValue", "Completionist_Native", GetIntValue);
		a_vm->RegisterFunction("GetHexValue", "Completionist_Native", GetHexValue);
		a_vm->RegisterFunction("SendNotification", "Completionist_Native", SendNotification);
		a_vm->RegisterFunction("_UpdateVariables", "Completionist_Native", _UpdateVariables);
		return true;
	}
}
	//---------------------------------------------------
	//-- End Of Code ------------------------------------
	//---------------------------------------------------
