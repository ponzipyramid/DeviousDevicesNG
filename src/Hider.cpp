#include "Hider.h"

SINGLETONBODY(DeviousDevices::DeviceHiderManager)

void DeviousDevices::DeviceHiderManager::Setup()
{
    if (!_setup)
    {
        LOG("DeviceHiderManager::Setup()")
        RE::TESDataHandler* loc_datahandler = RE::TESDataHandler::GetSingleton();

        if (loc_datahandler == nullptr) 
        {
            LOG("DeviceHiderManager::Setup() - loc_datahandler = NULL -> cant setup!")
            return;
        }

        //check lockable keyword
        if (_kwlockable == nullptr)
        {
            _kwlockable = static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x003894,"Devious Devices - Assets.esm"));
            if (_kwlockable != nullptr) _hidekeywords.push_back(_kwlockable);
        }
        //check plug keyword
        if (_kwplug == nullptr)
        {
            _kwplug = static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x003331,"Devious Devices - Assets.esm"));
            if (_kwplug != nullptr) _hidekeywords.push_back(_kwplug);
        }
        //check SoS keyword
        if (_kwsos == nullptr)
        {
            _kwsos = static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x0012D9,"Schlongs of Skyrim - Core.esm"));
            if (_kwsos != nullptr) _hidekeywords.push_back(_kwsos);
        }
        //check NoHide keyword
        if (_kwnohide == nullptr)
        {
            _kwnohide = static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x043F84,"Devious Devices - Integration.esm"));
            if (_kwnohide != nullptr) _nohidekeywords.push_back(_kwnohide);
        }


        const uintptr_t loc_GetWornMask_VisitAdr = REL::RelocationID(543106, 188971).address() + (REL::Module::GetRuntime() == REL::Module::Runtime::SE ? 0x10 : 0x88);
        REL::Relocation<std::uintptr_t> loc_vtbl{loc_GetWornMask_VisitAdr};
        GetWornMask_Visit_old = loc_vtbl.write_vfunc(0x00, GetWornMask_Visit);
        LOG("Installed papyrus hook on GetWornMask_Visit at {0:x} with replacement from address {0:x}", 
            loc_GetWornMask_VisitAdr, (void*)&DeviceHiderManager::GetWornMask_Visit);

        //_GetWornMask = (OriginalGetWornMask)loc_GetWornFormAdr;
        //
        //DetourTransactionBegin();
        //DetourUpdateThread(GetCurrentThread());
        //DetourAttach(&(PVOID&)_GetWornMask, (PBYTE)&DeviceHiderManager::GetWornMask);
        //
        //if (DetourTransactionCommit() == NO_ERROR)
        //{
        //    LOG("Installed papyrus hook on GetWornMask_Visit at {0:x} with replacement from address {0:x}", 
        //        loc_GetWornMaskVTAdr, (void*)&DeviceHiderManager::GetWornMask_Visit);
        //}
        //else
        //{
        //    WARN("Failed to install hook on GetWornMask");
        //}

        _setup = true;
    }
}

std::vector<int> DeviousDevices::RebuildSlotMask(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<int> a_slotfilter)
{
    DeviceHiderManager* loc_hider = DeviceHiderManager::GetSingleton();
    return loc_hider->RebuildSlotMask(a_actor,a_slotfilter);
}

int DeviousDevices::FilterMask(PAPYRUSFUNCHANDLE,RE::Actor* a_actor, int a_slotmask)
{
    DeviceHiderManager* loc_hider = DeviceHiderManager::GetSingleton();
    return loc_hider->FilterMask(a_actor,a_slotmask);
}

    if (loc_nohidekeyword == nullptr) return std::vector<int>();

    //result array
    //0-127 = SlotMaskUsage
    //128   = SlotMask
    std::vector<int> loc_res = std::vector<int>(129);

    for(uint32_t i1 = 0x00000001; i1 < 0x40000000; i1 <<= 1U)
    {
        //get armor from slot
        const RE::TESObjectARMO* loc_armor = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(i1));

        //check if armor is not null (otherwise crash ;))
        //also check if armor have no no_hide keyword
        if ((loc_armor != nullptr) && !loc_armor->HasKeywordInArray(_nohidekeywords,true))
        {
            //get slot mask
            const uint32_t loc_mask = static_cast<uint32_t>(loc_armor->GetSlotMask());

            for(uint8_t i2 = 0; i2 < 31; i2++)
            {
                if (loc_mask & (0x1U << i2))
                {
                    const uint8_t loc_filterindx = i2*4;
                    for(uint8_t i3 = loc_filterindx; i3 < (loc_filterindx+4); i3++)
                    {
                        if (a_slotfilter[i3] != 0)
                        {
                            loc_res[i3]  += 1;
                            loc_res[128] |= a_slotfilter[i3];
                        }
                    }
                }
            }
        }
    }
    return loc_res;
}

int DeviousDevices::DeviceHiderManager::FilterMask(RE::Actor* a_actor, int a_slotmask)
{
    if (a_actor == nullptr) return 0x00000000;
    int loc_res = a_slotmask;
    for(int i = 0x00000001; i != 0x40000000; i <<= 1)
    {
        if (a_slotmask & i)
        {
            //get armor from slot
            RE::TESObjectARMO* loc_armor = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(i));
            if ((loc_armor != nullptr) && (!IsValidForHide(loc_armor)))
            {
                loc_res &= ~i;
            }
        }
    }
    return loc_res;
}

bool DeviousDevices::DeviceHiderManager::IsValidForHide(RE::TESObjectARMO* a_armor)
{
    if (a_armor == nullptr) return false;
    return a_armor->HasKeywordInArray(_hidekeywords,false) && !a_armor->HasKeywordInArray(_nohidekeywords,false);
}

std::uint32_t DeviousDevices::DeviceHiderManager::GetWornMask(RE::InventoryChanges* a_this)
{
    uint32_t loc_res = _GetWornMask(a_this);
    
    LOG("GetWornMask({}) - res = {}",a_this->owner->GetName(),loc_res)
    return loc_res;
}

RE::BSContainer::ForEachResult DeviousDevices::DeviceHiderManager::GetWornMask_Visit(void* a_this, RE::InventoryEntryData* a_entryData)
{
    if (a_entryData != nullptr)
    {
        RE::TESBoundObject* loc_obj = a_entryData->object;
        RE::TESForm* loc_owner = a_entryData->GetOwner();
        if (loc_obj != nullptr && loc_owner != nullptr)
        {
            LOG("GetWornMask_Visit called for {} on {}",loc_obj->GetName(),loc_owner->GetName())
        }
    }

    //LOG("GetWornMask_Visit called for {}",a_entryData)

    

    return GetWornMask_Visit_old(a_this,a_entryData);
}