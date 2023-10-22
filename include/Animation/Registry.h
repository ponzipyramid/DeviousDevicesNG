#pragma once
#include "Animation.h"

namespace DeviousDevices {
    class Registry {
        SINGLETONHEADER(Registry)
    public:
        void Setup();
    private:
        std::unordered_map<std::string, Animation> _animations;
        std::unordered_map<std::string, std::vector<std::pair<std::string, std::unordered_map<int, int>>>> _anim_table;
    };
}