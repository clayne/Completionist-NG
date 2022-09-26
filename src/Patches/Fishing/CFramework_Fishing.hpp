#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CPatchManager_Fishing {

	class CHandler
	{
	public:
		static void	InstallFramework();
		static void	UpdateFoundForms();
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Items
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingItems
{

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	extern Serialization::CompletionistData Data;

	using EventResult = RE::BSEventNotifyControl;

	class CHandler final :

		public RE::BSTEventSink<RE::TESContainerChangedEvent> {

	public: [[nodiscard]] static CHandler* GetSingleton() {
		static CHandler singleton;
		return &singleton;
	}

		  static void RegisterEvents() { register_event<RE::TESContainerChangedEvent>(); }

		  EventResult			ProcessEvent(const RE::TESContainerChangedEvent* a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*) override;

		  static void			InstallFramework();
		  static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_curID);
		  static void			InjectAndCompileData();
		  static void			UpdateFoundForms();

		  static uint32_t		IsOptionCompleted(std::string a_name);
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
//------------------------------------------------------------------------------------------------------------------------------ Books
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingBooks
{
	extern Serialization::CompletionistData Data;

	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class BHandler : public RE::BSTEventSink<RE::BooksRead::Event> {
	public:
		static BHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;

		static void			InstallFramework();
		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_eventID, bool a_supress);
		static void			InjectAndCompileData();
		static void			UpdateFoundForms();

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);
	};

	class MHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
	public:
		static MHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Locations - Arctic
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingSpots_A
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
//------------------------------------------------------------------------------------------------------------------------------ Locations - Caves
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingSpots_C
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
//------------------------------------------------------------------------------------------------------------------------------ Locations - Lakes
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingSpots_L
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
//------------------------------------------------------------------------------------------------------------------------------ Locations - Streams
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CPatch_FishingSpots_S
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