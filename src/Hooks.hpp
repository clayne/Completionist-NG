#pragma once

//---------------------------------------------------
//-- NameSpace --------------------------------------
//---------------------------------------------------

namespace SKSE_Hooks
{
	void Install();

	class CrossHairHook
	{
	public:
		static void Hook();
		static void OnUpdateCrosshairText(RE::UIMessageQueue* a_this, const RE::BSFixedString& a_menuName, RE::UI_MESSAGE_TYPE a_type, RE::IUIMessageData* a_data);

	private:
		static inline REL::Relocation<decltype(OnUpdateCrosshairText)> _OnUpdateCrosshairText;
	};
}
