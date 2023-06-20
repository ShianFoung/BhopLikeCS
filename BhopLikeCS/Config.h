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
	static void Reset();
	static void Save();
	static void ResetAndSave();
	static void Flush();
private:
	static const char* FILE_NAME;

	static bool isInitialing;
	static bool isInitialized;
	static std::vector<std::string> outputBuffer;

	Config() = delete;

	static void addMessage(const char* message);
};
