#pragma once

namespace DeviousDevices
{
    #define NH_UPDTIME 0.5f   // update every 0.5s

    //#define NH_IMPARMHIDER

    //for implementing this, I used https://github.com/ArranzCNL/ImprovedCameraSE-NG as reference which also hides arms using nodes
    class NodeHider
    {
    SINGLETONHEADER(NodeHider)
    public:
        class NodeHiderSlot
        {
        public:
            bool                        enabled     = true;
            std::vector<std::string>    nodes;
            float                       timer       = 0.0f;
        };

        #ifdef NH_IMPARMHIDER
        void HideArms(RE::Actor* a_actor);
        void ShowArms(RE::Actor* a_actor);
        #endif

        //https://wiki.beyondskyrim.org/wiki/Arcane_University:Nifskope_Weapons_Setup
        

        void HideWeapons(RE::Actor* a_actor);
        void ShowWeapons(RE::Actor* a_actor);

        void Setup();
        void Update();
    protected:
        bool ActorIsValid(RE::Actor* a_actor) const;
        bool ShouldHideWeapons(RE::Actor* a_actor) const;
        bool AddHideNode(RE::Actor* a_actor, std::string a_nodename);
        bool RemoveHideNode(RE::Actor* a_actor, std::string a_nodename);

    private:
        bool _installed = false;
        std::vector<uint32_t> _lastupdatestack;
        std::vector<std::string> _WeaponNodes;
    };

    //papyrus interface
    inline void HideWeapons(PAPYRUSFUNCHANDLE,RE::Actor* a_actor)
    {
        //NodeHider::GetSingleton()->HideWeapons(a_actor);
    }

    inline void ShowWeapons(PAPYRUSFUNCHANDLE,RE::Actor* a_actor)
    {
        //NodeHider::GetSingleton()->ShowWeapons(a_actor);
    }
}