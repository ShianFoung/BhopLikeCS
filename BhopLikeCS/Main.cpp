#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"

#include <Windows.h>
#include <iostream>

#pragma warning(push)
#pragma warning(disable : 6031; disable : 28251)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
#ifdef _DEBUG
	// �}Console�í��ɰ򥻿�J��X
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
#endif

	Game game(1280, 720, false);
	game.Run();

#ifdef _DEBUG
	// �d��Console���L�������A�H�K�˵��T��
	std::cout << "Press Enter key to exit..." << std::endl;
	std::cin.get();
#endif

	return 0;
}

#pragma warning(pop)
