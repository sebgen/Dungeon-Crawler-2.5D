#include "panel.h"

namespace NativeUI
{
	WNDCLASSEX* Panel::PanelClass = NULL;
	std::unordered_map<HWND, Panel*> Panel::RegisteredPanels = std::unordered_map<HWND, Panel*>();

	LRESULT CALLBACK Panel::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Panel* panel = RegisteredPanels[hwnd];
		if (panel == nullptr)
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		static PAINTSTRUCT ps;

		switch (msg)
		{
		case WM_SIZE:
			panel->OnResize();
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_PAINT:
			BeginPaint(hwnd, &ps);
			// RENDERING HERE
			EndPaint(hwnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}

	void Panel::CreatePanelClass()
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		PanelClass = new WNDCLASSEX();

		PanelClass->cbSize = sizeof(WNDCLASSEX);
		PanelClass->style = 0;
		PanelClass->lpfnWndProc = WndProc;
		PanelClass->cbClsExtra = 0;
		PanelClass->cbWndExtra = 0;
		PanelClass->hInstance = hInstance;
		PanelClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);
		PanelClass->hCursor = LoadCursor(NULL, IDC_ARROW);
		PanelClass->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		PanelClass->lpszMenuName = NULL;
		PanelClass->lpszClassName = "NativeUIPanel";
		PanelClass->hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(PanelClass))
		{
			MessageBox(NULL, "Panel Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		}
	}

	Panel::Panel(Control* arg_parent)
		: Control(arg_parent)
	{
		if (PanelClass == NULL)
		{
			CreatePanelClass();
		}

		mHwnd = CreateWindow("NativeUIPanel", "", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 50, 50, arg_parent->GetHwnd(), NULL, GetModuleHandle(NULL), NULL);
		ShowWindow(mHwnd, TRUE);
		UpdateWindow(mHwnd);

		if (mHwnd == NULL)
		{
			MessageBox(NULL, "Panel Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		}
		else
		{
			RegisteredPanels[mHwnd] = this;
		}
	}



}
