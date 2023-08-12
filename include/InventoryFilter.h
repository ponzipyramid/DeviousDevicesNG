#pragma once

#include <RE/Skyrim.h>
#include <REL/Relocation.h>


#if (DD_USEINVENTORYFILTER_S == 1U)
namespace DeviousDevices
{
    class InventoryFilter
    {
    public:
        InventoryFilter(InventoryFilter &) = delete;
        void operator=(const InventoryFilter &) = delete;
        static InventoryFilter* GetSingleton();

        void Setup();
        void HookMethodsIM();
        void HookMethodsFM();

        bool PlayerHaveGag();

    protected:
        InventoryFilter(){}
        ~InventoryFilter(){}


    private:
        bool _hookedIM = false;
        bool _hookedFM = false;

        bool _init = false;
        static  InventoryFilter* _this;
        static  void PostDisplayIM(RE::InventoryMenu* a_this);
        static  inline REL::Relocation<decltype(PostDisplayIM)> PostDisplayIM_old;

        static  void PostDisplayFM(RE::FavoritesMenu* a_this);
        static  inline REL::Relocation<decltype(PostDisplayFM)> PostDisplayFM_old;

        std::vector<RE::BGSKeyword*>    _gagkeyword;
        std::vector<RE::BGSKeyword*>    _gagringkeyword;
        std::vector<RE::BGSKeyword*>    _gagpanelkeyword;
        RE::TESFaction*                 _gagpanelfaction;
    };


    class MenuEvent : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
    {
        MenuEvent() = default;
        MenuEvent(const MenuEvent&) = delete;
        MenuEvent(MenuEvent&&) = delete;
        MenuEvent& operator=(const MenuEvent&) = delete;
        MenuEvent& operator=(MenuEvent&&) = delete;

    public:
        static MenuEvent* GetSingleton() {
            static MenuEvent singleton;
            return &singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*); 

    };
}
#endif