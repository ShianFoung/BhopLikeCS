#include "../Header.h"

#include <Windows.h>

#include "Game.h"

// �{���i�J�I
// �q�`���ӬO int main �~��A���]���ڧƱ� Console �i�H�ۥѪ��}���A
// �ҥH�ڧ�M�ת���X�զ� Windows �Ӥ��O Console�A�åB�n�ϥ� WinMain ��@�i�J�I�A���M�|�����C
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ���}�C�������e���N Microsoft ����J�k�j���
	ImmDisableIME(GetCurrentThreadId());

	// Ū���]�w��
	Config::Init();

	// �} Console �í��ɰ򥻿�J��X
	if (Config::consoleSettings.openConsole)
	{
		AllocConsole();

		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);
		freopen_s(&stream, "CONIN$", "r", stdin);

		// �N Console ���W������m�]�w�� Config �]�w����m
		HWND consoleWnd = GetConsoleWindow();
		SetWindowPos(consoleWnd, HWND_TOP, Config::consoleSettings.xPosition, Config::consoleSettings.yPosition, 0, 0, SWP_NOSIZE);
	}

	// �N Config ���T����X
	Config::Flush();
	
	// �ҰʹC��
	// �p�G�]�w�����ù����檺�ܡA�]�w�����e���N�|�����A�����ϥΥD�ù������e
	Game game("Bhop Like CS", Config::windowSettings.width, Config::windowSettings.height, Config::windowSettings.fullscreen);
	// �]�w�C�� fps �P tickrate ���@�˪��ƭ�
	// �p�G fps �P tickrate ���P���ܡA�]�p�W�|�x���ܦh... (�ڤ��|���e������)
	// �ҥH�N²�檺�]�w���@�˪��ƭȡA��K��s�@
	game.Run(Config::gameSettings.tickrateAndFps);

	if (Config::consoleSettings.openConsole)
	{
		// �d��Console���L�������A�H�K�˵��T��
		std::cout << "Press Enter key to exit..." << std::endl;
		std::cin.get();
	}

	return 0;
}
