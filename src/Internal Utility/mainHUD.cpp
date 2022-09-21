#include "Serialization.hpp"
#include "Frameworks/FrameworkMaster.hpp"

#include "mainHUD.hpp"
#include "ScriptObject.hpp"
#include "InventoryMode.hpp"

using namespace ScriptObject;
using namespace Inv_vars;

static RE::FormID a_form;
static RE::TESForm* a_base;

static std::string replacename;

namespace Completionist_MainHUD {

	void FunctionHolder::ProcessCrosshairReference(RE::HUDData* data) {

		if (auto CurrentRef = RE::CrosshairPickData::GetSingleton(); CurrentRef) {
			if (auto CurrentObj = CurrentRef->target.get(); CurrentObj) {
				a_base = CurrentObj.get()->GetBaseObject();
				a_form = a_base->GetFormID();
			}
		}

		if (!a_base || !a_form || !Completionist_Inventory::FunctionHolder::IsReady()) { return; }

		replacename = data->text.c_str();

		switch (a_base->GetFormType()) {
		case RE::FormType::AlchemyItem:
		{
			if (ItemIsCollected(a_form) && Inv_vars::Inv_Alchemy_Enabled_Found) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Alchemy_ColourString_Found, Inv_vars::Inv_CrosshairTag_Found);
				return;
			}
			else if (ItemIsCollectable(a_form) && Inv_vars::Inv_Alchemy_Enabled_New) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Alchemy_ColourString_New, Inv_vars::Inv_CrosshairTag_New);
				return;
			}
			return;
		}
		case RE::FormType::Ammo:
		{
			if (ItemIsCollected(a_form) && Inv_vars::Inv_Ammo_Enabled_Found) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Ammo_ColourString_Found, Inv_vars::Inv_CrosshairTag_Found);
				return;
			}
			else if (ItemIsCollectable(a_form) && Inv_vars::Inv_Ammo_Enabled_New) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Ammo_ColourString_New, Inv_vars::Inv_CrosshairTag_New);
				return;
			}
			return;
		}
		case RE::FormType::Armor:
		{
			if (ItemIsCollected(a_form) && Inv_vars::Inv_Armor_Enabled_Found) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Armor_ColourString_Found, Inv_vars::Inv_CrosshairTag_Found);
				return;
			}
			else if (ItemIsCollectable(a_form) && Inv_vars::Inv_Armor_Enabled_New) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Armor_ColourString_New, Inv_vars::Inv_CrosshairTag_New);
				return;
			}
			return;
		}
		case RE::FormType::Book:
		{
			if (ItemIsCollected(a_form) && Inv_vars::Inv_Books_Enabled_Found) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Books_ColourString_Found, Inv_vars::Inv_CrosshairTag_Found);
				return;
			}
			else if (ItemIsCollectable(a_form) && Inv_vars::Inv_Books_Enabled_New) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Books_ColourString_New, Inv_vars::Inv_CrosshairTag_New);
				return;
			}
			return;
		}
		case RE::FormType::Ingredient:
		{
			if (ItemIsCollected(a_form) && Inv_vars::Inv_Alchemy_Enabled_Found) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Alchemy_ColourString_Found, Inv_vars::Inv_CrosshairTag_Found);
				return;
			}
			else if (ItemIsCollectable(a_form) && Inv_vars::Inv_Alchemy_Enabled_New) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Alchemy_ColourString_New, Inv_vars::Inv_CrosshairTag_New);
				return;
			}
			return;
		}
		case RE::FormType::Weapon:
		{
			if (ItemIsCollected(a_form) && Inv_vars::Inv_Weapons_Enabled_Found) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Weapons_ColourString_Found, Inv_vars::Inv_CrosshairTag_Found);
				return;
			}
			else if (ItemIsCollectable(a_form) && Inv_vars::Inv_Weapons_Enabled_New) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Weapons_ColourString_New, Inv_vars::Inv_CrosshairTag_New);
				return;
			}
			return;
		}
		default:

			if (ItemIsCollected(a_form) && Inv_vars::Inv_Other_Enabled_Found) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Other_ColourString_Found, Inv_vars::Inv_CrosshairTag_Found);
				return;
			}
			else if (ItemIsCollectable(a_form) && Inv_vars::Inv_Other_Enabled_New) {
				data->text = fmt::format("{:s} <font color='{:s}'>{:s}</font>"sv, replacename, Inv_vars::Inv_Other_ColourString_New, Inv_vars::Inv_CrosshairTag_New);
				return;
			}
			return;
		}
	}

	bool FunctionHolder::ItemIsCollectable(RE::FormID a_formID) {

		return 
			Serialization::CompletionistData::CheckIsCollectable(a_formID) &&
			!CFramework_Master::FoundItemData.HasForm(a_formID);
	}

	bool FunctionHolder::ItemIsCollected(RE::FormID a_formID) {

		return CFramework_Master::FoundItemData.HasForm(a_formID);
	}
}