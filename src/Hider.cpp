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

        _forcestrip.clear();
        _filter.assign(128,0);

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
        //check contraption keyword
        if (_contraption == nullptr)
        {
            _contraption = static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x0022FF,"Devious Devices - Contraptions.esm"));
            if (_contraption != nullptr) _nohidekeywords.push_back(_contraption);
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

bool DeviousDevices::DeviceHiderManager::IsDevice(const RE::TESObjectARMO* a_armor) const
{
    if (a_armor == nullptr) return false;
    static const std::vector<RE::BGSKeyword*> loc_devicekw = {_kwlockable, _kwplug};
    return a_armor->HasKeywordInArray(loc_devicekw,false);
}

void DeviousDevices::DeviceHiderManager::SyncSetting(std::vector<int> a_masks,HiderSetting a_setting)
{
    for (size_t i = 0; i < a_masks.size() && i < _filter.size(); i++) _filter[i] = a_masks[i];
    _setting = a_setting;
    UpdateActors3D();
}

const std::vector<int>& DeviousDevices::DeviceHiderManager::GetFilter() const
{
    return _filter;
}

const DeviousDevices::HiderSetting& DeviousDevices::DeviceHiderManager::GetSetting() const
{
    return _setting;
}

bool DeviousDevices::DeviceHiderManager::ProcessHider(RE::TESObjectARMO* a_armor, RE::Actor* a_actor) const
{
    _CheckResult = true;

    //LOG("DeviceHiderManager::ProcessHider({:08X},{}) called",a_armor->GetFormID(),a_actor->GetName(),_CheckResult)
    std::array<std::thread,8> loc_threads = 
    {
        std::thread(&DeviceHiderManager::CheckHiderSlots,this,a_armor,a_actor,0x00000001,0x00000008),
        std::thread(&DeviceHiderManager::CheckHiderSlots,this,a_armor,a_actor,0x00000010,0x00000080),
        std::thread(&DeviceHiderManager::CheckHiderSlots,this,a_armor,a_actor,0x00000100,0x00000800),
        std::thread(&DeviceHiderManager::CheckHiderSlots,this,a_armor,a_actor,0x00001000,0x00008000),
        std::thread(&DeviceHiderManager::CheckHiderSlots,this,a_armor,a_actor,0x00010000,0x00080000),
        std::thread(&DeviceHiderManager::CheckHiderSlots,this,a_armor,a_actor,0x00100000,0x00800000),
        std::thread(&DeviceHiderManager::CheckHiderSlots,this,a_armor,a_actor,0x01000000,0x08000000),
        std::thread(&DeviceHiderManager::CheckHiderSlots,this,a_armor,a_actor,0x10000000,0x40000000)
    };

    for (auto&& it : loc_threads) it.join();

    //LOG("DeviceHiderManager::ProcessHider res = {}",_CheckResult)

    //CheckHiderSlots(a_armor,a_actor,0x00000001,0x40000000);
    //LOG("DeviceHiderManager::ProcessHider({:08X},{}) called - result = {}",a_armor->GetFormID(),a_actor->GetName(),_CheckResult)
    return _CheckResult;
}

inline uint16_t DeviousDevices::DeviceHiderManager::UpdateActors3D()
{
    RE::Actor* loc_player = RE::PlayerCharacter::GetSingleton();

    Update3DSafe(loc_player);

    uint16_t loc_updated = 0;

    RE::TES::GetSingleton()->ForEachReferenceInRange(loc_player, 10000, [&](RE::TESObjectREFR& a_ref) {
        auto loc_refBase    = a_ref.GetBaseObject();
        auto loc_actor      = a_ref.As<RE::Actor>();
        if (loc_actor && !loc_actor->IsDisabled() && loc_actor->Is3DLoaded() && (a_ref.Is(RE::FormType::NPC) || (loc_refBase && loc_refBase->Is(RE::FormType::NPC)))) 
        {
            loc_updated += 1;
            Update3DSafe(loc_actor);
        }
        return RE::BSContainer::ForEachResult::kContinue;
    });

    return loc_updated;
}

void DeviousDevices::DeviceHiderManager::SetActorStripped(RE::Actor* a_actor, bool a_stripped, int a_armorfilter, int a_devicefilter)
{
    if (a_actor == nullptr) return;

    if (a_stripped)
    {
        if (IsActorStripped(a_actor)) return;
        _forcestrip.push_back({a_actor,a_armorfilter,a_devicefilter});
        Update3DSafe(a_actor);
    }
    else
    {
        if (IsActorStripped(a_actor)) return;
        const auto loc_it = std::find_if(_forcestrip.begin(),_forcestrip.end(),[a_actor] (const ForceStripSetting& a_strip)
            {
                return (a_strip.actor == a_actor);
            }
        );
        if (loc_it != _forcestrip.end()) 
        {
            _forcestrip.erase(loc_it);
            Update3DSafe(a_actor);
        }
    }
}

bool DeviousDevices::DeviceHiderManager::IsActorStripped(RE::Actor* a_actor)
{
    const auto loc_it = std::find_if(_forcestrip.begin(),_forcestrip.end(),[a_actor] (const ForceStripSetting& a_strip)
        {
            return (a_strip.actor == a_actor);
        }
    );
    return (loc_it != _forcestrip.end());
}

bool DeviousDevices::DeviceHiderManager::CheckForceStrip(RE::TESObjectARMO* a_armor, RE::Actor* a_actor) const
{
    if (_forcestrip.size() == 0) return true;
    const auto loc_it = std::find_if(_forcestrip.begin(),_forcestrip.end(),[a_actor] (const ForceStripSetting& a_strip)
        {
            return (a_strip.actor == a_actor);
        }
    );

    const bool loc_forcestriped = (loc_it != _forcestrip.end());

    if (loc_forcestriped)
    {
        const int loc_armorfilter = loc_it->armorfilter;
        const int loc_devicefilter = loc_it->devicefilter;

        const int loc_mask = (int)a_armor->GetSlotMask();

        const bool loc_isdevice = IsDevice(a_armor);
        if (((loc_mask & loc_devicefilter) && loc_isdevice) || ((loc_mask & loc_armorfilter) && !loc_isdevice))
        {
            return false;
        }
        
        return true;
    }
    
    return true;
}

bool DeviousDevices::DeviceHiderManager::CheckNPCArmor(RE::TESObjectARMO* a_armor, RE::Actor* a_actor) const
{
    switch (_setting)
    {
    case sAlwaysNakedNPCs:
        return false;
    case sBoundNakedNPCs:
        //check if actor is bound. If not, then continue
        const RE::TESObjectARMO* loc_device = a_actor->GetWornArmor(RE::BIPED_MODEL::BipedObjectSlot::kModChestPrimary);
        if ((loc_device != nullptr) && loc_device->HasKeywordString("zad_DeviousHeavyBondage"))
        {
            return false;
        }

        // TODO
        //const RE::ObjectRefHandle loc_furniture = a_actor->GetOccupiedFurniture();
        //if (loc_furniture.get() != nullptr) LOG("Actor {} is in furniture!",a_actor->GetName())
        //if ((loc_furniture.get() != nullptr) && loc_furniture.get()->GetBaseObject()->HasKeywordInArray({_contraption},true))
        //{
        //    return false;
        //}
        break;
    }
    return true;
}

void DeviousDevices::DeviceHiderManager::CheckHiderSlots(RE::TESObjectARMO* a_armor, RE::Actor* a_actor, uint32_t a_min, uint32_t a_max) const
{
    const int loc_mask = static_cast<int>(a_armor->GetSlotMask());

    for(uint32_t i1 = a_min; i1 <= a_max; i1 <<= 1U)
    {
        if (!_CheckResult) return;

        //get armor from slot
        
        const RE::TESObjectARMO* loc_armor = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(i1));

        //LOG("DeviceHiderManager::CheckHiderSlots({:08X}.{:08X}) -Checking slot 0x{:08X} = 0x{:08X}",a_min,a_max,i1,loc_armor ? loc_armor->GetFormID() : NULL)

        if (loc_armor && IsDevice(loc_armor))
        {
            const uint32_t loc_mask2 = static_cast<uint32_t>(loc_armor->GetSlotMask());
            const std::vector<int>& loc_filter = DeviceHiderManager::GetSingleton()->GetFilter();
            for(uint8_t i2 = 0; i2 < 31; i2++)
            {
                //armor have slot - use setting
                if (loc_mask2 & (0x1U << i2))
                {
                    const uint8_t loc_filterindx = i2*4;
                    for(uint8_t i3 = loc_filterindx; i3 < (loc_filterindx+4); i3++)
                    {
                        if (loc_mask & loc_filter[i3])
                        {
                            _CheckResult = false;
                            //LOG("DeviceHiderManager::CheckHiderSlots({:08X}.{:08X}) - done. Res={}",a_min,a_max,_CheckResult)
                            return;
                        }
                    }
                }
            }
        }
    }

    //LOG("DeviceHiderManager::CheckHiderSlots({:08X}.{:08X}) - done. Res={}",a_min,a_max,_CheckResult)
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

    DeviceHiderManager* loc_manager = DeviceHiderManager::GetSingleton();

    //check if actor is force striped
    if (!loc_manager->CheckForceStrip(a_armor,a_actor)) return;

    //check if armor is device and can be hidden. If not, just render it
    if (loc_manager->IsValidForHide(a_armor))
    {
        //LOG("Device {:08X} on {} is valid for hider!",a_armor->GetFormID(),a_actor->GetName())
        if (!loc_manager->ProcessHider(a_armor,a_actor)) return;
    } 
    else
    {
        if (!a_actor->IsPlayerRef() && !loc_manager->CheckNPCArmor(a_armor,a_actor))
        {
            return;
        }
    }

    for (auto&& itArmorAddon : a_armor->armorAddons) 
    {
        if (HasRace(itArmorAddon,loc_race)) 
        {
            InitWornArmorAddon(itArmorAddon,a_armor,a_biped,loc_sex);
        }
    }
}

bool DeviousDevices::DeviceHiderManager::Update3D(RE::Actor* a_actor)
{
    using func_t = decltype(Update3D);
    static REL::Relocation<func_t> func{ REL::RelocationID(19316, 19743), REL::VariantOffset(0x0,0x0,0x2A5AC0) };
    return func(a_actor);
}

void DeviousDevices::DeviceHiderManager::Update3DSafe(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;
    auto loc_handle = a_actor->GetHandle();
    SKSE::GetTaskInterface()->AddTask([loc_handle]
    {
        if (auto actor = loc_handle.get(); actor && actor->Is3DLoaded()) {
            Update3D(actor.get());
        }
    });
}
