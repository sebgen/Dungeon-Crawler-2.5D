#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#define SDL_MAIN_HANDLED

#include <iostream>
#include <sdl2/SDL.h>
#include <Windows.h>

SDL_Window* WindowSDLWindow;
SDL_Renderer* WindowSDLRenderer;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hds = BeginPaint(hwnd, &ps);

		SDL_SetRenderDrawColor(WindowSDLRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(WindowSDLRenderer);
		SDL_RenderPresent(WindowSDLRenderer);

		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow)
int main()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MyWIndowClass";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"MyWIndowClass",
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	WindowSDLWindow = SDL_CreateWindowFrom(hwnd);
	WindowSDLRenderer = SDL_CreateRenderer(WindowSDLWindow, -1, SDL_RENDERER_ACCELERATED);

	HWND hwndButton = CreateWindow("BUTTON", "OK", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 10, 100, 100, hwnd, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

	ShowWindow(hwnd, TRUE);
	UpdateWindow(hwnd);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* SDLWindow = SDL_CreateWindowFrom(hwndButton);
	SDL_Renderer* SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDLRenderer);
	SDL_RenderPresent(SDLRenderer);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}