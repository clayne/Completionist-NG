#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CFramework_CCManager {

	class CHandler
	{
	public:
		static void	InstallFramework();
		static void	UpdateFoundForms();
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Locations
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_CreationClub_L
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
//------------------------------------------------------------------------------------------------------------------------------ Books
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_CreationClub_B
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

		static bool			IsOptionCompleted(std::string a_name);
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
//------------------------------------------------------------------------------------------------------------------------------ Spell Tomes
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_CreationClub_S
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

		static bool			IsOptionCompleted(std::string a_name);
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
//------------------------------------------------------------------------------------------------------------------------------ Armor
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_CreationClub_A
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class CHandler final : public RE::BSTEventSink<RE::TESContainerChangedEvent> {

	public: [[nodiscard]] static CHandler* GetSingleton() {
		static CHandler singleton;
		return &singleton;
	}

		  static void RegisterEvents() { register_event<RE::TESContainerChangedEvent>(); }

		  EventResult			ProcessEvent(const RE::TESContainerChangedEvent* a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*) override;

		  static void			InstallFramework();
		  static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_curID);
		  static void			SendNotification(std::string a_msg);
		  static void			InjectAndCompileData();
		  static void			UpdateFoundForms();

		  static bool			IsOptionCompleted(std::string a_name);
		  static void			SetOptionCompleted(std::string a_name);

	private:

		CHandler() = default;
		CHandler(const CHandler&) = delete;
		CHandler(CHandler&&) = delete;

		~CHandler() override = default;

		CHandler& operator=(const CHandler&) = delete;
		CHandler& operator=(CHandler&&) = delete;

		template <class T>
		static void register_event()
		{
			if (const auto scripts = RE::ScriptEventSourceHolder::GetSingleton(); scripts) {
				scripts->AddEventSink<T>(GetSingleton());
			}
		}
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Items
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_CreationClub_I
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class CHandler final : public RE::BSTEventSink<RE::TESContainerChangedEvent> {

	public: [[nodiscard]] static CHandler* GetSingleton() {
		static CHandler singleton;
		return &singleton;
	}

		  static void RegisterEvents() { register_event<RE::TESContainerChangedEvent>(); }

		  EventResult			ProcessEvent(const RE::TESContainerChangedEvent* a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*) override;

		  static void			InstallFramework();
		  static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_curID);
		  static void			SendNotification(std::string a_msg);
		  static void			InjectAndCompileData();
		  static void			UpdateFoundForms();

		  static bool			IsOptionCompleted(std::string a_name);
		  static void			SetOptionCompleted(std::string a_name);

	private:

		CHandler() = default;
		CHandler(const CHandler&) = delete;
		CHandler(CHandler&&) = delete;

		~CHandler() override = default;

		CHandler& operator=(const CHandler&) = delete;
		CHandler& operator=(CHandler&&) = delete;

		template <class T>
		static void register_event()
		{
			if (const auto scripts = RE::ScriptEventSourceHolder::GetSingleton(); scripts) {
				scripts->AddEventSink<T>(GetSingleton());
			}
		}
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Weapons
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_CreationClub_W
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class CHandler final : public RE::BSTEventSink<RE::TESContainerChangedEvent> {

	public: [[nodiscard]] static CHandler* GetSingleton() {
		static CHandler singleton;
		return &singleton;
	}

		  static void RegisterEvents() { register_event<RE::TESContainerChangedEvent>(); }

		  EventResult			ProcessEvent(const RE::TESContainerChangedEvent* a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*) override;

		  static void			InstallFramework();
		  static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_curID);
		  static void			SendNotification(std::string a_msg);
		  static void			InjectAndCompileData();
		  static void			UpdateFoundForms();

		  static bool			IsOptionCompleted(std::string a_name);
		  static void			SetOptionCompleted(std::string a_name);

	private:

		CHandler() = default;
		CHandler(const CHandler&) = delete;
		CHandler(CHandler&&) = delete;

		~CHandler() override = default;

		CHandler& operator=(const CHandler&) = delete;
		CHandler& operator=(CHandler&&) = delete;

		template <class T>
		static void register_event()
		{
			if (const auto scripts = RE::ScriptEventSourceHolder::GetSingleton(); scripts) {
				scripts->AddEventSink<T>(GetSingleton());
			}
		}
	};
}