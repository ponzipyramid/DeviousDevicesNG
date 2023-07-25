#include "Hider.h"

std::vector<int> DeviousDevices::RebuildSlotMask(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<int> a_slotusage, std::vector<int> a_slotfilter)
{
    if (a_actor == nullptr) return std::vector<int>(); 

    //get nohide keyword
    //variables are made static to increase performance
    static RE::BGSKeyword* loc_nohidekeyword = nullptr;
    static std::vector<RE::BGSKeyword*> loc_nohidekeywordarr;

    if (loc_nohidekeyword == nullptr)
    {
        loc_nohidekeyword = static_cast<RE::BGSKeyword*>(RE::TESDataHandler::GetSingleton()->LookupForm(0x043F84,"Devious Devices - Integration.esm"));
        loc_nohidekeywordarr.push_back(loc_nohidekeyword);
    }

    if (loc_nohidekeyword == nullptr) return std::vector<int>();

    //result array
    //0-127 = SlotMaskUsage
    //128   = SlotMask
    std::vector<int> loc_res = std::vector<int>(129);

    for(uint32_t i1 = 0x00000001; i1 < 0x40000000; i1 <<= 1U)
    {
        //get armor from slot
        RE::TESObjectARMO* loc_armor = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(i1));

        //check if armor is not null (otherwise crash ;))
        //also check if armor have no no_hide keyword
        if ((loc_armor != nullptr) && !loc_armor->HasKeywordInArray(loc_nohidekeywordarr,true))
        {
            //get slot mask
            uint32_t loc_mask = static_cast<uint32_t>(loc_armor->GetSlotMask());

            for(uint8_t i2 = 0; i2 < 31; i2++)
            {
                if (loc_mask & (0x1U << i2))
                {
                    uint8_t loc_filterindx = i2*4;
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

int DeviousDevices::FilterMask(PAPYRUSFUNCHANDLE,RE::Actor* a_actor, int a_slotmask)
{
    if (a_actor == nullptr) return 0x00000000;

    int loc_res = a_slotmask;
    for(int i = 0x00000001; i != 0x40000000; i <<= 1)
    {
        if (a_slotmask & i)
        {
            //get armor from slot
            RE::TESObjectARMO* loc_armor = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(i));
            if ((loc_armor != nullptr) && (!_IsValidForHide(loc_armor)))
            {
                loc_res &= ~i;
            }
        }
    }
    return loc_res;
}

bool DeviousDevices::_IsValidForHide(RE::TESObjectARMO* a_armor)
{
    if (a_armor == nullptr) return false;

    static std::vector<RE::BGSKeyword*> loc_nohidekeywords;

    //check lockable keyword
    static RE::BGSKeyword* loc_kwlockable = nullptr;
    if (loc_kwlockable == nullptr)
    {
        loc_kwlockable = static_cast<RE::BGSKeyword*>(RE::TESDataHandler::GetSingleton()->LookupForm(0x003894,"Devious Devices - Assets.esm"));
        if (loc_kwlockable != nullptr) loc_nohidekeywords.push_back(loc_kwlockable);
    }
    //check plug keyword
    static RE::BGSKeyword* loc_kwplug = nullptr;
    if (loc_kwplug == nullptr)
    {
        loc_kwplug = static_cast<RE::BGSKeyword*>(RE::TESDataHandler::GetSingleton()->LookupForm(0x003331,"Devious Devices - Assets.esm"));
        if (loc_kwplug != nullptr) loc_nohidekeywords.push_back(loc_kwplug);
    }
    //check SoS keyword
    static RE::BGSKeyword* loc_kwsos = nullptr;
    if (loc_kwsos == nullptr)
    {
        loc_kwsos = static_cast<RE::BGSKeyword*>(RE::TESDataHandler::GetSingleton()->LookupForm(0x0012D9,"Schlongs of Skyrim - Core.esm"));
        if (loc_kwsos != nullptr) loc_nohidekeywords.push_back(loc_kwsos);
    }

    return !a_armor->HasKeywordInArray(loc_nohidekeywords,false);
}
