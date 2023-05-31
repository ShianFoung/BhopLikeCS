#include "Header.h"

#include <Windows.h>

#include "Game.h"

int g_WindowWidth;
int g_WindowHeight;
bool g_WindowFullscrean;
float g_ResolutionAspectRatio;
int g_WindowHalfWidth;
float g_WindowHalfWidthFloat;
int g_WindowHalfHeight;
float g_WindowHalfHeightFloat;

void LoadConfig();

// �{���i�J�I
// �q�`���ӬO int main �~��A���]���ڱM�ת���X�O Windows �Ӥ��O Console�A
// �ҥH�n�ϥ� WinMain ��@�i�J�I�A���M�|�����C
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#ifdef _DEBUG
	// �} Console �í��ɰ򥻿�J��X
	AllocConsole();

	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);
	freopen_s(&stream, "CONIN$", "r", stdin);

	// �N Console ���W������m�]�w��ù��� (10, 10) ��m
	HWND consoleWnd = GetConsoleWindow();
	SetWindowPos(consoleWnd, HWND_TOP, 10, 10, 0, 0, SWP_NOSIZE);
#endif
	// ���}�C�������e���N Microsoft ����J�k�j���
	ImmDisableIME(GetCurrentThreadId());

	// Ū���]�w��
	LoadConfig();
	
	// �ҰʹC��
	// �p�G�]�w�����ù����檺�ܡA�]�w�����e���N�|�����A�����ϥΥD�ù������e
	Game game("Bhop Like CS", g_WindowWidth, g_WindowHeight, g_WindowFullscrean);
	// �]�w�C�� fps �P tickrate �� 128
	// �p�G fps �P tickrate ���P���ܡA�]�p�W�|�x���ܦh... (�ڤ��|���e������)
	// �ҥH�N²�檺�]�w���@�˪��ƭȡA��K��s�@
	game.Run(128);

#ifdef _DEBUG
	// �d��Console���L�������A�H�K�˵��T��
	std::cout << "Press Enter key to exit..." << std::endl;
	std::cin.get();
#endif

	return 0;
}

void LoadConfig()
{
	Config* config = &Config::GetInstance();
	config->Init();

	json windowSettings = config->Data()["windowSettings"];
	g_WindowWidth = windowSettings["width"];
	g_WindowHeight = windowSettings["height"];
	g_WindowFullscrean = windowSettings["fullscreen"];
	g_ResolutionAspectRatio = 1.0f * g_WindowWidth * g_WindowHeight;
	g_WindowHalfWidth = g_WindowWidth / 2;
	g_WindowHalfWidthFloat = static_cast<float>(g_WindowHalfWidth);
	g_WindowHalfHeight = g_WindowHeight / 2;
	g_WindowHalfHeightFloat = static_cast<float>(g_WindowHalfHeight);
}
