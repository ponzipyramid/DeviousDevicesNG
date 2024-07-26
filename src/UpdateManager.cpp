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

        static const bool loc_nodehider = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bEnabled",true);
        if (loc_nodehider && !loc_manager->UpdateThread2) 
        {
            loc_manager->UpdateThread2 = true;
            NodeHider::GetSingleton()->UpdatePlayer(loc_player);
            std::thread([loc_manager]
            {
                //wait
                std::this_thread::sleep_for(std::chrono::milliseconds(ConfigManager::GetSingleton()->GetVariable<int>("NodeHider.iUpdatePlayerTime",500))); //wait x ms before updating again
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
        NodeHider::GetSingleton()->IncUpdateCounter();
    }
    UpdatePlayer_old(a_actor,a_delta);
}

//this function is only called if no menu is open. It also looks like that it is not called when player is in free cam mode
void DeviousDevices::UpdateManager::UpdateCharacter(RE::Actor* a_actor, float a_delta)
{
    const auto loc_refBase = a_actor->GetActorBase();
    if(a_actor->Is(RE::FormType::NPC) || (loc_refBase && loc_refBase->Is(RE::FormType::NPC)))
    {
        if (a_actor->GetRace()->GetPlayable())
        {
            static const bool loc_gag = ConfigManager::GetSingleton()->GetVariable<bool>("GagExpression.bNPCsEnabled", true);
            if (loc_gag)
            {
                ExpressionManager::GetSingleton()->UpdateGagExpressionTimed(a_actor);
            }

            static const bool loc_nodehider = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bEnabled",true);
            if (loc_nodehider)
            {
                NodeHider::GetSingleton()->UpdateTimed(a_actor);
            }
        }
    }
    UpdateCharacter_old(a_actor,a_delta);
}