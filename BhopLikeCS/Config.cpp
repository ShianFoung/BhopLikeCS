#include "../Header.h"

#include "Config.h"

//void Config::Init()
//{
//    this->isInitialized = true;
//    std::ifstream configFile(FILE_NAME);
//
//    if (configFile.is_open())
//    {
//        this->jsonData = json::parse(configFile);
//        return;
//    }
//
//    this->jsonData = Config::staticGetDefaultConfig();
//    this->Save();
//}
//
//json& Config::Data()
//{
//    return this->jsonData;
//}
//
//bool Config::Save()
//{
//    std::ofstream configFile(FILE_NAME, std::ios::out | std::ios::trunc);
//
//    if (configFile.is_open())
//    {
//        configFile << this->jsonData.dump(4);
//        return true;
//    }
//    
//    return false;
//}
//
//json Config::staticGetDefaultConfig()
//{
//    json defaultJson = {
//        { "windowSettings", {
//            { "width", 1280 },
//            { "height", 720 },
//            { "fullscreen", false }
//        }},
//        { "gameSettings", {
//            { "tickrateAndFps", 128 }
//        }}
//    };
//
//    return defaultJson;
//}
//
//Config::Config() {  }
//
//Config::~Config() {  }
