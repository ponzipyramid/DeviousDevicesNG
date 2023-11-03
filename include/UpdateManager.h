#pragma once

#include "NodeHider.h"
#include "Expression.h"

namespace DeviousDevices
{
    class UpdateManager
    {
    SINGLETONHEADER(UpdateManager)
    public:
        void Setup();

        bool UpdateThread500 = false;
    private:
        bool _installed = false;
        static void Update(RE::Actor* a_actor, float a_delta);
        inline static REL::Relocation<decltype(Update)> Update_old;
    };
}