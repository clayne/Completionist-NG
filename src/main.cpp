#include "Serialization.hpp"
#include "Papyrus.hpp"
#include "Hooks.hpp"
#include "Events.hpp"
#include "Radiant Quest Handler/Radiant Quests Manager.hpp"
#include "Internal Utility/InventoryMode.hpp"
#include "Frameworks/FrameworkMaster.hpp"

using namespace Completionist;

const SKSE::MessagingInterface* g_messaging = nullptr;
const SKSE::LoadInterface* g_LoadInterface = nullptr;
const SKSE::QueryInterface* g_QueryInterface = nullptr;

static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message)
{
	switch (message->type)
	{
	case SKSE::MessagingInterface::kDataLoaded:

		MenuEvents::Install();
		BookEvents::Install();
		SKSE_Hooks::Install();
		Quest_Manager::Install();
		CFramework_Master::FrameworkAPI::Register();
		Completionist_Inventory::FunctionHolder::Register();
		Papyrus::Register();
		break;

	case SKSE::MessagingInterface::kNewGame:
		break;

	case SKSE::MessagingInterface::kPreLoadGame:
		break;

	case SKSE::MessagingInterface::kPostLoadGame:
		CFramework_Master::FrameworkAPI::Framework_Load();
		break;

	case SKSE::MessagingInterface::kPostLoad:
		CFramework_Master::FrameworkAPI::Framework_Load();
		break;

	case SKSE::MessagingInterface::kPostPostLoad:
		CFramework_Master::FrameworkAPI::Framework_Load();
		break;
	}
}

DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
#ifndef NDEBUG
	while (!IsDebuggerPresent()) { Sleep(100); }
#endif

	DKUtil::Logger::Init(Plugin::NAME, REL::Module::get().version().string());
	SKSE::Init(a_skse);

	INFO("{} v{} loaded", Plugin::NAME, Plugin::Version);

	g_messaging = reinterpret_cast<SKSE::MessagingInterface*>(a_skse->QueryInterface(SKSE::LoadInterface::kMessaging));
	if (!g_messaging)
	{
		INFO("Failed to load messaging interface! This error is fatal, plugin will not load.");
		return false;
	}

	auto papyrus = reinterpret_cast<SKSE::PapyrusInterface*>(a_skse->QueryInterface(SKSE::LoadInterface::kPapyrus));
	if (!papyrus)
	{
		INFO("Failed to load scripting interface! This error is fatal, plugin will not load.");
		return false;
	}

	SKSE::Init(a_skse);
	SKSE::AllocTrampoline(256);

	g_messaging->RegisterListener("SKSE", SKSEMessageHandler);

	const auto* serialization = SKSE::GetSerializationInterface();
	serialization->SetUniqueID(Serialization::kHeader);
	serialization->SetSaveCallback(Serialization::SaveCallback);
	serialization->SetLoadCallback(Serialization::LoadCallback);
	serialization->SetRevertCallback(Serialization::RevertCallback);
	return true;
}
