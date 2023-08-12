#pragma once

#include "NodeHider.h"

namespace DeviousDevices
{
    class UpdateHook
    {
    public:
        UpdateHook(UpdateHook &) = delete;
        void operator=(const UpdateHook &) = delete;
        static UpdateHook* GetSingleton();

        void Setup();

    protected:
        UpdateHook(){}
        ~UpdateHook(){}

        static UpdateHook* _this;
    private:
        bool _hooked = false;

        static void Update(RE::Actor* a_actor, float a_delta);
        inline static REL::Relocation<decltype(Update)> Update_old;
    };
}