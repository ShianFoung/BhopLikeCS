//#include "Config.h"
//
//Config* Config::GetInstance()
//{
//	if (Config::_Instance == nullptr)
//		Config::_Instance = new Config();
//
//	return Config::_Instance;
//}
//
//json* Config::_GetDefaultConfig()
//{
//	return nullptr;
//}
//
//Config::Config()
//{
//	if (!this->_readConfig())
//		this->_json = this->_GetDefaultConfig();
//
//	json::value_type a = this->_json->at("A");
//}
//
//
//bool Config::_readConfig()
//{
//	std::ifstream jsonFileStream("settings.json");
//
//	if (!jsonFileStream.is_open())
//		return false;
//
//	json jsonData = json::parse(jsonFileStream);
//	this->_json = &jsonData;
//
//	return true;
//}