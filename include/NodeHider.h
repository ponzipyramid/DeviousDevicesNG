#pragma once

namespace DeviousDevices
{
    //for implementing this, I used https://github.com/ArranzCNL/ImprovedCameraSE-NG as reference which also hides arms using nodes
    class NodeHider
    {
    public:
        NodeHider(NodeHider &) = delete;
        void operator=(const NodeHider &) = delete;
        static NodeHider* GetSingleton();

        void HideArms(RE::Actor* a_actor);
        void ShowArms(RE::Actor* a_actor);

        void HideWeapons(RE::Actor* a_actor);
        void ShowWeapons(RE::Actor* a_actor);

        void Setup();
    protected:
        NodeHider(){}
        ~NodeHider(){}

        static NodeHider* _this;
    };

    //papyrus interface
    void HideWeapons(PAPYRUSFUNCHANDLE,RE::Actor* a_actor);
    void ShowWeapons(PAPYRUSFUNCHANDLE,RE::Actor* a_actor);
}