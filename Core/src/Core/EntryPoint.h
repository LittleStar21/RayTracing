#pragma once

#ifdef PLATFORM_WINDOWS

extern Core::Application *Core::CreateApplication(int argc, char **argv);
bool g_ApplicationRunning = true;

namespace Core
{

	int Main(int argc, char **argv)
	{
		while (g_ApplicationRunning)
		{
			Core::Application *app = Core::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#ifdef APP_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Core::Main(__argc, __argv);
}

#else

int main(int argc, char **argv)
{
	return Core::Main(argc, argv);
}

#endif // APP_DIST

#endif // PLATFORM_WINDOWS
