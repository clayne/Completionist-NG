#include "PCH.h"
#include "Quests_Bounty.hpp"

namespace BountyQuests
{
	EventResult ScriptEventHandler::ProcessEvent(const RE::TESQuestStageEvent* a_event, RE::BSTEventSource<RE::TESQuestStageEvent>*) {
		
		if (!a_event) { return EventResult::kContinue; }

		if (const auto quest = RE::TESForm::LookupByID<RE::TESQuest>(a_event->formID)) {

			auto questID = std::string(quest->GetFormEditorID());

			if (IsValidQuest(questID, "BQ01") && a_event->stage == 200) {
				if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_BountyBQ01")) {
					global->value += 1;
					return EventResult::kContinue;
				}
			}

			if (IsValidQuest(questID, "BQ02") && a_event->stage == 200) {
				if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_BountyBQ02")) {
					global->value += 1;
					return EventResult::kContinue;
				}
			}

			if (IsValidQuest(questID, "BQ03") && a_event->stage == 200) {
				if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_BountyBQ03")) {
					global->value += 1;
					return EventResult::kContinue;
				}
			}

			if (IsValidQuest(questID, "BQ04") && a_event->stage == 200) {
				if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_BountyBQ04")) {
					global->value += 1;
					return EventResult::kContinue;
				}
			}
		}
		return EventResult::kContinue;
	}

	bool ScriptEventHandler::IsValidQuest(std::string questID, std::string checkID) {

		if (const auto* modInfo = RE::TESDataHandler::GetSingleton()->LookupModByName("Favor Quests Seperated.esp"); !modInfo) {
			return questID == checkID;
		}

		if (checkID == "BQ01") {
			return
				questID == checkID ||
				questID == "BQ01Eastmarch" ||
				questID == "BQ01Falkreath" ||
				questID == "BQ01Haafingar" ||
				questID == "BQ01Hjaalmarch" ||
				questID == "BQ01Pale" ||
				questID == "BQ01Reach" ||
				questID == "BQ01Rift" ||
				questID == "BQ01Whiterun" ||
				questID == "BQ01Winterhold";
		}

		else if (checkID == "BQ02") {
			return
				questID == checkID ||
				questID == "BQ02Eastmarch" ||
				questID == "BQ02Falkreath" ||
				questID == "BQ02Haafingar" ||
				questID == "BQ02Hjaalmarch" ||
				questID == "BQ02Pale" ||
				questID == "BQ02Reach" ||
				questID == "BQ02Rift" ||
				questID == "BQ02Whiterun" ||
				questID == "BQ02Winterhold";
		}

		else if (checkID == "BQ03") {
			return
				questID == checkID ||
				questID == "BQ03Eastmarch" ||
				questID == "BQ03Falkreath" ||
				questID == "BQ03Haafingar" ||
				questID == "BQ03Hjaalmarch" ||
				questID == "BQ03Pale" ||
				questID == "BQ03Reach" ||
				questID == "BQ03Rift" ||
				questID == "BQ03Whiterun" ||
				questID == "BQ03Winterhold";
		}

		else if (checkID == "BQ04") {
			return
				questID == checkID ||
				questID == "BQ04Eastmarch" ||
				questID == "BQ04Falkreath" ||
				questID == "BQ04Haafingar" ||
				questID == "BQ04Hjaalmarch" ||
				questID == "BQ04Pale" ||
				questID == "BQ04Reach" ||
				questID == "BQ04Rift" ||
				questID == "BQ04Whiterun" ||
				questID == "BQ04Winterhold";
		}
		return false;
	}
}
