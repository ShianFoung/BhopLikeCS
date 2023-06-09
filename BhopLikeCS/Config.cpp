#include "../Header.h"

#include "Config.h"

ConsoleSettings Config::consoleSettings = ConsoleSettings();
WindowSettings Config::windowSettings = WindowSettings();
GameSettings Config::gameSettings = GameSettings();

void Config::Init()
{
	if (isInitialized)
		return;

	std::ifstream configFile(Config::FILE_NAME);

	if (!configFile.is_open())
	{
		configFile.close();
		std::cout << "Cannot open 'config.json' file, create new one.\n";
		Config::Save();
		return;
	}

	Json json = Json::parse(configFile);
	Config::consoleSettings.FromJson(json["consoleSettings"]);
	Config::windowSettings.FromJson(json["windowSettings"]);
	Config::gameSettings.FromJson(json["gameSettings"]);
}

void Config::Save()
{
	std::ofstream configFile(Config::FILE_NAME, std::ios::out | std::ios::trunc);

	if (!configFile.is_open())
	{
		std::cerr << "Cannot save 'config.file'.\n";
		return;
	}

	Json json = {  };
	Config::consoleSettings.ToJson(json["consoleSettings"]);
	Config::windowSettings.ToJson(json["windowSettings"]);
	Config::gameSettings.ToJson(json["gameSettings"]);

	configFile << json.dump(4);
	configFile.close();

	std::cout << "'config.json' saved.\n";
}

const char* Config::FILE_NAME = "config.json";

bool Config::isInitialized = false;
