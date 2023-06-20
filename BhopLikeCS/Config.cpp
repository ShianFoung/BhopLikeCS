#include "../Header.h"

#include "Config.h"

ConsoleSettings Config::consoleSettings = ConsoleSettings();
WindowSettings Config::windowSettings = WindowSettings();
GameSettings Config::gameSettings = GameSettings();

void Config::Init()
{
	if (Config::isInitialized)
		return;

	Config::isInitialing = Config::isInitialized = true;

	std::ifstream configFile(Config::FILE_NAME);

	if (!configFile.is_open())
	{
		configFile.close();
		Config::addMessage("Cannot open 'config.json' file, create new one.\n");
		Config::ResetAndSave();
		return;
	}

	try
	{
		Json json = Json::parse(configFile);
		Config::consoleSettings = json["consoleSettings"].template get<ConsoleSettings>();
		Config::windowSettings = json["windowSettings"].template get<WindowSettings>();
		Config::gameSettings = json["gameSettings"].template get<GameSettings>();
		return;
	}
	catch (std::exception& e)
	{
		Config::addMessage(e.what());
		Config::addMessage("Cannot parse 'config.json', create new one.");
	}

	Config::ResetAndSave();
	Config::isInitialing = false;
}

void Config::Reset()
{
	Config::consoleSettings = ConsoleSettings();
	Config::windowSettings = WindowSettings();
	Config::gameSettings = GameSettings();
}

void Config::Save()
{
	if (!Config::isInitialized)
		return;

	std::ofstream configFile(Config::FILE_NAME, std::ios::out | std::ios::trunc);

	if (!configFile.is_open())
	{
		Config::addMessage("Cannot save 'config.file'.");
		return;
	}

	Json json = {  };
	json["consoleSettings"] = Config::consoleSettings;
	json["windowSettings"] = Config::windowSettings;
	json["gameSettings"] = Config::gameSettings;

	configFile << json.dump(4);
	configFile.close();

	Config::addMessage("'config.json' saved.");
	Config::Flush();
}

void Config::ResetAndSave()
{
	Config::Reset();
	Config::Save();
}

void Config::Flush()
{
	if (Config::isInitialing)
		return;

	for (const std::string& message : Config::outputBuffer)
		std::cout << message << '\n';

	Config::outputBuffer.clear();
}

void Config::addMessage(const char* message)
{
	Config::outputBuffer.push_back(std::string(message));
}

const char* Config::FILE_NAME = "config.json";

bool Config::isInitialing = false;
bool Config::isInitialized = false;
std::vector<std::string> Config::outputBuffer;
