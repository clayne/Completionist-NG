#include "PCH.h"
#include "Radiant Quests Manager.hpp"
#include "Homes.hpp"

using namespace Quest_Manager;

namespace CCHomes
{
	EventResult ScriptEventHandler::ProcessEvent(const RE::TESQuestStageEvent* a_event, RE::BSTEventSource<RE::TESQuestStageEvent>*) {
		
		if (!a_event) { return EventResult::kContinue; }

		if (const auto quest = RE::TESForm::LookupByID<RE::TESQuest>(a_event->formID)) {
			auto questID = std::string(quest->GetFormEditorID());

			if (questID == "ccEEJSSE001_Quest" && a_event->stage == 10) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 101, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}
			if (questID == "ccEEJSSE002_MageTowerQuest" && a_event->stage == 100) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 102, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}
			if (questID == "ccEEJSSE003_HouseQuest" && a_event->stage == 100) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 103, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}
			if (questID == "ccAARSSE001ManufactoryControlQuest" && a_event->stage == 100) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 104, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}
			if (questID == "ccEEJSSE004_Quest" && a_event->stage == 100) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 105, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}
			if (questID == "ccRMSSSE001_Quest" && a_event->stage == 200) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 106, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}
			if (questID == "ccEEJSSE005_Quest" && (a_event->stage == 200 || a_event->stage == 300)) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 107, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}
			if (questID == "ccBGSSSE031_HomeQuest" && a_event->stage == 30) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 108, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}
			if (questID == "ccVSVSSE004_MainQuest" && a_event->stage == 300) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 110, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}

			if (questID == "HousePurchase" && a_event->stage == 10) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 999, nullptr};
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}

			if (questID == "DLC2RR02" && a_event->stage == 200) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 999, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}

			if ((questID == "BYOHHouseFalkreath" || questID == "BYOHHouseHjaalmarch" || questID == "BYOHHousePale") && a_event->stage == 100) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_RequestOwnershipCC", RE::BSFixedString(), 999, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
				return EventResult::kContinue;
			}
		}
		return EventResult::kContinue;
	}
}