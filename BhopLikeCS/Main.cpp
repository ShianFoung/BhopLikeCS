#define _CRT_SECURE_NO_WARNINGS

#include "Engine.h"

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

	// �j����Engine�b���������ɪ����I�s�Ѻc�l
	{
		Engine engine(1280, 720, false);
		engine.Run();
	}

	// �d��Console���L�������A�H�K�˵��T��
	std::cin.get();

	return 0;
}

#pragma warning(pop)
