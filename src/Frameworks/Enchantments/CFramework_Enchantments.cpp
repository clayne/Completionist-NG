#include "Serialization.hpp"
#include "CFramework_Enchantments.hpp"
#include "Frameworks/FrameworkMaster.hpp"
#include "Internal Utility/ScriptObject.hpp"

#undef AddForm

namespace CFramework_EnchantmentsManager {

	void CHandler::InstallFramework() {

		CFramework_AEnchantments_V::CHandler::InstallFramework();
		CFramework_AEnchantments_P::CHandler::InstallFramework();

		CFramework_WEnchantments_V::CHandler::InstallFramework();
		CFramework_WEnchantments_P::CHandler::InstallFramework();
	}

	void CHandler::UpdateFoundForms() {

		CFramework_AEnchantments_V::CHandler::UpdateFoundForms();
		CFramework_AEnchantments_P::CHandler::UpdateFoundForms();

		CFramework_WEnchantments_V::CHandler::UpdateFoundForms();
		CFramework_WEnchantments_P::CHandler::UpdateFoundForms();
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Vanilla (Armor Enchantments)
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_AEnchantments_V {

	using namespace CFramework_Master;

	// clang-format off

	constexpr Serialization::FormArray SkyrimForms = {
	0x10FB70,0x10FB71,0x10FB7E,0x10FB84,0x10FB72,0x10FB73,0x10FB74,0x10FB75,
	0x10FB77,0x10FB78,0x10FB79,0x10FB7A,0x10FB7B,0x10FB7C,0x10FB7F,0x10FB80,
	0x10FB81,0x10FB82,0x10FB83,0x10FB85,0x10FB87,0x10FB88,0x10FB89,0x10FB76,
	0x10FB7D,0x10FB86,0x10FB8A,0x10FB8B,0x10FB8C,0x10FB8D,0x10FB8E,0x10FB8F,
	0x10FB90,
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	inline uint32_t EntriesTotal;
	inline uint32_t EntriesFound;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		CHandler::Sink();
		CHandler::InjectAndCompileData();		
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Singleton ) ----------
	//---------------------------------------------------

	auto CHandler::GetSingleton() -> CHandler* {
		static CHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void CHandler::Sink() {
		auto ui = RE::UI::GetSingleton();
		ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(CHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Menu Open ) --------------
	//---------------------------------------------------

	auto CHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event->menuName == RE::JournalMenu::MENU_NAME && a_event->opening) {
			for (auto i = 0; i < FormArray.size(); i++) {

				if (auto* enchantment = static_cast<RE::EnchantmentItem*>(FormArray[i]); enchantment) {
					if (auto known = enchantment->GetKnown(); known) {
						BoolArray[i] = true;
						FoundItemData.AddForm(enchantment);
					}
				}
			}
			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CFramework_AEnchantments_V::SkyrimForms, "Skyrim.esm");
		CFramework_AEnchantments_V::Data.Populate(NameArray, FormArray, BoolArray, TextArray);
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (auto* enchantment = static_cast<RE::EnchantmentItem*>(FormArray[i]); enchantment) {
				if (auto known = enchantment->GetKnown(); known || FoundItemData.HasForm(enchantment->GetFormID())) {
					BoolArray[i] = true;
					FoundItemData.AddForm(enchantment);
				}
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM is Entry Complete ) --
	//---------------------------------------------------

	uint32_t CHandler::IsOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			return uint32_t(BoolArray[std::distance(NameArray.begin(), t_pos)]);
		}
		return -1;
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Set Entry Complete ) -
	//---------------------------------------------------

	void CHandler::SetOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			auto b_pos = std::distance(NameArray.begin(), t_pos);

			if (BoolArray.at(b_pos)) {
				BoolArray.at(b_pos) = false;

				FoundItemData.RemoveForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.RemoveForm(var);
					}
				}
			}
			else {
				BoolArray.at(b_pos) = true;
				FoundItemData.AddForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.AddForm(var);
					}
				}
			}

			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Summermyst (Armor Enchantments)
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_AEnchantments_P {

	using namespace CFramework_Master;

	// clang-format off

	const char* pname = "Summermyst - Enchantments of Skyrim.esp";

	constexpr Serialization::FormArray SummermystForms = {
	0x051266,0x0512AD,0x0512B5,0x0512CA,0x0512C3,0x0512BC,0x3473E3,0x051552,
	0x05128B,0x1E9CFF,0x051493,0x328D7F,0x328D81,0x393519,0x051513,0x3892DD,
	0x0512FF,0x051303,0x3841AC,0x3892C8,0x051368,0x0513CE,0x05155C,0x051278,
	0x051291,0x0514ED,0x3841A3,0x3841A8,0x38419E,0x2A5326,0x3892CC,0x328D91,
	0x051347,0x0513C1,0x1EEE21,0x1EEE1F,0x32DEB3,0x3892D6,0x051583,0x0512A5,
	0x3841B1,0x3892B8,0x3892BC,0x05139F,0x051500,0x39D738,0x328D95,0x05135F,
	0x051544,0x051362,0x051470,0x0514E1,0x05151B,0x0513A7,0x3473ED,0x32DEB9,
	0x3422D1,0x051328,0x051319,0x05126A,0x0B9EEF,0x1E9D01,0x193B1B,0x3892CA,
	0x051284,0x051536,0x38E40C,0x38E410,0x0513D6,0x051524,0x356785,
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	inline uint32_t EntriesTotal;
	inline uint32_t EntriesFound;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		if (const auto* Mod = RE::TESDataHandler::GetSingleton()->LookupLoadedModByName(pname); Mod) {
			CHandler::Sink();
			CHandler::InjectAndCompileData();
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Singleton ) ----------
	//---------------------------------------------------

	auto CHandler::GetSingleton() -> CHandler* {
		static CHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void CHandler::Sink() {
		auto ui = RE::UI::GetSingleton();
		ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(CHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Menu Open ) --------------
	//---------------------------------------------------

	auto CHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event->menuName == RE::JournalMenu::MENU_NAME && a_event->opening) {
			for (auto i = 0; i < FormArray.size(); i++) {

				if (auto* enchantment = static_cast<RE::EnchantmentItem*>(FormArray[i]); enchantment) {
					if (auto known = enchantment->GetKnown(); known) {
						BoolArray[i] = true;
						FoundItemData.AddForm(enchantment);
					}
				}
			}
			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CFramework_AEnchantments_P::SummermystForms, pname);
		CFramework_AEnchantments_P::Data.Populate(NameArray, FormArray, BoolArray, TextArray);
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (auto* enchantment = static_cast<RE::EnchantmentItem*>(FormArray[i]); enchantment) {
				if (auto known = enchantment->GetKnown(); known || FoundItemData.HasForm(enchantment->GetFormID())) {
					BoolArray[i] = true;
					FoundItemData.AddForm(enchantment);
				}
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM is Entry Complete ) --
	//---------------------------------------------------

	uint32_t CHandler::IsOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			return uint32_t(BoolArray[std::distance(NameArray.begin(), t_pos)]);
		}
		return -1;
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Set Entry Complete ) -
	//---------------------------------------------------

	void CHandler::SetOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			auto b_pos = std::distance(NameArray.begin(), t_pos);

			if (BoolArray.at(b_pos)) {
				BoolArray.at(b_pos) = false;

				FoundItemData.RemoveForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.RemoveForm(var);
					}
				}
			}
			else {
				BoolArray.at(b_pos) = true;
				FoundItemData.AddForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.AddForm(var);
					}
				}
			}

			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Vanilla (Weapon Enchantments)
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_WEnchantments_V {

	using namespace CFramework_Master;

	// clang-format off

	constexpr Serialization::FormArray SkyrimForms = {
	0x10FB91,0x10FB9D,0x10FB92,0x10FB93,0x10FB94,0x10FB95,0x10FB96,0x10FB97,
	0x10FB98,0x10FB99,0x10FB9A,0x10FB9B,0x10FB9C,
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	inline uint32_t EntriesTotal;
	inline uint32_t EntriesFound;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		CHandler::Sink();
		CHandler::InjectAndCompileData();
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Singleton ) ----------
	//---------------------------------------------------

	auto CHandler::GetSingleton() -> CHandler* {
		static CHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void CHandler::Sink() {
		auto ui = RE::UI::GetSingleton();
		ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(CHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Menu Open ) --------------
	//---------------------------------------------------

	auto CHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event->menuName == RE::JournalMenu::MENU_NAME && a_event->opening) {
			for (auto i = 0; i < FormArray.size(); i++) {

				if (auto* enchantment = static_cast<RE::EnchantmentItem*>(FormArray[i]); enchantment) {
					if (auto known = enchantment->GetKnown(); known) {
						BoolArray[i] = true;
						FoundItemData.AddForm(enchantment);
					}
				}
			}
			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CFramework_WEnchantments_V::SkyrimForms, "Skyrim.esm");
		CFramework_WEnchantments_V::Data.Populate(NameArray, FormArray, BoolArray, TextArray);
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (auto* enchantment = static_cast<RE::EnchantmentItem*>(FormArray[i]); enchantment) {
				if (auto known = enchantment->GetKnown(); known || FoundItemData.HasForm(enchantment->GetFormID())) {
					BoolArray[i] = true;
					FoundItemData.AddForm(enchantment);
				}
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM is Entry Complete ) --
	//---------------------------------------------------

	uint32_t CHandler::IsOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			return uint32_t(BoolArray[std::distance(NameArray.begin(), t_pos)]);
		}
		return -1;
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Set Entry Complete ) -
	//---------------------------------------------------

	void CHandler::SetOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			auto b_pos = std::distance(NameArray.begin(), t_pos);

			if (BoolArray.at(b_pos)) {
				BoolArray.at(b_pos) = false;

				FoundItemData.RemoveForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.RemoveForm(var);
					}
				}
			}
			else {
				BoolArray.at(b_pos) = true;
				FoundItemData.AddForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.AddForm(var);
					}
				}
			}

			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------ Summermyst (Weapon Enchantments)
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

namespace CFramework_WEnchantments_P {

	using namespace CFramework_Master;

	// clang-format off

	const char* pname = "Summermyst - Enchantments of Skyrim.esp";

	constexpr Serialization::FormArray SummermystForms = {
	0x0510DC,0x0510E0,0x0513F8,0x0511F4,0x051432,0x05143E,0x05143F,0x05143A,
	0x05143B,0x051218,0x051104,0x051177,0x051132,0x05150B,0x051188,0x0511CB,
	0x0513FF,0x05118E,0x05119D,0x0510DA,0x051157,0x0511D6,0x051229,0x0511FE,
	0x051241,0x05115E,0x05110B,0x0511C4,0x0511A7,0x0510ED,0x05117E,0x05112A,
	0x051208,0x05142A,0x051221,0x05122E,0x05125A,0x0513EF,0x0510F1,0x05140E,
	0x25E4D2,0x051213,0x0511E9,0x051242,0x05141E,0x051150,0x0510F9,0x25E4D5,
	0x05115F,0x051115,0x0510FC,0x0511AE,
	};

	// clang-format on

	Serialization::CompletionistData Data;

	std::vector<std::string> NameArray{};
	std::vector<std::string> TextArray{};
	std::vector<RE::TESForm*> FormArray{};
	std::vector<bool> BoolArray{};

	inline ScriptObjectPtr  MCMScript;

	inline uint32_t EntriesTotal;
	inline uint32_t EntriesFound;

	//---------------------------------------------------
	//-- Framework Functions ( Install Framework ) ------
	//---------------------------------------------------

	void CHandler::InstallFramework() {

		if (const auto* Mod = RE::TESDataHandler::GetSingleton()->LookupLoadedModByName(pname); Mod) {
			CHandler::Sink();
			CHandler::InjectAndCompileData();
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Get Singleton ) ----------
	//---------------------------------------------------

	auto CHandler::GetSingleton() -> CHandler* {
		static CHandler singleton;
		return std::addressof(singleton);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Sink Event ) -------------
	//---------------------------------------------------

	void CHandler::Sink() {
		auto ui = RE::UI::GetSingleton();
		ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(CHandler::GetSingleton()));
	}

	//---------------------------------------------------
	//-- Framework Events ( On Menu Open ) --------------
	//---------------------------------------------------

	auto CHandler::ProcessEvent(RE::MenuOpenCloseEvent const* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> RE::BSEventNotifyControl {

		if (a_event->menuName == RE::JournalMenu::MENU_NAME && a_event->opening) {
			for (auto i = 0; i < FormArray.size(); i++) {

				if (auto* enchantment = static_cast<RE::EnchantmentItem*>(FormArray[i]); enchantment) {
					if (auto known = enchantment->GetKnown(); known) {
						BoolArray[i] = true;
						FoundItemData.AddForm(enchantment);
					}
				}
			}
			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
		return EventResult::kContinue;
	}

	//---------------------------------------------------
	//-- Framework Functions ( Form Injection ) ---------
	//---------------------------------------------------

	void CHandler::InjectAndCompileData() {

		auto handler = RE::TESDataHandler::GetSingleton();
		MCMScript = ScriptObject::FromForm(static_cast<RE::TESForm*>(handler->LookupForm(0x00800, "Completionist.esp")), "Completionist_MCMScript");

		Data.CompileFormArray(CFramework_WEnchantments_P::SummermystForms, pname);
		CFramework_WEnchantments_P::Data.Populate(NameArray, FormArray, BoolArray, TextArray);
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Update Found Forms ) -----
	//---------------------------------------------------

	void CHandler::UpdateFoundForms() {

		for (auto i = 0; i < FormArray.size(); i++) {
			if (auto* enchantment = static_cast<RE::EnchantmentItem*>(FormArray[i]); enchantment) {
				if (auto known = enchantment->GetKnown(); known || FoundItemData.HasForm(enchantment->GetFormID())) {
					BoolArray[i] = true;
					FoundItemData.AddForm(enchantment);
				}
			}
		}
		EntriesTotal = FormArray.size();
		EntriesFound = std::ranges::count(BoolArray, true);
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM is Entry Complete ) --
	//---------------------------------------------------

	uint32_t CHandler::IsOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			return uint32_t(BoolArray[std::distance(NameArray.begin(), t_pos)]);
		}
		return -1;
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Set Entry Complete ) -
	//---------------------------------------------------

	void CHandler::SetOptionCompleted(std::string a_name) {

		if (auto t_pos = std::find(NameArray.begin(), NameArray.end(), a_name); t_pos != NameArray.end()) {
			auto b_pos = std::distance(NameArray.begin(), t_pos);

			if (BoolArray.at(b_pos)) {
				BoolArray.at(b_pos) = false;

				FoundItemData.RemoveForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.RemoveForm(var);
					}
				}
			}
			else {
				BoolArray.at(b_pos) = true;
				FoundItemData.AddForm(FormArray.at(b_pos)->GetFormID());
				for (auto var : Data.GetAllVariations()) {
					if (Data.GetBase(var) == FormArray.at(b_pos)->GetFormID()) {
						FoundItemData.AddForm(var);
					}
				}
			}

			EntriesTotal = FormArray.size();
			EntriesFound = std::ranges::count(BoolArray, true);
		}
	}
}