#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CFramework_LocationsManager {

	class CHandler
	{
	public:
		static void	InstallFramework();
		static void	UpdateFoundForms();
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ A - G
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Locations_AG
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
		static void			ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ H - R
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Locations_HR
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
		static void			ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ S - Z
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Locations_SZ
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
		static void			ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Dawnguard
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Locations_DG
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
		static void			ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Dragonborn
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Locations_DB
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
		static void			ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();
	};
}