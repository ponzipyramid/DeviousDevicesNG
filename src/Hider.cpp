#include "Hider.h"

DeviousDevices::DeviceHiderManager* DeviousDevices::DeviceHiderManager::_this = new DeviousDevices::DeviceHiderManager;

void DeviousDevices::DeviceHiderManager::Setup()
{
    RE::TESDataHandler* loc_datahandler = RE::TESDataHandler::GetSingleton();

    if (loc_datahandler == nullptr) return;

    _hidekeywords.clear();

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

DeviousDevices::DeviceHiderManager* DeviousDevices::DeviceHiderManager::GetSingleton()
{
    return _this;
}

std::vector<int> DeviousDevices::DeviceHiderManager::RebuildSlotMask(RE::Actor* a_actor, std::vector<int> a_slotfilter)
{
    if (a_actor == nullptr) return std::vector<int>(); 

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
    return !a_armor->HasKeywordInArray(_hidekeywords,false);
}
