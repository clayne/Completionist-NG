#pragma once

namespace Completionist_MainHUD
{
	class FunctionHolder {

		using VM = RE::BSScript::Internal::VirtualMachine;
		using StackID = RE::VMStackID;
		using Severity = RE::BSScript::ErrorLogger::Severity;

	public:
		static void InstallHook();

		static void	ProcessCrosshairReference(RE::HUDData* data);
		static bool ItemIsCollectable(RE::FormID a_formID);
		static bool ItemIsCollected(RE::FormID a_formID);
		
		static void OnUpdateCrosshairText(RE::UIMessageQueue* a_this, const RE::BSFixedString& a_menuName, RE::UI_MESSAGE_TYPE a_type, RE::IUIMessageData* a_data);

	private:
		static inline REL::Relocation<decltype(OnUpdateCrosshairText)> _OnUpdateCrosshairText;
	};
}
