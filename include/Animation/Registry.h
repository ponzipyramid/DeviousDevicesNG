#pragma once
#include "Animation.h"

namespace DeviousDevices {
    class Registry {
        SINGLETONHEADER(Registry)
    public:
        void Setup();
        std::string Filter(std::vector<RE::Actor*> actors);
    private:
        std::unordered_map<std::string, Animation> _animations;
        std::unordered_map<std::string, std::vector<std::pair<std::string, std::unordered_map<int, int>>>> _anim_table;
    };
}