#include "UpdateHook.h"

SINGLETONBODY(DeviousDevices::UpdateHook)

void DeviousDevices::UpdateHook::Setup()
{
    if (!_hooked)
    {
        _hooked = true;
        REL::Relocation<std::uintptr_t> vtbl{RE::PlayerCharacter::VTABLE[0]};
        Update_old = vtbl.write_vfunc(0x0AD, Update);
    }
}

//this function is only called if no menu is open. It also looks like that it is not called when player is in free cam mode
void DeviousDevices::UpdateHook::Update(RE::Actor* a_actor, float a_delta)
{
    SKSE::log::info("START");
    static RE::Actor* loc_player = RE::PlayerCharacter::GetSingleton();
    if (a_actor == loc_player)
    {
        // ==== Update Node Hider ====
        {
            static NodeHider* loc_nodehider = NodeHider::GetSingleton();
            loc_nodehider->Update(a_delta);
        }
    }
    Update_old(a_actor,a_delta);
    SKSE::log::info("STOP");
}
