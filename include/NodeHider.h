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
        enum ArmState : uint8_t
        {
            sShown  = 0,
            sHidden = 1
        };

        void HideArms(RE::Actor* a_actor);
        void ShowArms(RE::Actor* a_actor);
        void UpdateArms(RE::Actor* a_actor);

        //https://wiki.beyondskyrim.org/wiki/Arcane_University:Nifskope_Weapons_Setup
        void HideWeapons(RE::Actor* a_actor);
        void ShowWeapons(RE::Actor* a_actor);

        void Setup();
        void Update();
        void Reload();
    protected:
        bool ActorIsValid(RE::Actor* a_actor) const;
        bool ShouldHideWeapons(RE::Actor* a_actor) const;
        bool AddHideNode(RE::Actor* a_actor, std::string a_nodename);
        bool RemoveHideNode(RE::Actor* a_actor, std::string a_nodename);

    private:
        bool _installed = false;
        std::vector<uint32_t> _lastupdatestack;
        std::vector<std::string> _WeaponNodes;
        std::vector<std::string> _ArmNodes;
        std::unordered_map<uint32_t,ArmState> _armhiddenstates;
        RE::BGSKeyword* _straitjacket;
    };
}