#include "Animation/Registry.h"
#include <jsoncons/json.hpp>

using namespace DeviousDevices;
using namespace jsoncons;

SINGLETONBODY(Registry)

namespace {
    bool IsDirValid(std::string dir) {
        bool valid = true;
        struct stat info;
        const char* cstr = dir.c_str();
        if (stat(cstr, &info) != 0) {
            return false;
        } else if (!(info.st_mode & S_IFDIR)) {
            return false;
        }

        return true;
    }

    void AddInfo(std::unordered_map<std::string, std::size_t>& tag_map, std::string tag) {
        if (!tag_map.count(tag)) {
            tag_map[tag] = tag_map.size();
        }
    }
}

void Registry::Setup() {
    LOG("Registry::Setup(): START")

	std::string dir("Data\\SKSE\\Plugins\\DD\\Registry");
    std::string ext("json");

    std::unordered_set<std::string> skipInfo{"submissive", "vampire", "climax", "dead"};
    std::unordered_map<std::string, std::size_t> tag_map;

    for (const auto& p : std::filesystem::directory_iterator(dir)) {
        auto fileName = p.path();

        LOG("Registry::Setup(): Found {}", fileName.string());

        if (fileName.extension().string().ends_with(ext)) {
            LOG("Registry::Setup(): Parsing {}", fileName.string());
            std::ifstream is(fileName.string());
            auto j = json::parse(is);
            auto scenes = j["scenes"];
            for (const auto& keyValue : scenes.object_range()) {
                auto scene = keyValue.value();
                auto positions = scene["stages"][0]["positions"];

                Animation anim;
                anim.name = scene["name"].as<std::string>();
                
                LOG("Registry::Setup(): Adding animation {}", anim.name)
                for (auto& pos : positions.array_range()) {
                    Position new_pos;
                    
                    // gender data
                    for (const auto& genData : pos["sex"].object_range()) {
                        if (genData.value().as<bool>()) {
                            std::string gender = genData.key();
                            new_pos.info.push_back(gender);
                            AddInfo(tag_map, gender);
                        }
                    }

                    // race data
                    auto race = pos["race"].as<std::string>();
                    new_pos.info.push_back(race);
                    AddInfo(tag_map, race);

                    // restraint data 
                    for (const auto& extraData : pos["extra"].object_range()) {
                        if (!skipInfo.contains(extraData.key()) && extraData.value().as<bool>()) {
                            std::string info = extraData.key();
                            new_pos.info.push_back(info);
                            AddInfo(tag_map, info);
                        }
                    }

                    anim.positions.push_back(new_pos);
                }


                _animations[anim.name] = anim;
            }
        }

        for (auto& [name, anim] : _animations) {
            auto orderings = anim.GetOrderings(tag_map);
            for (auto& [key, ordering] : orderings) {
                LOG("Registry::Setup(): Storing animation {} under key {}", anim.name, key)

                _anim_table[key].push_back(std::pair(name, ordering));
            }
        }

    }
    LOG("Registry::Setup(): END")
}