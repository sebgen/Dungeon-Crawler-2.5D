#include "window.h"
#include <iostream>

namespace NativeUI
{
	WNDCLASSEX* Window::WindowClass = NULL;
	std::unordered_map<HWND, Window*> Window::mRegisteredWindows = std::unordered_map<HWND, Window*>();

	LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* window = mRegisteredWindows[hwnd];
		if (window == nullptr)
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		static PAINTSTRUCT ps;

		switch (msg)
		{
		case WM_SIZE:
			window->OnUserResize();
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_PAINT:
			//BeginPaint(hwnd, &ps);
			// RENDERING HERE
			//EndPaint(hwnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);;
	}

	void Window::CreateWindowClass()
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		WindowClass = new WNDCLASSEX();

		WindowClass->cbSize = sizeof(WNDCLASSEX);
		WindowClass->style = 0;
		WindowClass->lpfnWndProc = WndProc;
		WindowClass->cbClsExtra = 0;
		WindowClass->cbWndExtra = 0;
		WindowClass->hInstance = hInstance;
		WindowClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WindowClass->hCursor = LoadCursor(NULL, IDC_ARROW);
		WindowClass->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		WindowClass->lpszMenuName = NULL;
		WindowClass->lpszClassName = "NativeUWindowBase";
		WindowClass->hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(WindowClass))
		{
			MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		}
	}

	Window::Window()
		: Control(NULL)
	{
		if (WindowClass == NULL)
		{
			CreateWindowClass();
		}
		HINSTANCE hInstance = GetModuleHandle(NULL);

		mHwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			"NativeUWindowBase",
			"Window title",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
			NULL, NULL, hInstance, NULL);

		if (mHwnd == NULL)
		{
			MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		}
		else
		{
			mRegisteredWindows[mHwnd] = this;
			SetSize(Point(800.0f, 600.0f));
		}

	}

	void Window::Show()
	{
		ShowWindow(mHwnd, TRUE);
	}

	void Window::SetTitle(const char* arg_title)
	{
		SetWindowText(mHwnd, arg_title);
	}

	void Window::Maximize()
	{
		SendMessage(mHwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	}
}
