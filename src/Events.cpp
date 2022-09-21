#include "Events.hpp"
#include "Papyrus.hpp"
#include "Internal Utility/InventoryMode.hpp"

using namespace BookEvents;
using namespace MenuEvents;

namespace MenuEvents {

	auto MenuHandler::GetSingleton() -> MenuHandler* {
		static MenuHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------

	void MenuHandler::Sink() {
		auto ui = RE::UI::GetSingleton();
		ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(MenuHandler::GetSingleton()));
	}

	//---------------------------------------------------

	auto MenuHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event == nullptr) {
			return RE::BSEventNotifyControl::kContinue;
		}

		if (a_event->menuName == RE::BookMenu::MENU_NAME && a_event->opening) {

			if (auto* normalbook = RE::BookMenu::GetTargetForm(); normalbook) {
				SKSE::ModCallbackEvent modEvent{ "Completionist_BookEvent", normalbook->GetFullName(), 0.0f, nullptr };
				auto modCallback = SKSE::GetModCallbackEventSource();
				modCallback->SendEvent(&modEvent);
			}
			return RE::BSEventNotifyControl::kContinue;
		}

		if (a_event->menuName == RE::MapMenu::MENU_NAME && a_event->opening) {
			SKSE::ModCallbackEvent modEvent{ "Completionist_MapEvent", RE::BSFixedString(), 0.0f, nullptr };
			auto modCallback = SKSE::GetModCallbackEventSource();
			modCallback->SendEvent(&modEvent);
			return RE::BSEventNotifyControl::kContinue;
		}
		return RE::BSEventNotifyControl::kContinue;
	}

	//---------------------------------------------------

	void Install() {
		MenuHandler::Sink();
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------

namespace BookEvents {

	auto BookHandler::GetSingleton() -> BookHandler* {
		static BookHandler Tomesingleton;
		return std::addressof(Tomesingleton);
	}

	//---------------------------------------------------

	void BookHandler::Sink() {
		RE::BooksRead::GetEventSource()->AddEventSink(BookHandler::GetSingleton());
	}

	//---------------------------------------------------

	auto BookHandler::ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) -> RE::BSEventNotifyControl {
		
		if (a_event == nullptr) { return RE::BSEventNotifyControl::kContinue;}

		if (auto* spelltome = a_event->book; spelltome) {
			SKSE::ModCallbackEvent modEvent{ "Completionist_TomeEvent", spelltome->GetFullName(), 0.0f, nullptr };
			auto modCallback = SKSE::GetModCallbackEventSource();
			modCallback->SendEvent(&modEvent);
		}
		return RE::BSEventNotifyControl::kContinue;
	}

	//---------------------------------------------------

	void Install() {
		BookHandler::Sink();
	}
}
