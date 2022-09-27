#include "PatchMaster.hpp"

#include "Internal Utility/ScriptObject.hpp"
#include "Patches/Fishing/CFramework_Fishing.hpp"
#include "AdditionalHearthfireDolls/CFramework_AHD.hpp"
#include "BortherhoodOfOld/CFramework_BOO.hpp"
#include "Clockwork/CFramework_CLW.hpp"
#include "Falskaar/CFramework_FSK.hpp"
#include "FossilMining/CFramework_FOS.hpp"

namespace CPatch_Master {

	int PatchesInstalled;

	//---------------------------------------------------
	//-- Framework Functions ( Master Registration ) ----
	//---------------------------------------------------

	void PatchAPI::InstallPatches() {

		CPatch_AHD::CHandler::InstallFramework();
		CPatch_BOO::CHandler::InstallFramework();
		CPatch_CLW::CHandler::InstallFramework();
		CPatch_FSK::CHandler::InstallFramework();
		CPatch_FOS::CHandler::InstallFramework();

		// Finished
		RE::DebugMessageBox("Finished Installing Patches");
	}

	//---------------------------------------------------
	//-- Patches Functions ( Master Registration ) ------
	//---------------------------------------------------

	void PatchAPI::LoadallPatches() {

		CPatch_AHD::CHandler::UpdateFoundForms();
		CPatch_BOO::CHandler::UpdateFoundForms();
		CPatch_CLW::CHandler::UpdateFoundForms();
		CPatch_FSK::CHandler::UpdateFoundForms();
		CPatch_FOS::CHandler::UpdateFoundForms();
	}

	//---------------------------------------------------
	//-- Patches Functions ( Master Registration ) ------
	//---------------------------------------------------

	bool PatchAPI::ShouldDisplayMiscHeader(RE::StaticFunctionTag*) {

		return bool(PatchesInstalled);
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Total ) ---------
	//---------------------------------------------------

	uint32_t PatchAPI::GetEntries_TotalByID(uint32_t a_patchID) {
	
		if (a_patchID == CPatch_AHD::kItems || a_patchID == CPatch_AHD::KBooks || a_patchID == CPatch_AHD::KMapMa) { return CPatch_AHD::CHandler::ReturnEntriesInt(a_patchID, "Total"); }
		if (a_patchID == CPatch_BOO::kItems || a_patchID == CPatch_BOO::KBooks || a_patchID == CPatch_BOO::KMapMa) { return CPatch_BOO::CHandler::ReturnEntriesInt(a_patchID, "Total"); }
		if (a_patchID == CPatch_CLW::kItems || a_patchID == CPatch_CLW::KBooks || a_patchID == CPatch_CLW::KMapMa) { return CPatch_CLW::CHandler::ReturnEntriesInt(a_patchID, "Total"); }
		if (a_patchID == CPatch_FSK::kItems || a_patchID == CPatch_FSK::KBooks || a_patchID == CPatch_FSK::KMapMa) { return CPatch_FSK::CHandler::ReturnEntriesInt(a_patchID, "Total"); }
		if (a_patchID == CPatch_FOS::kItmL1 || a_patchID == CPatch_FOS::kItmL2 || a_patchID == CPatch_FOS::kItmL3) { return CPatch_FOS::CHandler::ReturnEntriesInt(a_patchID, "Total"); }
		
		switch (a_patchID) {

		default:
			return -1;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Found ) ---------
	//---------------------------------------------------

	uint32_t PatchAPI::GetEntries_FoundByID(uint32_t a_patchID) {

		if (a_patchID == CPatch_AHD::kItems || a_patchID == CPatch_AHD::KBooks || a_patchID == CPatch_AHD::KMapMa) { return CPatch_AHD::CHandler::ReturnEntriesInt(a_patchID, "Found"); }
		if (a_patchID == CPatch_BOO::kItems || a_patchID == CPatch_BOO::KBooks || a_patchID == CPatch_BOO::KMapMa) { return CPatch_BOO::CHandler::ReturnEntriesInt(a_patchID, "Found"); }
		if (a_patchID == CPatch_CLW::kItems || a_patchID == CPatch_CLW::KBooks || a_patchID == CPatch_CLW::KMapMa) { return CPatch_CLW::CHandler::ReturnEntriesInt(a_patchID, "Found"); }
		if (a_patchID == CPatch_FSK::kItems || a_patchID == CPatch_FSK::KBooks || a_patchID == CPatch_FSK::KMapMa) { return CPatch_FSK::CHandler::ReturnEntriesInt(a_patchID, "Found"); }
		if (a_patchID == CPatch_FOS::kItmL1 || a_patchID == CPatch_FOS::kItmL2 || a_patchID == CPatch_FOS::kItmL3) { return CPatch_FOS::CHandler::ReturnEntriesInt(a_patchID, "Found"); }
		
		switch (a_patchID) {

		default:
			return -1;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Forms ) ---------
	//---------------------------------------------------

	std::vector<RE::TESForm*> PatchAPI::GetFormArrayByID(uint32_t a_patchID) {

		std::vector<RE::TESForm*> Null;

		if (a_patchID == CPatch_AHD::kItems || a_patchID == CPatch_AHD::KBooks || a_patchID == CPatch_AHD::KMapMa) { return CPatch_AHD::CHandler::ReturnEntriesForm(a_patchID); }
		if (a_patchID == CPatch_BOO::kItems || a_patchID == CPatch_BOO::KBooks || a_patchID == CPatch_BOO::KMapMa) { return CPatch_BOO::CHandler::ReturnEntriesForm(a_patchID); }
		if (a_patchID == CPatch_CLW::kItems || a_patchID == CPatch_CLW::KBooks || a_patchID == CPatch_CLW::KMapMa) { return CPatch_CLW::CHandler::ReturnEntriesForm(a_patchID); }
		if (a_patchID == CPatch_FSK::kItems || a_patchID == CPatch_FSK::KBooks || a_patchID == CPatch_FSK::KMapMa) { return CPatch_FSK::CHandler::ReturnEntriesForm(a_patchID); }
		if (a_patchID == CPatch_FOS::kItmL1 || a_patchID == CPatch_FOS::kItmL2 || a_patchID == CPatch_FOS::kItmL3) { return CPatch_FOS::CHandler::ReturnEntriesForm(a_patchID); }

		switch (a_patchID) {

		default:
			return Null;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Names ) ---------
	//---------------------------------------------------

	std::vector<std::string> PatchAPI::GetNameArrayByID(uint32_t a_patchID) {

		std::vector<std::string> Null;

		if (a_patchID == CPatch_AHD::kItems || a_patchID == CPatch_AHD::KBooks || a_patchID == CPatch_AHD::KMapMa) { return CPatch_AHD::CHandler::ReturnEntriesString(a_patchID, "Name"); }
		if (a_patchID == CPatch_BOO::kItems || a_patchID == CPatch_BOO::KBooks || a_patchID == CPatch_BOO::KMapMa) { return CPatch_BOO::CHandler::ReturnEntriesString(a_patchID, "Name"); }
		if (a_patchID == CPatch_CLW::kItems || a_patchID == CPatch_CLW::KBooks || a_patchID == CPatch_CLW::KMapMa) { return CPatch_CLW::CHandler::ReturnEntriesString(a_patchID, "Name"); }
		if (a_patchID == CPatch_FSK::kItems || a_patchID == CPatch_FSK::KBooks || a_patchID == CPatch_FSK::KMapMa) { return CPatch_FSK::CHandler::ReturnEntriesString(a_patchID, "Name"); }
		if (a_patchID == CPatch_FOS::kItmL1 || a_patchID == CPatch_FOS::kItmL2 || a_patchID == CPatch_FOS::kItmL3) { return CPatch_FOS::CHandler::ReturnEntriesString(a_patchID, "Name"); }

		switch (a_patchID) {

		default:
			return Null;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Texts ) ---------
	//---------------------------------------------------

	std::vector<std::string> PatchAPI::GetTextArrayByID(uint32_t a_patchID) {

		std::vector<std::string> Null;

		if (a_patchID == CPatch_AHD::kItems || a_patchID == CPatch_AHD::KBooks || a_patchID == CPatch_AHD::KMapMa) { return CPatch_AHD::CHandler::ReturnEntriesString(a_patchID, "Text"); }
		if (a_patchID == CPatch_BOO::kItems || a_patchID == CPatch_BOO::KBooks || a_patchID == CPatch_BOO::KMapMa) { return CPatch_BOO::CHandler::ReturnEntriesString(a_patchID, "Text"); }
		if (a_patchID == CPatch_CLW::kItems || a_patchID == CPatch_CLW::KBooks || a_patchID == CPatch_CLW::KMapMa) { return CPatch_CLW::CHandler::ReturnEntriesString(a_patchID, "Text"); }
		if (a_patchID == CPatch_FSK::kItems || a_patchID == CPatch_FSK::KBooks || a_patchID == CPatch_FSK::KMapMa) { return CPatch_FSK::CHandler::ReturnEntriesString(a_patchID, "Text"); }
		if (a_patchID == CPatch_FOS::kItmL1 || a_patchID == CPatch_FOS::kItmL2 || a_patchID == CPatch_FOS::kItmL3) { return CPatch_FOS::CHandler::ReturnEntriesString(a_patchID, "Text"); }
		
		switch (a_patchID) {

		default:
			return Null;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( Getter - Bools ) ---------
	//---------------------------------------------------

	std::vector<bool> PatchAPI::GetBoolArrayByID(uint32_t a_patchID) {
		
		std::vector<bool> Null;

		if (a_patchID == CPatch_AHD::kItems || a_patchID == CPatch_AHD::KBooks || a_patchID == CPatch_AHD::KMapMa) { return CPatch_AHD::CHandler::ReturnEntriesBool(a_patchID); }
		if (a_patchID == CPatch_BOO::kItems || a_patchID == CPatch_BOO::KBooks || a_patchID == CPatch_BOO::KMapMa) { return CPatch_BOO::CHandler::ReturnEntriesBool(a_patchID); }
		if (a_patchID == CPatch_CLW::kItems || a_patchID == CPatch_CLW::KBooks || a_patchID == CPatch_CLW::KMapMa) { return CPatch_CLW::CHandler::ReturnEntriesBool(a_patchID); }
		if (a_patchID == CPatch_FSK::kItems || a_patchID == CPatch_FSK::KBooks || a_patchID == CPatch_FSK::KMapMa) { return CPatch_FSK::CHandler::ReturnEntriesBool(a_patchID); }
		if (a_patchID == CPatch_FOS::kItmL1 || a_patchID == CPatch_FOS::kItmL2 || a_patchID == CPatch_FOS::kItmL3) { return CPatch_FOS::CHandler::ReturnEntriesBool(a_patchID); }
		
		switch (a_patchID) {

		default:
			return Null;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Getter - Status ) ----
	//---------------------------------------------------

	uint32_t PatchAPI::IsOptionCompleted(uint32_t a_patchID, std::string a_name) {

		if (a_patchID == CPatch_AHD::kItems || a_patchID == CPatch_AHD::KBooks) { return CPatch_AHD::CHandler::IsOptionCompleted(a_name); }
		if (a_patchID == CPatch_BOO::kItems || a_patchID == CPatch_BOO::KBooks) { return CPatch_BOO::CHandler::IsOptionCompleted(a_name); }
		if (a_patchID == CPatch_CLW::kItems || a_patchID == CPatch_CLW::KBooks) { return CPatch_CLW::CHandler::IsOptionCompleted(a_name); }
		if (a_patchID == CPatch_FSK::kItems || a_patchID == CPatch_FSK::KBooks) { return CPatch_FSK::CHandler::IsOptionCompleted(a_name); }
		if (a_patchID == CPatch_FOS::kItmL1 || a_patchID == CPatch_FOS::kItmL2 || a_patchID == CPatch_FOS::kItmL3) { return CPatch_FOS::CHandler::IsOptionCompleted(a_name); }
		
		switch (a_patchID) {

		default:
			return -1;
		}
	}

	//---------------------------------------------------
	//-- Framework Functions ( MCM Setter - Status ) ----
	//---------------------------------------------------

	void PatchAPI::SetOptionCompleted(uint32_t a_patchID, std::string a_name) {

		if (a_patchID == CPatch_AHD::kItems || a_patchID == CPatch_AHD::KBooks) { CPatch_AHD::CHandler::SetOptionCompleted(a_name); return; }
		if (a_patchID == CPatch_BOO::kItems || a_patchID == CPatch_BOO::KBooks) { CPatch_BOO::CHandler::SetOptionCompleted(a_name); return; }
		if (a_patchID == CPatch_CLW::kItems || a_patchID == CPatch_CLW::KBooks) { CPatch_CLW::CHandler::SetOptionCompleted(a_name); return; }
		if (a_patchID == CPatch_FSK::kItems || a_patchID == CPatch_FSK::KBooks) { CPatch_FSK::CHandler::SetOptionCompleted(a_name); return; }
		if (a_patchID == CPatch_FOS::kItmL1 || a_patchID == CPatch_FOS::kItmL2 || a_patchID == CPatch_FOS::kItmL3) { CPatch_FOS::CHandler::SetOptionCompleted(a_name); return; }
		
		switch (a_patchID) {

		default:
			break;
		}
	}
}
