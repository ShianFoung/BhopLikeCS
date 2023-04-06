#include <Windows.h>

#include "Engine.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Engine engine;

	return engine.Run();
}