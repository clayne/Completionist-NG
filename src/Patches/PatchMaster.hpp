#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CPatch_Master
{
	extern int PatchesInstalled;

	class PatchAPI {

		using VM = RE::BSScript::Internal::VirtualMachine;
		using StackID = RE::VMStackID;
		using Severity = RE::BSScript::ErrorLogger::Severity;

	public:

		static void	InstallPatches();
		static void LoadallPatches();

		static bool ShouldDisplayMiscHeader(RE::StaticFunctionTag*);

		static std::vector<RE::TESForm*> GetFormArrayByID(uint32_t a_patchID);
		static std::vector<std::string> GetNameArrayByID(uint32_t a_patchID);
		static std::vector<std::string> GetTextArrayByID(uint32_t a_patchID);
		static std::vector<bool> GetBoolArrayByID(uint32_t a_patchID);

		static uint32_t GetEntries_TotalByID(uint32_t a_patchID);
		static uint32_t GetEntries_FoundByID(uint32_t a_patchID);

		static uint32_t IsOptionCompleted(uint32_t a_patchID, std::string a_name);
		static void SetOptionCompleted(uint32_t a_patchID, std::string a_name);
	};
}
