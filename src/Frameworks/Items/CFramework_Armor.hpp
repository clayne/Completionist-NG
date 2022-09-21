#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CFramework_Armor
{
	extern Serialization::CompletionistData Data;
	
	extern std::vector<std::string> NameArray;
	extern std::vector<std::string> TextArray;
	extern std::vector<RE::TESForm*> FormArray;
	extern std::vector<bool> BoolArray;

	extern uint32_t EntriesTotal;
	extern uint32_t EntriesFound;

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