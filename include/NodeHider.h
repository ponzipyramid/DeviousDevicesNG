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
        const std::vector<std::string> WeaponNodes = 
        {
            "QUIVER",
            "SHIELD",
            "WeaponAxe",
            "WeaponBack",
            "WeaponBow",
            "WeaponDagger",
            "WeaponMace",
            "WeaponStaff",
            "WeaponSword"
        };

        void HideWeapons(RE::Actor* a_actor);
        void ShowWeapons(RE::Actor* a_actor);

        void Setup();

        void Update();
        bool ValidateActor(RE::Actor* a_actor);

    protected:

        bool AddHideNode(RE::Actor* a_actor, std::string a_nodename);
        bool RemoveHideNode(RE::Actor* a_actor, std::string a_nodename);

    private:
        std::map<uint32_t,NodeHiderSlot> _slots;
    };

    //papyrus interface
    void HideWeapons(PAPYRUSFUNCHANDLE,RE::Actor* a_actor);
    void ShowWeapons(PAPYRUSFUNCHANDLE,RE::Actor* a_actor);
}