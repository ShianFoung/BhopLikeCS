#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"

#include <Windows.h>
#include <iostream>
#include <glm/glm.hpp>

#pragma comment(lib, "imm32.lib")

#pragma warning(push)
#pragma warning(disable : 6031; disable : 28251)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
#ifdef _DEBUG
	// �} Console �í��ɰ򥻿�J��X
	// �ѩ� #define _CRT_SECURE_NO_WARNINGS �����Y�� freopen ���|����
	// ���M���`�����n�� freopen_s �~�� (�w���ʰ��D)
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);

	// �N Console ���W������m�]�w��ù��� (10, 10) ��m
	HWND consoleWnd = GetConsoleWindow();
	SetWindowPos(consoleWnd, HWND_TOP, 10, 10, 0, 0, SWP_NOSIZE);
#endif
	// ���}�C�������e���N Microsoft ����J�k�j���
	ImmDisableIME(GetCurrentThreadId());
	
	// �ҰʹC��
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
