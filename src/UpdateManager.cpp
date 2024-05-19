#include "UpdateManager.h"

SINGLETONBODY(DeviousDevices::UpdateManager)

void DeviousDevices::UpdateManager::Setup()
{
    if (!_installed)
    {
        _installed = true;
        REL::Relocation<std::uintptr_t> vtbl_player{RE::PlayerCharacter::VTABLE[0]};
        UpdatePlayer_old = vtbl_player.write_vfunc(REL::Module::GetRuntime() != REL::Module::Runtime::VR ? 0x0AD : 0x0AF, UpdatePlayer);

        REL::Relocation<std::uintptr_t> vtbl_character{RE::Character::VTABLE[0]};
        UpdateCharacter_old = vtbl_character.write_vfunc(REL::Module::GetRuntime() != REL::Module::Runtime::VR ? 0x0AD : 0x0AF, UpdateCharacter);

        DEBUG("UpdateManager::Setup() - Updates hooked")
    }
}

//this function is only called if no menu is open. It also looks like that it is not called when player is in free cam mode
void DeviousDevices::UpdateManager::UpdatePlayer(RE::Actor* a_actor, float a_delta)
{
    static RE::Actor* loc_player = RE::PlayerCharacter::GetSingleton();
    UpdateManager* loc_manager = UpdateManager::GetSingleton();

    if (a_actor == loc_player)
    {
        if (!loc_manager->UpdateThread1) 
        {
            loc_manager->UpdateThread1 = true;
            ExpressionManager::GetSingleton()->UpdateGagExpression(loc_player);
            std::thread([loc_manager]
            {
                //wait
                std::this_thread::sleep_for(std::chrono::milliseconds(ConfigManager::GetSingleton()->GetVariable<int>("GagExpression.iUpdatePlayerTime",500))); //wait x ms before updating again
                loc_manager->UpdateThread1 = false;
            }).detach();
        }

        if (!loc_manager->UpdateThread2) 
        {
            loc_manager->UpdateThread2 = true;
            NodeHider::GetSingleton()->Update();
            std::thread([loc_manager]
            {
                //wait
                std::this_thread::sleep_for(std::chrono::milliseconds(ConfigManager::GetSingleton()->GetVariable<int>("UpdateThreads.iUpdateTime2",2000))); //wait x ms before updating again
                loc_manager->UpdateThread2 = false;
            }).detach();
        }

        if (!loc_manager->UpdateThread3) 
        {
            loc_manager->UpdateThread3 = true;
            ExpressionManager::GetSingleton()->CleanUnusedActors();
            std::thread([loc_manager]
            {
                //wait
                std::this_thread::sleep_for(std::chrono::seconds(ConfigManager::GetSingleton()->GetVariable<int>("GagExpression.iCleanTime",10))); //wait 30 seconds
                loc_manager->UpdateThread3 = false;
            }).detach();
        }
        ExpressionManager::GetSingleton()->IncUpdateCounter();
    }
    UpdatePlayer_old(a_actor,a_delta);
}

//this function is only called if no menu is open. It also looks like that it is not called when player is in free cam mode
void DeviousDevices::UpdateManager::UpdateCharacter(RE::Actor* a_actor, float a_delta)
{
    static bool loc_updatenpc = ConfigManager::GetSingleton()->GetVariable<bool>("GagExpression.bNPCsEnabled", true);
    if (loc_updatenpc)
    {
        ExpressionManager::GetSingleton()->UpdateGagExpressionTimed(a_actor,a_delta);
    }

    UpdateCharacter_old(a_actor,a_delta);
}