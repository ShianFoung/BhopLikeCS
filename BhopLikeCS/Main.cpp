#define _CRT_SECURE_NO_WARNINGS

#include "Engine.h"

#include <Windows.h>
#include <iostream>

#pragma warning(push)
#pragma warning(disable : 6031; disable : 28251)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
#ifdef _DEBUG
	// 開Console並重導基本輸入輸出
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
#endif

	// 強制讓Engine在關閉視窗時直接呼叫解構子
	{
		Engine engine(1280, 720, false);
		engine.Run();
	}

#ifdef _DEBUG
	// 卡住Console讓他不關閉，以便檢視訊息
	std::cin.get();
#endif

	return 0;
}

#pragma warning(pop)
