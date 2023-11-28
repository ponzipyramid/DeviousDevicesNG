#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace DeviousDevices
{
    class ConfigManager
    {
    SINGLETONHEADER(ConfigManager)
    public:
        void Setup();

        template<typename T> T GetVariable(std::string a_name, T a_def) const;
        template<typename T> std::vector<T> GetArray(std::string a_name, std::string a_sep = ",") const;
    private:
        bool _loaded = false;
        boost::property_tree::ptree _config;
        mutable std::unordered_map<std::string,void*> _catche;
        std::vector<std::string> GetArrayRaw(std::string a_name, std::string a_sep = ",") const;
    };
}