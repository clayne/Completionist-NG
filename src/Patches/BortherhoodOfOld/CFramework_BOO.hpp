#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CPatch_BOO_Items {
	extern Serialization::CompletionistData Data;
}

namespace CPatch_BOO_Books {
	extern Serialization::CompletionistData Data;
}

namespace CPatch_BOO_MapMa {
	extern Serialization::CompletionistData Data;
}

namespace CPatch_BOO
{	
	enum PatchID : uint32_t
	{
		kItems = 203,
		KBooks = 204,
		KMapMa = 205,
	};

	extern std::vector<std::string> Items_NameArray;
	extern std::vector<std::string> Items_TextArray;
	extern std::vector<RE::TESForm*> Items_FormArray;
	extern std::vector<bool> Items_BoolArray;
	extern uint32_t Items_EntriesTotal;
	extern uint32_t Items_EntriesFound;

	extern std::vector<std::string> Books_NameArray;
	extern std::vector<std::string> Books_TextArray;
	extern std::vector<RE::TESForm*> Books_FormArray;
	extern std::vector<bool> Books_BoolArray;
	extern uint32_t Books_EntriesTotal;
	extern uint32_t Books_EntriesFound;

	extern std::vector<std::string> MapMa_NameArray;
	extern std::vector<std::string> MapMa_TextArray;
	extern std::vector<RE::TESForm*> MapMa_FormArray;
	extern std::vector<bool> MapMa_BoolArray;
	extern uint32_t MapMa_EntriesTotal;
	extern uint32_t MapMa_EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class CHandler final :

	public RE::BSTEventSink<RE::TESContainerChangedEvent>,
	public RE::BSTEventSink<RE::MenuOpenCloseEvent>,
	public RE::BSTEventSink<RE::BooksRead::Event> {

	public: [[nodiscard]] static CHandler* GetSingleton() {
		static CHandler singleton;
		return &singleton;
	}

		EventResult			ProcessEvent(const RE::TESContainerChangedEvent* a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*) override;
		EventResult			ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;
		EventResult			ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;

		static void			SinkEvents();
		static void			InstallFramework();
		static void			UpdateFoundForms();
		static void			InjectAndCompileData();

		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_curID, std::string a_variable);
		static void			ProcessMapMarker(RE::TESForm* a_form, uint32_t a_pos);

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);

		public: [[nodiscard]] static uint32_t ReturnEntriesInt(uint32_t a_patchID, std::string a_section) {

			switch (a_patchID) {

			case kItems:
				if (a_section == "Total") { return Items_EntriesTotal; }
				if (a_section == "Found") { return Items_EntriesFound; }
				return -1;

			case KBooks:
				if (a_section == "Total") { return Books_EntriesTotal; }
				if (a_section == "Found") { return Books_EntriesFound; }
				return -1;

			case KMapMa:
				if (a_section == "Total") { return MapMa_EntriesTotal; }
				if (a_section == "Found") { return MapMa_EntriesFound; }
				return -1;

			default:
				return -1;
			}
		}

		public: [[nodiscard]] static std::vector<RE::TESForm*> ReturnEntriesForm(uint32_t a_patchID) {

			std::vector<RE::TESForm*> Null;

			switch (a_patchID) {

			case kItems:
				return Items_FormArray;

			case KBooks:
				return Books_FormArray;

			case KMapMa:
				return MapMa_FormArray;

			default:
				return Null;
			}
		}

		public: [[nodiscard]] static std::vector<std::string> ReturnEntriesString(uint32_t a_patchID, std::string a_section) {

			std::vector<std::string> Null;

			switch (a_patchID) {

			case kItems:
				if (a_section == "Name") { return Items_NameArray; }
				if (a_section == "Text") { return Items_TextArray; }
				return Null;

			case KBooks:
				if (a_section == "Name") { return Books_NameArray; }
				if (a_section == "Text") { return Books_TextArray; }
				return Null;

			case KMapMa:
				if (a_section == "Name") { return MapMa_NameArray; }
				if (a_section == "Text") { return MapMa_TextArray; }
				return Null;

			default:
				return Null;
			}
		}

		public: [[nodiscard]] static std::vector<bool> ReturnEntriesBool(uint32_t a_patchID) {

			std::vector<bool> Null;

			switch (a_patchID) {

			case kItems:
				return Items_BoolArray;

			case KBooks:
				return Books_BoolArray;

			case KMapMa:
				return MapMa_BoolArray;

			default:
				return Null;
			}
		}
	};
}