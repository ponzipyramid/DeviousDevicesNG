#pragma once

#include "NodeHider.h"
#include "Expression.h"
#include "Config.h"

namespace DeviousDevices
{
    class UpdateManager
    {
    SINGLETONHEADER(UpdateManager)
    public:
        void Setup();

        bool UpdateThread1 = false;
        bool UpdateThread2 = false;
        bool UpdateThread3 = false;
    private:
        bool _installed = false;
        static void UpdatePlayer(RE::Actor* a_actor, float a_delta);
        static void UpdateCharacter(RE::Actor* a_actor, float a_delta);
        inline static REL::Relocation<decltype(UpdatePlayer)>       UpdatePlayer_old;
        inline static REL::Relocation<decltype(UpdateCharacter)>    UpdateCharacter_old;
    };
}