#include "PCH.h"
#include "Radiant Quests Manager.hpp"
#include "Quests_Misc.hpp"

using namespace Quest_Manager;

namespace MiscQuests
{
	EventResult ScriptEventHandler::ProcessEvent(const RE::TESQuestStartStopEvent* a_event, RE::BSTEventSource<RE::TESQuestStartStopEvent>*) {

		if (!a_event || !a_event->started) { return EventResult::kContinue; }

		if (const auto quest = RE::TESForm::LookupByID<RE::TESQuest>(a_event->formID)) {
			auto questID = std::string(quest->GetFormEditorID());

			if (questID != "FavorJobsDrunksScene") { return EventResult::kContinue; }

			for (const auto& alias : quest->aliases) {

				if (!alias || alias->aliasName != "Drunk") { break; }
					
				auto reference = static_cast<RE::BGSRefAlias*>(alias);
				if (!reference) { return EventResult::kContinue; }

				auto drunkrefr = reference->GetActorReference()->GetActorBase()->GetFormID();
				if (!drunkrefr) { return EventResult::kContinue; }

				RadiantQuestManager::ProcessFormID(drunkrefr, "FavorJobsDrunks");
				RE::DebugMessageBox("Updating :)");
			}
		}
		return EventResult::kContinue;
	}

	EventResult ScriptEventHandler::ProcessEvent(const RE::TESQuestStageEvent* a_event, RE::BSTEventSource<RE::TESQuestStageEvent>*) {
		
		if (!a_event) { return EventResult::kContinue; }

		if (const auto quest = RE::TESForm::LookupByID<RE::TESQuest>(a_event->formID)) {
			auto questID = std::string(quest->GetFormEditorID());

			if (questID == "ccBGSSSE001_Radiant_1" && a_event->stage == 200) {
				if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_Fishing1")) {
					global->value += 1;
					return EventResult::kContinue;
				}
			}

			if (questID == "ccBGSSSE001_Radiant_2" && a_event->stage == 200) {
				if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_Fishing2")) {
					global->value += 1;
					return EventResult::kContinue;
				}
			}

			if (questID == "ccBGSSSE001_Radiant_3" && a_event->stage == 200) {
				if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_Fishing3")) {
					global->value += 1;
					return EventResult::kContinue;
				}
			}

			if (questID == "DBrecurring" && a_event->stage == 200) {
				if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_DBrecurring")) {
					global->value += 1;
					return EventResult::kContinue;
				}
			}

			if (questID == "dunSleepingTreeCampQST" && a_event->stage == 3) {
				if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>("Completionist_dunSleepingTreeCampQST")) {
					global->value += 1;
					return EventResult::kContinue;
				}
			}

			if ((questID == "CWSiegeObj" || questID == "CWFortSiegeFort") && a_event->stage == 9000) {
				RadiantQuestManager::ProcessFormID(uint32_t(0), questID);
				return EventResult::kContinue;
			}
		}
		return EventResult::kContinue;
	}
}

