#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>

#include "Header.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_truetype.h>

#include "Game.h"

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
	// �p�G�]�w�����ù����檺�ܡA�]�w�����e���N�|�����A�����ϥΥD�ù������e
	Game game("Bhop Like CS", 1280, 720, false);
	// �]�w�C�� fps �P tickrate �� 128
	// �p�G fps �P tickrate ���P���ܡA�]�p�W�|�x���ܦh... (�ڤ��|���e������)
	// �ҥH�N²�檺�]�w���@�˪��ƭȡA��K�s�@ �~�~
	game.Run(128);

#ifdef _DEBUG
	// �d��Console���L�������A�H�K�˵��T��
	std::cout << "Press Enter key to exit..." << std::endl;
	std::cin.get();
#endif

	return 0;
}

#pragma warning(pop)
