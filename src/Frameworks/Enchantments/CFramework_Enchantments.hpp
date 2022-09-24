#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CFramework_EnchantmentsManager {

	class CHandler
	{
	public:
		static void	InstallFramework();
		static void	UpdateFoundForms();
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Vanilla (Armor Enchantments)
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_AEnchantments_V
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;
	class CHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		static CHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;

		static void			InstallFramework();
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Summermyst (Armor Enchantments)
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_AEnchantments_P
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;
	class CHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		static CHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;

		static void			InstallFramework();
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Vanilla (Weapon Enchantments)
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_WEnchantments_V
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;
	class CHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		static CHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;

		static void			InstallFramework();
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Summermyst (Weapon Enchantments)
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_WEnchantments_P
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;
	class CHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		static CHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;

		static void			InstallFramework();
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};
}