#pragma once

#include "Json/Settings/ConsoleSettings.h"
#include "Json/Settings/WindowSettings.h"
#include "Json/Settings/GameSettings.h"

class Config
{
public:
	static ConsoleSettings consoleSettings;
	static WindowSettings windowSettings;
	static GameSettings gameSettings;

	static void Init();
	static void Save();
private:
	static const char* FILE_NAME;

	static bool isInitialized;

	Config() = delete;
};
