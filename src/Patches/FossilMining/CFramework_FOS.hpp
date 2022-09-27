#pragma once

#include <SKSE\API.h>
#include "Serialization.hpp"

namespace CPatch_FOS_ItmL1 {
	extern Serialization::CompletionistData Data;
}

namespace CPatch_FOS_ItmL2 {
	extern Serialization::CompletionistData Data;
}

namespace CPatch_FOS_ItmL3 {
	extern Serialization::CompletionistData Data;
}

namespace CPatch_FOS 
{	
	enum PatchID : uint32_t
	{	
		kItmL1 = 212,
		kItmL2 = 213,
		kItmL3 = 214,
	};

	extern std::vector<std::string> ItmL1_NameArray;
	extern std::vector<std::string> ItmL1_TextArray;
	extern std::vector<RE::TESForm*> ItmL1_FormArray;
	extern std::vector<bool> ItmL1_BoolArray;
	extern uint32_t ItmL1_EntriesTotal;
	extern uint32_t ItmL1_EntriesFound;

	extern std::vector<std::string> ItmL2_NameArray;
	extern std::vector<std::string> ItmL2_TextArray;
	extern std::vector<RE::TESForm*> ItmL2_FormArray;
	extern std::vector<bool> ItmL2_BoolArray;
	extern uint32_t ItmL2_EntriesTotal;
	extern uint32_t ItmL2_EntriesFound;

	extern std::vector<std::string> ItmL3_NameArray;
	extern std::vector<std::string> ItmL3_TextArray;
	extern std::vector<RE::TESForm*> ItmL3_FormArray;
	extern std::vector<bool> ItmL3_BoolArray;
	extern uint32_t ItmL3_EntriesTotal;
	extern uint32_t ItmL3_EntriesFound;

	using EventResult = RE::BSEventNotifyControl;

	class CHandler final :

	public RE::BSTEventSink<RE::TESContainerChangedEvent> {

		public: [[nodiscard]] static CHandler* GetSingleton() {
			static CHandler singleton;
			return &singleton;
		}

		EventResult			ProcessEvent(const RE::TESContainerChangedEvent* a_event, RE::BSTEventSource<RE::TESContainerChangedEvent>*) override;

		static void			SinkEvents();
		static void			InstallFramework();
		static void			UpdateFoundForms();
		static void			InjectAndCompileData();

		static void			ProcessFoundForm(RE::FormID a_baseID, RE::FormID a_curID, std::string a_variable);

		static uint32_t		IsOptionCompleted(std::string a_name);
		static void			SetOptionCompleted(std::string a_name);

		public: [[nodiscard]] static uint32_t ReturnEntriesInt(uint32_t a_patchID, std::string a_section) {

			switch (a_patchID) {

			case kItmL1:
				if (a_section == "Total") { return ItmL1_EntriesTotal; }
				if (a_section == "Found") { return ItmL1_EntriesFound; }
				return -1;

			case kItmL2:
				if (a_section == "Total") { return ItmL2_EntriesTotal; }
				if (a_section == "Found") { return ItmL2_EntriesFound; }
				return -1;

			case kItmL3:
				if (a_section == "Total") { return ItmL3_EntriesTotal; }
				if (a_section == "Found") { return ItmL3_EntriesFound; }
				return -1;

			default:
				return -1;
			}
		}

		public: [[nodiscard]] static std::vector<RE::TESForm*> ReturnEntriesForm(uint32_t a_patchID) {

			std::vector<RE::TESForm*> Null;

			switch (a_patchID) {

			case kItmL1:
				return ItmL1_FormArray;

			case kItmL2:
				return ItmL2_FormArray;

			case kItmL3:
				return ItmL3_FormArray;

			default:
				return Null;
			}
		}

		public: [[nodiscard]] static std::vector<std::string> ReturnEntriesString(uint32_t a_patchID, std::string a_section) {

			std::vector<std::string> Null;

			switch (a_patchID) {

			case kItmL1:
				if (a_section == "Name") { return ItmL1_NameArray; }
				if (a_section == "Text") { return ItmL1_TextArray; }
				return Null;

			case kItmL2:
				if (a_section == "Name") { return ItmL2_NameArray; }
				if (a_section == "Text") { return ItmL2_TextArray; }
				return Null;

			case kItmL3:
				if (a_section == "Name") { return ItmL3_NameArray; }
				if (a_section == "Text") { return ItmL3_TextArray; }
				return Null;

			default:
				return Null;
			}
		}

		public: [[nodiscard]] static std::vector<bool> ReturnEntriesBool(uint32_t a_patchID) {

			std::vector<bool> Null;

			switch (a_patchID) {

			case kItmL1:
				return ItmL1_BoolArray;

			case kItmL2:
				return ItmL2_BoolArray;

			case kItmL3:
				return ItmL3_BoolArray;

			default:
				return Null;
			}
		}
	};
}