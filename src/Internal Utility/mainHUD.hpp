#pragma once

namespace Completionist_MainHUD
{
	class FunctionHolder {

		using VM = RE::BSScript::Internal::VirtualMachine;
		using StackID = RE::VMStackID;
		using Severity = RE::BSScript::ErrorLogger::Severity;

	public:
		static void	ProcessCrosshairReference(RE::HUDData* data);
		static bool ItemIsCollectable(RE::FormID a_formID);
		static bool ItemIsCollected(RE::FormID a_formID);
	};
}
