#pragma once

#include <string>

namespace DeviousDevices {
    struct Position {
        std::vector<std::string> info;

        std::string key;
        inline std::string GetKey(std::unordered_map<std::string, std::size_t> info_map) {
            if (!key.empty()) return key;

            std::string tempKey(info_map.size(), '0');

            for (auto& infoVal : info) {
                tempKey[info_map[infoVal]] = '1';
            }

            key = tempKey;

            return key;
        }
    };

    struct Animation {
        std::string name;
        std::vector<Position> positions;

        std::vector<std::pair<std::string, std::unordered_map<int, int>>> orderings;

        inline std::vector<std::pair<std::string, std::unordered_map<int, int>>> GetOrderings(
            std::unordered_map<std::string, std::size_t> info_map) {

            // TODO: use string views to speed up this logic

            if (!orderings.empty()) return orderings;

            std::vector<std::pair<std::string, int>> posKeys;
            posKeys.reserve(positions.size());
            

            for (int i = 0; i < positions.size(); i++) {
                auto& pos = positions[i];
                posKeys.push_back(std::pair(pos.GetKey(info_map), i));
            }
            
            std::unordered_set<std::string> seen;

            do {
                std::string key;
                std::unordered_map<int, int> ordering;

                for (int i = 0; i < posKeys.size(); i++) {
                    auto& [posKey, index] = posKeys[i];
                    key += posKey;
                    ordering[i] = index;
                }

                for (int i = 0; i < (5 - positions.size()) * info_map.size(); i++) {
                    key += '0';
                }

                if (!seen.contains(key)) {
                    orderings.push_back(std::pair(key, ordering));
                    seen.insert(key);
                }

            } while (std::next_permutation(posKeys.begin(), posKeys.end()));

            return orderings;
        }
    };
}