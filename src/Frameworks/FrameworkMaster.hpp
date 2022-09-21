#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CFramework_Master
{
	extern Serialization::CompletionistData FoundItemData;

	class FrameworkAPI {

		using VM = RE::BSScript::Internal::VirtualMachine;
		using StackID = RE::VMStackID;
		using Severity = RE::BSScript::ErrorLogger::Severity;

	public:

		static void Register();

		static bool	RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm);

		static void Framework_Load();

		static std::vector<RE::TESForm*> Framework_GetFormArrayByID(RE::StaticFunctionTag*, uint32_t a_ID);
		static std::vector<std::string> Framework_GetNameArrayByID(RE::StaticFunctionTag*, uint32_t a_ID);
		static std::vector<std::string> Framework_GetTextArrayByID(RE::StaticFunctionTag*, uint32_t a_ID);
		static std::vector<bool> Framework_GetBoolArrayByID(RE::StaticFunctionTag*, uint32_t a_ID);

		static uint32_t Framework_GetEntries_TotalByID(RE::StaticFunctionTag*, uint32_t a_ID);
		static uint32_t Framework_GetEntries_FoundByID(RE::StaticFunctionTag*, uint32_t a_ID);

		static void ShowMessageMainMCM(RE::BSFixedString a_msg);
		static void ShowMessageMiscMCM(RE::BSFixedString a_msg);
		static bool GetQuestHandle(RE::BSScript::IVirtualMachine* a_vm, std::string ScriptName, RE::VMHandle& handleOut);

		static bool Framework_IsOptionCompleted(RE::StaticFunctionTag*, uint32_t a_ID, std::string a_name);
		static void Framework_SetOptionCompleted(RE::StaticFunctionTag*, uint32_t a_ID, std::string a_name);

		static std::string GetBookSkill(RE::ActorValue a_val);

		static bool Framework_CCItemsInstalled(RE::StaticFunctionTag*);
		static bool Framework_CCBooksInstalled(RE::StaticFunctionTag*);
		static bool Framework_CCLocationsInstalled(RE::StaticFunctionTag*);
	};
}
