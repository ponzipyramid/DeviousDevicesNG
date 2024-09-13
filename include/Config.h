#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "Utils.h"

namespace DeviousDevices
{
    class ConfigManager
    {
    SINGLETONHEADER(ConfigManager)
    public:
        void Setup();

        void SetLoggingDisable(bool a_val);
        bool GetLoggingDisable() const;

        template<typename T> T GetVariable(std::string a_name, T a_def) const;
        template<typename T> std::vector<T> GetArray(std::string a_name, std::string a_sep = ",") const;
        std::vector<std::string> GetArrayText(std::string a_name, bool a_lowercase, std::string a_sep = ",") const;
    private:
        bool _loaded = false;
        boost::property_tree::ptree _config;
        mutable std::unordered_map<std::string,void*> _catche;
        mutable Spinlock _lock;
        std::vector<std::string> GetArrayRaw(std::string a_name, bool a_tolower, std::string a_sep = ",") const;
        bool _LogDisable = false;
    };
}