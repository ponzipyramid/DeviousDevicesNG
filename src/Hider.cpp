#include "Hider.h"

#include <xbyak/xbyak.h>

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

        _setting.assign(128,0);

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

	    auto hook = REL::Relocation<uintptr_t>(REL::Relocation<std::uintptr_t>{REL::RelocationID(24232,24736), REL::VariantOffset(0x2F0,0x2F0, 0x373CB0)});

	    // Expected size: 0x12
	    struct Patch : public Xbyak::CodeGenerator
	    {
		    Patch(std::uintptr_t a_funcAddr)
		    {
			    mov(rdx, r13);
			    mov(rcx, rbp);
			    mov(rax, a_funcAddr);
			    call(rax);
		    }
	    };

	    Patch patch{ reinterpret_cast<std::uintptr_t>(InitWornArmor) };
	    patch.ready();

	    if (patch.getSize() > 0x17) {
		    util::report_and_fail("Patch was too large, failed to install"sv);
	    }

	    REL::safe_fill(hook.address(), REL::NOP, 0x17);
	    REL::safe_write(hook.address(), patch.getCode(), patch.getSize());

        _setup = true;
    }
}

bool DeviousDevices::DeviceHiderManager::IsValidForHide(RE::TESObjectARMO* a_armor) const
{
    if (a_armor == nullptr) return false;
    return a_armor->HasKeywordInArray(_hidekeywords,false) && !a_armor->HasKeywordInArray(_nohidekeywords,false);
}

void DeviousDevices::DeviceHiderManager::SyncSetting(std::vector<int> a_masks)
{
    for (size_t i = 0; i < a_masks.size() && i < _setting.size(); i++) _setting[i] = a_masks[i];
}

const std::vector<int>& DeviousDevices::DeviceHiderManager::GetSetting() const
{
    return _setting;
}

bool DeviousDevices::DeviceHiderManager::ProcessHider(RE::TESObjectARMO* a_armor, RE::Actor* a_actor)
{
    _CheckResult = true;
    //LOG("DeviceHiderManager::ProcessHider({:08X},{}) called",a_armor->GetFormID(),a_actor->GetName(),_CheckResult)
    CheckHiderSlots(a_armor,a_actor,0x00000001,0x40000000);
    //LOG("DeviceHiderManager::ProcessHider({:08X},{}) called - result = {}",a_armor->GetFormID(),a_actor->GetName(),_CheckResult)
    return _CheckResult;
}

void DeviousDevices::DeviceHiderManager::CheckHiderSlots(RE::TESObjectARMO* a_armor, RE::Actor* a_actor, uint32_t a_min, uint32_t a_max)
{
    // TODO
    const int loc_mask = static_cast<int>(a_armor->GetSlotMask());

    for(uint32_t i1 = a_min; i1 < a_max; i1 <<= 1U)
    {
        if (!_CheckResult) return;

        //get armor from slot
        const RE::TESObjectARMO* loc_armor = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(i1));

        if (loc_armor)
        {
            const uint32_t loc_mask2 = static_cast<uint32_t>(loc_armor->GetSlotMask());
            const std::vector<int>& loc_setting = DeviceHiderManager::GetSingleton()->GetSetting();
            for(uint8_t i2 = 0; i2 < 31; i2++)
            {
                //armor have slot - use setting
                if (loc_mask2 & (0x1U << i2))
                {
                    const uint8_t loc_filterindx = i2*4;
                    for(uint8_t i3 = loc_filterindx; i3 < (loc_filterindx+4); i3++)
                    {
                        if (loc_mask & loc_setting[i3])
                        {
                            _CheckResult = false;
                            return;
                        }
                    }
                }
            }
        }
    }
}

bool DeviousDevices::DeviceHiderManager::HasRace(RE::TESObjectARMA* a_armorAddon, RE::TESRace* a_race)
{
    using func_t = decltype(HasRace);
    static REL::Relocation<func_t> func{ REL::RelocationID(17359,17757), REL::VariantOffset(0,0, 0x2380A0) };
    return func(a_armorAddon, a_race);
}

void DeviousDevices::DeviceHiderManager::InitWornArmorAddon(RE::TESObjectARMA* a_armorAddon, RE::TESObjectARMO* a_armor, RE::BSTSmartPointer<RE::BipedAnim>* a_biped, RE::SEX a_sex)
{
    using func_t = decltype(InitWornArmorAddon);
    static REL::Relocation<func_t> func{ REL::RelocationID(17361, 17759), REL::VariantOffset(0x0,0x0,0x2383A0) };
    return func(a_armorAddon, a_armor, a_biped, a_sex);
}

void DeviousDevices::DeviceHiderManager::InitWornArmor(RE::TESObjectARMO* a_armor, RE::Actor* a_actor, RE::BSTSmartPointer<RE::BipedAnim>* a_biped)
{
    RE::TESRace*    loc_race    = a_actor->GetRace();
    RE::SEX         loc_sex     = a_actor->GetActorBase()->GetSex();
    //LOG("InitWornArmor called")
    //LOG("InitWornArmor called for {} on {}",a_armor->GetName(),a_actor->GetName())

    //check if armor is device and can be hidden. If not, just render it
    if (DeviceHiderManager::GetSingleton()->IsValidForHide(a_armor))
    {
        if (!DeviceHiderManager::GetSingleton()->ProcessHider(a_armor,a_actor)) return;
    }

    for (auto&& itArmorAddon : a_armor->armorAddons) 
    {
        if (HasRace(itArmorAddon,loc_race)) 
        {
            InitWornArmorAddon(itArmorAddon,a_armor,a_biped,loc_sex);
        }
    }
}
