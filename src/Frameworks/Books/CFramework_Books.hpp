#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CFramework_BooksManager {

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

namespace CFramework_Books_AG
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			SendNotification(std::string a_msg);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MenuHandler*GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ H - S
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Books_HS
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			SendNotification(std::string a_msg);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MenuHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ T - Y
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Books_TY
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			SendNotification(std::string a_msg);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MenuHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ SkillBooks
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Books_SB
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			SendNotification(std::string a_msg);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MenuHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ SpellTomes
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Books_ST
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			SendNotification(std::string a_msg);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MenuHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Dawnguard
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Books_DG
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			SendNotification(std::string a_msg);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MenuHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}


//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Dawnguard SpellTomes
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Books_DGS
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			SendNotification(std::string a_msg);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MenuHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Dragonborn
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Books_DB
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			SendNotification(std::string a_msg);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MenuHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Dragonborn
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_Books_DBS
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			SendNotification(std::string a_msg);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MenuHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}