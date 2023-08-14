#pragma once

#include "NodeHider.h"

namespace DeviousDevices
{
    class UpdateHook
    {
    SINGLETONHEADER(UpdateHook)
    public:
        void Setup();

    private:
        bool _hooked = false;

        static void Update(RE::Actor* a_actor, float a_delta);
        inline static REL::Relocation<decltype(Update)> Update_old;
    };
}