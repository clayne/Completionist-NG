#pragma once

#include <SKSE\API.h>

namespace MenuEvents
{
	using EventResult = RE::BSEventNotifyControl;
	class MenuHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		static MenuHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};

	void Install();
}

namespace BookEvents
{
	using EventResult = RE::BSEventNotifyControl;
	class BookHandler : public RE::BSTEventSink<RE::BooksRead::Event>
	{
	public:
		static BookHandler* GetSingleton();
		static void							Sink();
		virtual RE::BSEventNotifyControl	ProcessEvent(RE::BooksRead::Event const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::BooksRead::Event>* a_eventSource) override;
	};

	void Install();
}
