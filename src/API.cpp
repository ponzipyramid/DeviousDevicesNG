#include "API.h"

#include "DeviceReader.h"
#include "Expression.h"
#include "LibFunctions.h"
#include "Hider.h"

size_t DeviousDevicesAPI::DeviousDevicesAPI::GetVersion() const
{
    return DD_APIVERSION;
}

const std::map<RE::TESObjectARMO*, DeviousDevicesAPI::DeviceUnitPrototype>& DeviousDevicesAPI::DeviousDevicesAPI::GetDatabase() const
{
    return *(const std::map<RE::TESObjectARMO*, DeviceUnitPrototype>*)&DeviousDevices::DeviceReader::GetSingleton()->GetDatabase();
}

RE::TESObjectARMO* DeviousDevicesAPI::DeviousDevicesAPI::GetDeviceRender(RE::TESObjectARMO* a_invdevice) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetDeviceRender(a_invdevice);
}

RE::TESObjectARMO* DeviousDevicesAPI::DeviousDevicesAPI::GetDeviceInventory(RE::TESObjectARMO* a_renddevice) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetDeviceInventory(a_renddevice);
}
RE::TESForm* DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyForm(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, RE::TESForm* a_defvalue, int a_mode) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyForm(a_invdevice,a_propertyname,a_defvalue,a_mode);
}

int DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyInt(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_defvalue, int a_mode) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyInt(a_invdevice,a_propertyname,a_defvalue,a_mode);
}

float DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyFloat(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, float a_defvalue, int a_mode) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyFloat(a_invdevice,a_propertyname,a_defvalue,a_mode);
}

bool DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyBool(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, bool a_defvalue, int a_mode) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyBool(a_invdevice,a_propertyname,a_defvalue,a_mode);
}

std::string DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyString(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, std::string a_defvalue, int a_mode) const
{
    return std::string(DeviousDevices::DeviceReader::GetSingleton()->GetPropertyString(a_invdevice,a_propertyname,a_defvalue,a_mode));
}

std::vector<RE::TESForm*> DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyFormArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyFormArray(a_invdevice,a_propertyname,a_mode);
}

std::vector<int> DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyIntArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyIntArray(a_invdevice,a_propertyname,a_mode);
}

std::vector<float> DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyFloatArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyFloatArray(a_invdevice,a_propertyname,a_mode);
}

std::vector<bool> DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyBoolArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyBoolArray(a_invdevice,a_propertyname,a_mode);
}

std::vector<std::string> DeviousDevicesAPI::DeviousDevicesAPI::GetPropertyStringArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode) const
{
    return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyStringArray(a_invdevice,a_propertyname,a_mode);
}

bool DeviousDevicesAPI::DeviousDevicesAPI::ApplyExpression(RE::Actor* a_actor, const std::vector<float> a_expression, float a_strength, bool a_openMouth, int a_priority) const
{
    return DeviousDevices::ExpressionManager::GetSingleton()->ApplyExpression(a_actor,a_expression,a_strength,a_openMouth,a_priority);
}

bool DeviousDevicesAPI::DeviousDevicesAPI::ResetExpression(RE::Actor* a_actor, int a_priority) const
{
    return DeviousDevices::ExpressionManager::GetSingleton()->ResetExpression(a_actor,a_priority);
}

void DeviousDevicesAPI::DeviousDevicesAPI::UpdateGagExpression(RE::Actor* a_actor) const
{
    DeviousDevices::ExpressionManager::GetSingleton()->UpdateGagExpression(a_actor);
}

void DeviousDevicesAPI::DeviousDevicesAPI::ResetGagExpression(RE::Actor* a_actor) const
{
    DeviousDevices::ExpressionManager::GetSingleton()->ResetGagExpression(a_actor);
}

bool DeviousDevicesAPI::DeviousDevicesAPI::IsGagged(RE::Actor* a_actor) const
{
    return DeviousDevices::ExpressionManager::GetSingleton()->IsGagged(a_actor);
}

bool DeviousDevicesAPI::DeviousDevicesAPI::RegisterGagType(RE::BGSKeyword* a_keyword, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults) const
{
    return DeviousDevices::ExpressionManager::GetSingleton()->RegisterGagType(a_keyword,a_factions,a_defaults);
}

bool DeviousDevicesAPI::DeviousDevicesAPI::RegisterDefaultGagType(std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults) const
{
    return DeviousDevices::ExpressionManager::GetSingleton()->RegisterDefaultGagType(a_factions,a_defaults);
}

DeviousDevicesAPI::BondageState DeviousDevicesAPI::DeviousDevicesAPI::GetBondageState(RE::Actor* a_actor) const
{
    return (BondageState)DeviousDevices::LibFunctions::GetSingleton()->GetBondageState(a_actor);
}

bool DeviousDevicesAPI::DeviousDevicesAPI::IsDevice(RE::TESObjectARMO* a_obj) const
{
    return false;
}

bool DeviousDevicesAPI::DeviousDevicesAPI::ActorHasBlockingGag(RE::Actor* a_actor, RE::TESObjectARMO* a_gag) const
{
    return false;
}

void DeviousDevicesAPI::DeviousDevicesAPI::SetActorStripped(RE::Actor* a_actor, bool a_stripped, int a_armorfilter, int a_devicefilter) const
{
    DeviousDevices::DeviceHiderManager::GetSingleton()->SetActorStripped(a_actor,a_stripped,a_armorfilter,a_devicefilter);
}

bool DeviousDevicesAPI::DeviousDevicesAPI::IsActorStripped(RE::Actor* a_actor) const
{
    return DeviousDevices::DeviceHiderManager::GetSingleton()->IsActorStripped(a_actor);
}

bool DeviousDevicesAPI::DeviousDevicesAPI::IsValidForHide(RE::TESObjectARMO* a_armor) const
{
    return DeviousDevices::DeviceHiderManager::GetSingleton()->IsValidForHide(a_armor);
}

std::vector<RE::TESObjectARMO*> DeviousDevicesAPI::DeviousDevicesAPI::GetDevices(RE::Actor* a_actor, int a_mode, bool a_worn) const
{
    return DeviousDevices::LibFunctions::GetSingleton()->GetDevices(a_actor,a_mode,a_worn);
}

RE::TESObjectARMO* DeviousDevicesAPI::DeviousDevicesAPI::GetWornDevice(RE::Actor* a_actor, RE::BGSKeyword* a_kw, bool a_fuzzy) const
{
    return DeviousDevices::LibFunctions::GetSingleton()->GetWornDevice(a_actor,a_kw,a_fuzzy);
}

std::vector<RE::TESObjectARMO*> DeviousDevicesAPI::DeviousDevicesAPI::GetWornDevices(RE::Actor* a_actor) const
{
    return DeviousDevices::LibFunctions::GetSingleton()->GetWornDevices(a_actor);
}

RE::TESObjectARMO* DeviousDevicesAPI::DeviousDevicesAPI::GetHandRestrain(RE::Actor* a_actor) const
{
    return DeviousDevices::LibFunctions::GetSingleton()->GetHandRestrain(a_actor);
}

