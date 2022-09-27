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

		static std::string	GetHexValue(RE::StaticFunctionTag*, std::uint32_t IntVal);
		static std::string	GetVersion(RE::StaticFunctionTag*);

		static int32_t	GetIntValue(VM* vm, StackID stackId, RE::StaticFunctionTag*, RE::BSFixedString HexVal);

		static void _UpdateVariables(VM* vm, StackID stackId, RE::StaticFunctionTag*);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//Internal Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		static void	Register();

		static bool	RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm);
		static std::string	do_replace(std::string const& in, std::string const& from, std::string const& to);
    };

	//---------------------------------------------------
	//-- End Of Code ------------------------------------
	//---------------------------------------------------
}
