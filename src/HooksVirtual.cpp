#include "HooksVirtual.h"
#include "LibFunctions.h"

SINGLETONBODY(DeviousDevices::HooksVirtual)

void DeviousDevices::HooksVirtual::Setup()
{
    if (!_init)
    {
        // Vtable of MovementHandler
        REL::Relocation<std::uintptr_t> vtbl_MovementHandler{RELOCATION_ID(263056, 208715).address()};
        ProcessButton_old = vtbl_MovementHandler.write_vfunc(0x04, ProcessButton);
        _init = true;
    }
}

void DeviousDevices::HooksVirtual::ProcessButton(RE::MovementHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data)
{
    ProcessButton_old(a_this,a_event,a_data);     

    static auto loc_kwds = ConfigManager::GetSingleton()->GetArrayText("Movement.asForceWalkKeywords",false);

    for (auto&& it :loc_kwds)
    {
        if (LibFunctions::GetSingleton()->WornHasKeyword(RE::PlayerCharacter::GetSingleton(),it))
        {
            a_data->running = false;
            return;
        }
    }
}
