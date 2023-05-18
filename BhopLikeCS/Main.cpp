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
	// 開 Console 並重導基本輸入輸出
	// 由於有 #define _CRT_SECURE_NO_WARNINGS 的關係讓 freopen 不會報錯
	// 不然正常來講要用 freopen_s 才行 (安全性問題)
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);

	// 將 Console 左上角的位置設定到螢幕的 (10, 10) 位置
	HWND consoleWnd = GetConsoleWindow();
	SetWindowPos(consoleWnd, HWND_TOP, 10, 10, 0, 0, SWP_NOSIZE);
#endif
	// 打開遊戲視窗前先將 Microsoft 的輸入法強制停用
	ImmDisableIME(GetCurrentThreadId());
	
	// 啟動遊戲
	// 如果設定成全螢幕執行的話，設定的長寬高將會忽略，直接使用主螢幕的長寬
	Game game("Bhop Like CS", 1280, 720, false);
	// 設定遊戲 fps 與 tickrate 為 128
	// 如果 fps 與 tickrate 不同的話，設計上會困難很多... (我不會做畫面平滑)
	// 所以就簡單的設定成一樣的數值，方便製作 ㄏㄏ
	game.Run(128);

#ifdef _DEBUG
	// 卡住Console讓他不關閉，以便檢視訊息
	std::cout << "Press Enter key to exit..." << std::endl;
	std::cin.get();
#endif

	return 0;
}

#pragma warning(pop)
