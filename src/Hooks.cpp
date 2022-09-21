#pragma once
#include <string.h>
#include "Hooks.hpp"
#include "Papyrus.hpp"
#include "Internal Utility/mainHUD.hpp"
#include "Internal Utility/InventoryMode.hpp"

namespace SKSE_Hooks {

	//---------------------------------------------------
	//-- Install Hooks Function -------------------------
	//---------------------------------------------------

	void Install() {

		CrossHairHook::Hook();
	}

	//---------------------------------------------------
	//-- Crosshair Hook For HUD Tagging -----------------
	//---------------------------------------------------

	void CrossHairHook::Hook() {

		auto& trampoline = SKSE::GetTrampoline();
		_OnUpdateCrosshairText = trampoline.write_call<5>(RELOCATION_ID(39535, 40621).address() + REL::Relocate(0x289, 0x280), OnUpdateCrosshairText);
	}

	void CrossHairHook::OnUpdateCrosshairText(RE::UIMessageQueue* a_this, const RE::BSFixedString& a_menuName, RE::UI_MESSAGE_TYPE a_type, RE::IUIMessageData* a_data) {

		_OnUpdateCrosshairText(a_this, a_menuName, a_type, a_data);

		const auto data = a_data ? static_cast<RE::HUDData*>(a_data) : nullptr;
		const auto crossHairRef = data ? data->crossHairRef.get() : RE::TESObjectREFRPtr();

		if (!data) { return; }
		Completionist_MainHUD::FunctionHolder::ProcessCrosshairReference(data);
	}

	//---------------------------------------------------
	//-- End Of Code  -----------------------------------
	//---------------------------------------------------
}
