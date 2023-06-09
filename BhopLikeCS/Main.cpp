#include "../Header.h"

#include <Windows.h>

#include "Game.h"

// 程式進入點
// 通常應該是 int main 才對，但因為我希望 Console 可以自由的開關，
// 所以我把專案的輸出調成 Windows 而不是 Console，並且要使用 WinMain 當作進入點，不然會報錯。
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// 打開遊戲視窗前先將 Microsoft 的輸入法強制停用
	ImmDisableIME(GetCurrentThreadId());

	// 讀取設定檔
	Config::Init();
	// 這邊直接做儲存是因為之後還會增加設定，所以載入 Config 後儲存可以直接把新設定存入。
	Config::Save();

	if (Config::consoleSettings.openConsole)
	{
		// 開 Console 並重導基本輸入輸出
		AllocConsole();

		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);
		freopen_s(&stream, "CONOUT$", "w", stderr);
		freopen_s(&stream, "CONIN$", "r", stdin);

		// 將 Console 左上角的位置設定到 Config 設定的位置
		HWND consoleWnd = GetConsoleWindow();
		SetWindowPos(consoleWnd, HWND_TOP, Config::consoleSettings.xPosition, Config::consoleSettings.yPosition, 0, 0, SWP_NOSIZE);
	}
	
	// 啟動遊戲
	// 如果設定成全螢幕執行的話，設定的長寬高將會忽略，直接使用主螢幕的長寬
	Game game("Bhop Like CS", Config::windowSettings.width, Config::windowSettings.height, Config::windowSettings.fullscreen);
	// 設定遊戲 fps 與 tickrate 為 128
	// 如果 fps 與 tickrate 不同的話，設計上會困難很多... (我不會做畫面平滑)
	// 所以就簡單的設定成一樣的數值，方便於製作
	game.Run(Config::gameSettings.tickrateAndFps);

	if (Config::consoleSettings.openConsole)
	{
		// 卡住Console讓他不關閉，以便檢視訊息
		std::cout << "Press Enter key to exit..." << std::endl;
		std::cin.get();
	}

	return 0;
}
