#include "LibFunctions.h"

SINGLETONBODY(DeviousDevices::LibFunctions)

std::vector<RE::TESObjectARMO*> DeviousDevices::LibFunctions::GetDevices(RE::Actor* a_actor, int a_mode, bool a_worn)
{
    std::vector<RE::TESObjectARMO*> loc_res;
    if (a_actor == nullptr) return loc_res;

    if (a_worn)
    {
        for (uint32_t loc_mask = 0x00000001U; loc_mask != 0x80000000U ;loc_mask <<= 1U)
        {
            RE::TESObjectARMO* loc_deviceRD = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(loc_mask));
            if (loc_deviceRD != nullptr)
            {
                DeviceReader::DeviceUnit loc_device = DeviceReader::GetSingleton()->GetDeviceUnit(loc_deviceRD,1);
                if (loc_device.deviceInventory != nullptr && loc_device.deviceRendered != nullptr)
                {
                    if (a_mode == 0) loc_res.push_back(loc_device.deviceInventory);
                    else loc_res.push_back(loc_device.deviceRendered);
                }
            }
        }
    }
    else
    {
        RE::Actor::InventoryItemMap loc_inv = a_actor->GetInventory();
        for (auto&& it : loc_inv)
        {
            RE::TESBoundObject* loc_obj = it.first;
            if ((loc_obj != nullptr) && loc_obj->IsArmor())
            {
                RE::TESObjectARMO* loc_deviceID = loc_obj->As<RE::TESObjectARMO>();
                RE::TESObjectARMO* loc_deviceRD = DeviceReader::GetSingleton()->GetDeviceRender(loc_deviceID);
                if ((loc_deviceID != nullptr) && (loc_deviceRD != nullptr))
                {
                    if (a_mode == 0) loc_res.push_back(loc_deviceID);
                    else loc_res.push_back(loc_deviceRD);
                }
            }
        }
    }
    return loc_res;
}

RE::TESObjectARMO* DeviousDevices::LibFunctions::GetWornDevice(RE::Actor* a_actor, RE::BGSKeyword* a_kw)
{
    if ((a_actor == nullptr) || (a_kw == nullptr)) return nullptr;
    for (uint32_t loc_mask = 0x00000001U; loc_mask != 0x80000000U ;loc_mask <<= 1U)
    {
        RE::TESObjectARMO* loc_deviceRD = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(loc_mask));
        if (loc_deviceRD != nullptr)
        {
            DeviceReader::DeviceUnit loc_device = DeviceReader::GetSingleton()->GetDeviceUnit(loc_deviceRD,1);
            if (loc_device.kwd == a_kw)
            {
                return loc_device.deviceInventory;
            }
        }
    }
    return nullptr;
}

std::vector<RE::TESObjectARMO*> DeviousDevices::GetDevices(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, int a_mode, bool a_worn)
{
    LOG("GetDevices called")
    return LibFunctions::GetSingleton()->GetDevices(a_actor,a_mode,a_worn);
}

RE::TESObjectARMO* DeviousDevices::GetWornDevice(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, RE::BGSKeyword* a_kw)
{
    LOG("GetWornDevice called")
    return LibFunctions::GetSingleton()->GetWornDevice(a_actor,a_kw);
}
