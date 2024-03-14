#include "UpdateManager.h"

SINGLETONBODY(DeviousDevices::UpdateManager)

void DeviousDevices::UpdateManager::Setup()
{
    if (!_installed)
    {
        _installed = true;
        REL::Relocation<std::uintptr_t> vtbl{RE::PlayerCharacter::VTABLE[0]};
        Update_old = vtbl.write_vfunc(REL::Module::GetRuntime() != REL::Module::Runtime::VR ? 0x0AD : 0x0AF, Update);
    }
}

//this function is only called if no menu is open. It also looks like that it is not called when player is in free cam mode
void DeviousDevices::UpdateManager::Update(RE::Actor* a_actor, float a_delta)
{
    static RE::Actor* loc_player = RE::PlayerCharacter::GetSingleton();
    UpdateManager* loc_manager = UpdateManager::GetSingleton();
    if (a_actor == loc_player)
    {
        if (!loc_manager->UpdateThread1) std::thread([loc_manager]
        {
            loc_manager->UpdateThread1 = true;

            //serialize task so it doesnt create race condition
            SKSE::GetTaskInterface()->AddTask([]
            {
                //update gag expressions
                ExpressionManager::GetSingleton()->UpdateGagExpForNPCs();
            });

            //wait
            std::this_thread::sleep_for(std::chrono::milliseconds(ConfigManager::GetSingleton()->GetVariable<int>("UpdateThreads.iUpdateTime1",500))); //wait x ms before updating again
            loc_manager->UpdateThread1 = false;
        }).detach();

        if (!loc_manager->UpdateThread2) std::thread([loc_manager]
        {
            loc_manager->UpdateThread2 = true;

            //serialize task so it doesnt create race condition
            SKSE::GetTaskInterface()->AddTask([]
            {
                //update node hider
                NodeHider::GetSingleton()->Update();
            });

            //wait
            std::this_thread::sleep_for(std::chrono::milliseconds(ConfigManager::GetSingleton()->GetVariable<int>("UpdateThreads.iUpdateTime2",2000))); //wait x ms before updating again
            loc_manager->UpdateThread2 = false;
        }).detach();
    }
    Update_old(a_actor,a_delta);
}