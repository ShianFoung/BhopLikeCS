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

// 程式進入點
// 通常應該是 int main 才對，但因為我專案的輸出是 Windows 而不是 Console，
// 所以要使用 WinMain 當作進入點，不然會報錯。
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#ifdef _DEBUG
	// 開 Console 並重導基本輸入輸出
	AllocConsole();

	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);
	freopen_s(&stream, "CONIN$", "r", stdin);

	// 將 Console 左上角的位置設定到螢幕的 (10, 10) 位置
	HWND consoleWnd = GetConsoleWindow();
	SetWindowPos(consoleWnd, HWND_TOP, 10, 10, 0, 0, SWP_NOSIZE);
#endif
	// 打開遊戲視窗前先將 Microsoft 的輸入法強制停用
	ImmDisableIME(GetCurrentThreadId());

	// 讀取設定檔
	LoadConfig();
	
	// 啟動遊戲
	// 如果設定成全螢幕執行的話，設定的長寬高將會忽略，直接使用主螢幕的長寬
	Game game("Bhop Like CS", g_WindowWidth, g_WindowHeight, g_WindowFullscrean);
	// 設定遊戲 fps 與 tickrate 為 128
	// 如果 fps 與 tickrate 不同的話，設計上會困難很多... (我不會做畫面平滑)
	// 所以就簡單的設定成一樣的數值，方便於製作
	game.Run(128);

#ifdef _DEBUG
	// 卡住Console讓他不關閉，以便檢視訊息
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
