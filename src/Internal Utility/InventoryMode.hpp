#pragma once

namespace Inv_vars {

	extern ScriptObjectPtr  Inv_MCM;

	extern uint32_t IconChoice;
	extern uint32_t TextChoice;

	extern bool Inv_Ammo_Enabled_New;
	extern bool Inv_Ammo_Enabled_Found;
	extern uint32_t Inv_Ammo_Colour_New;
	extern uint32_t Inv_Ammo_Colour_Found;
	extern std::string Inv_Ammo_ColourString_New;
	extern std::string Inv_Ammo_ColourString_Found;

	extern bool Inv_Alchemy_Enabled_New;
	extern bool Inv_Alchemy_Enabled_Found;
	extern uint32_t Inv_Alchemy_Colour_New;
	extern uint32_t Inv_Alchemy_Colour_Found;
	extern std::string Inv_Alchemy_ColourString_New;
	extern std::string Inv_Alchemy_ColourString_Found;

	extern bool Inv_Armor_Enabled_New;
	extern bool Inv_Armor_Enabled_Found;
	extern uint32_t Inv_Armor_Colour_New;
	extern uint32_t Inv_Armor_Colour_Found;
	extern std::string Inv_Armor_ColourString_New;
	extern std::string Inv_Armor_ColourString_Found;

	extern bool Inv_Books_Enabled_New;
	extern bool Inv_Books_Enabled_Found;
	extern uint32_t Inv_Books_Colour_New;
	extern uint32_t Inv_Books_Colour_Found;
	extern std::string Inv_Books_ColourString_New;
	extern std::string Inv_Books_ColourString_Found;

	extern bool Inv_Weapons_Enabled_New;
	extern bool Inv_Weapons_Enabled_Found;
	extern uint32_t Inv_Weapons_Colour_New;
	extern uint32_t Inv_Weapons_Colour_Found;
	extern std::string Inv_Weapons_ColourString_New;
	extern std::string Inv_Weapons_ColourString_Found;

	extern bool Inv_Other_Enabled_New;
	extern bool Inv_Other_Enabled_Found;
	extern uint32_t Inv_Other_Colour_New;
	extern uint32_t Inv_Other_Colour_Found;
	extern std::string Inv_Other_ColourString_New;
	extern std::string Inv_Other_ColourString_Found;

	extern uint32_t Inv_Default_New;
	extern uint32_t Inv_Default_Found;

	extern std::string Inv_CrosshairTag_New;
	extern std::string Inv_CrosshairTag_Found;

	extern bool Inv_DearDiarySupport;
}

namespace InventoryEvents
{
	using EventResult = RE::BSEventNotifyControl;
	class InventoryMenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		static InventoryMenuHandler*		GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}

namespace Completionist_Inventory
{
	class FunctionHolder {

		using VM = RE::BSScript::Internal::VirtualMachine;
		using StackID = RE::VMStackID;
		using Severity = RE::BSScript::ErrorLogger::Severity;

	public:

		static void			UpdateVariables();

		static void			Register();

		static bool			IsReady();

		static const char*	ProcessInventoryText(const char* OriginalName, RE::TESBoundObject* baseform);
	};
}

namespace Completionist_IconSetter{

	void ProcessEntry(RE::ItemList::Item* a_item);
	void ApplyTextModifications(std::string& a_name);

	bool ItemIsCollectable(RE::FormID a_formID);
	bool ItemIsCollected(RE::FormID a_formID);
}