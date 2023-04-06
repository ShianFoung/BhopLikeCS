#pragma once

#include <Windows.h>

class Engine
{
public:
	Engine();
	~Engine();

	int Run();
	void Update();
	void Render();
private:
	int width;
	int height;
};