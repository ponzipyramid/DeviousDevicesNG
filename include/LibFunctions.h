#pragma once
#include <RE/Skyrim.h>
#include <DeviceReader.h>

namespace DeviousDevices
{
    //copy of RE::InventoryChanges::IItemChangeVisitor, with full definition so it can be inherited from
    class IItemChangeVisitor
    {
    public:
        virtual ~IItemChangeVisitor(){}  // 00

        // add
        virtual RE::BSContainer::ForEachResult Visit(RE::InventoryEntryData* a_entryData) {return RE::BSContainer::ForEachResult::kContinue;}; // 01
        virtual bool ShouldVisit([[maybe_unused]] RE::InventoryEntryData* a_entryData, [[maybe_unused]] RE::TESBoundObject* a_object) { return true; }  // 02
        virtual RE::BSContainer::ForEachResult Unk_03(RE::InventoryEntryData* a_entryData, [[maybe_unused]] void* a_arg2, bool* a_arg3) // 03
        {
            *a_arg3 = true;
            return Visit(a_entryData);
        }

        RE::InventoryChanges::IItemChangeVisitor& AsNativeVisitor(){return *(RE::InventoryChanges::IItemChangeVisitor*)this;}
    };
    static_assert(sizeof(IItemChangeVisitor) == 0x8);

    // Visitor for worn devices
    class WornVisitor : public IItemChangeVisitor
    {
    public:
        WornVisitor(std::function<RE::BSContainer::ForEachResult(RE::InventoryEntryData*)> a_fun) : _fun(a_fun) {};

        virtual RE::BSContainer::ForEachResult Visit(RE::InventoryEntryData* a_entryData) override
        {
            return _fun(a_entryData);
        }
    private:
        std::function<RE::BSContainer::ForEachResult(RE::InventoryEntryData*)> _fun;
    };


    class LibFunctions
    {
    SINGLETONHEADER(LibFunctions)
    public:
        void Setup();
        std::vector<RE::TESObjectARMO*> GetDevices(RE::Actor* a_actor, int a_mode, bool a_worn);
        RE::TESObjectARMO* GetWornDevice(RE::Actor* a_actor, RE::BGSKeyword* a_kw, bool a_fuzzy);
        RE::TESObjectARMO* GetHandRestrain(RE::Actor* a_actor);
        bool IsBound(RE::Actor* a_actor) const;
        bool WornHasKeyword(RE::Actor* a_actor, RE::BGSKeyword* a_kw) const;
        RE::TESObjectARMO* GetWornArmor(RE::Actor* a_actor,int a_mask) const;
        bool IsAnimating(RE::Actor* a_actor);
        bool PluginInstalled(std::string a_dll);
    private:
        bool _installed = false;
        std::vector<RE::BGSKeyword*>    _idkw;
        std::vector<RE::BGSKeyword*>    _rdkw;
        RE::BGSKeyword*                 _hbkw;
        std::vector<RE::TESFaction*>    _animationfactions;
    };

    inline std::vector<RE::TESObjectARMO*> GetDevices(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, int a_mode, bool a_worn)
    {
        LOG("GetDevices({},{},{}) called",a_actor ? a_actor->GetName() : "NONE",a_mode,a_worn)
        return LibFunctions::GetSingleton()->GetDevices(a_actor,a_mode,a_worn);
    }
    inline RE::TESObjectARMO* GetWornDevice(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, RE::BGSKeyword* a_kw, bool a_fuzzy) 
    {
        LOG("GetWornDevice({},{},{}) called",a_actor ? a_actor->GetName() : "NONE",a_kw ? a_kw->GetName() : "NONE",a_fuzzy)
        return LibFunctions::GetSingleton()->GetWornDevice(a_actor, a_kw, a_fuzzy);
    }

    inline bool PluginInstalled(PAPYRUSFUNCHANDLE,std::string a_dll)
    {
        LOG("GetWornDevice({}) called",a_dll)
        return LibFunctions::GetSingleton()->PluginInstalled(a_dll);
    }
}