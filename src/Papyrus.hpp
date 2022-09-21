#pragma once

#include <SKSE/RegistrationSet.h>

//---------------------------------------------------
//-- NameSpace --------------------------------------
//---------------------------------------------------

namespace Completionist
{	
    class Papyrus {

		using VM = RE::BSScript::Internal::VirtualMachine;
		using StackID = RE::VMStackID;
		using Severity = RE::BSScript::ErrorLogger::Severity;

    public:

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//Papyrus Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		static void	SendNotification(RE::StaticFunctionTag*, std::string Message, std::string Colour, bool ColourEnabled);

		static bool	CanTravelToMarker(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESObjectREFR* ref);
		static bool	IsMarkerVisibleOnMap(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESObjectREFR* ref);

		static std::vector<std::string>	SortStringArray(RE::StaticFunctionTag*, const RE::reference_array<std::string> a_strings);

		static std::string	GetHexValue(RE::StaticFunctionTag*, std::uint32_t IntVal);
		static std::string	GetVersion(RE::StaticFunctionTag*);

		static uint32_t	CheckForConflicts(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESForm* cQuest, std::string cName);
		static uint32_t	GetMarkerType(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESObjectREFR* ref);
		static int32_t	GetIntValue(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::BSFixedString HexVal);

		static RE::BSFixedString	GetBookSkill(VM* vm, StackID stackId, RE::StaticFunctionTag*, uint32_t oSkillVal);
		static RE::BSFixedString	GetMarkerName(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::TESObjectREFR* ref);
		static RE::TESForm*	FormLookUp(RE::StaticFunctionTag*, std::string_view EditorID);

		static void _UpdateVariables(VM* vm, StackID stackId, RE::StaticFunctionTag*);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//Internal Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		static void	Register();

		static bool	RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm);
		static bool	CanTravelToInternal(RE::TESObjectREFR* ref);
		
		static std::string	do_replace(std::string const& in, std::string const& from, std::string const& to);
		static RE::ExtraMapMarker*	GetMapMarkerInternal(RE::TESObjectREFR* ref);
    };

	//---------------------------------------------------
	//-- End Of Code ------------------------------------
	//---------------------------------------------------
}
