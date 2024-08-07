#pragma once

namespace DeviousDevices
{
    class HooksVirtual
    {
    SINGLETONHEADER(HooksVirtual)
    public:
        void Setup();
        static void ProcessButton(RE::MovementHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data);

    private:
        bool _init = false;
    private:
        inline static REL::Relocation<decltype(ProcessButton)>      ProcessButton_old;
    };
}