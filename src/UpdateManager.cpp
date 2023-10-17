#include "UpdateManager.h"

SINGLETONBODY(DeviousDevices::UpdateManager)

void DeviousDevices::UpdateManager::Setup()
{
    if (!_installed)
    {
        _installed = true;
        REL::Relocation<std::uintptr_t> vtbl{RE::PlayerCharacter::VTABLE[0]};
        Update_old = vtbl.write_vfunc(0x0AD, Update);
    }
}

bool DeviousDevices::UpdateManager::AddSerTask(std::function<void(void*)> a_task, void* a_arg, bool a_freearg)
{
    std::unique_lock lock(_taskmutex);
    _taskstack.push_back({a_arg,a_task,a_freearg});
    return true;
}

//this function is only called if no menu is open. It also looks like that it is not called when player is in free cam mode
void DeviousDevices::UpdateManager::Update(RE::Actor* a_actor, float a_delta)
{
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
}

void DeviousDevices::UpdateManager::CallSerTasks()
{
    std::unique_lock lock(_taskmutex);

    for (auto&& it : _taskstack)
    {
        it.task(it.arg);
        if (it.freearg) delete it.arg;
    }
    _taskstack.clear();
}
