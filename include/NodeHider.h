#pragma once

#include "Utils.h"

namespace DeviousDevices
{
    //for implementing this, I used https://github.com/ArranzCNL/ImprovedCameraSE-NG as reference which also hides arms using nodes
    class NodeHider
    {
    SINGLETONHEADER(NodeHider)
    public:
        enum HidderState : uint8_t
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
        void UpdateWeapons(RE::Actor* a_actor);
        void UpdatePlayer(RE::Actor* a_actor);
        void Setup();
        //void Update();
        void UpdateTimed(RE::Actor* a_actor);
        void Reload();

        void CleanUnusedActors();
        void IncUpdateCounter();

        Spinlock SaveLock;
    protected:
        bool ActorIsValid(RE::Actor* a_actor) const;
        bool ShouldHideWeapons(RE::Actor* a_actor) const;
        bool AddHideNode(RE::Actor* a_actor, std::string a_nodename);
        bool RemoveHideNode(RE::Actor* a_actor, std::string a_nodename);
    private:
        bool _installed = false;
        RE::BGSKeyword*             _straitjacket;
        std::vector<uint32_t>       _lastupdatestack;
        std::vector<std::string>    _WeaponNodes;
        std::vector<std::string>    _ArmNodes;
        std::unordered_map<uint32_t,HidderState> _armhiddenstates;    //temporary array with state of arm nodes on updated actors
        std::unordered_map<uint32_t,HidderState> _weaponhiddenstates; //temporary array with state of weapon nodes on updated actors
        std::unordered_map<uint32_t,std::unordered_map<std::string,HidderState>> _weaponnodestates; //temporary array with states of weapon nodes on updated actors
        uint64_t                    _UpdateCounter = 0UL;
        std::unordered_map<RE::Actor*,UpdateHandle> _UpdatedActors;
        std::vector<std::string>    _ArmHiddingKeywords;
        
    };

    inline void HideWeapons(PAPYRUSFUNCHANDLE, RE::Actor* a_actor) {
        LOG("HideWeapons called")
        UniqueLock lock(NodeHider::GetSingleton()->SaveLock);
        NodeHider::GetSingleton()->HideWeapons(a_actor);
    }

    inline void ShowWeapons(PAPYRUSFUNCHANDLE, RE::Actor* a_actor) {
        LOG("ShowWeapons called")
        UniqueLock lock(NodeHider::GetSingleton()->SaveLock);
        NodeHider::GetSingleton()->ShowWeapons(a_actor);
    }
}