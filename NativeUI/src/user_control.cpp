#include "user_control.h"

namespace NativeUI
{
	WNDCLASSEX* UserControl::UserControlClass = NULL;
	std::unordered_map<HWND, UserControl*> UserControl::RegisteredUserControls = std::unordered_map<HWND, UserControl*>();

	LRESULT CALLBACK UserControl::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		UserControl* userControl = RegisteredUserControls[hwnd];
		if (userControl == nullptr)
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		static PAINTSTRUCT ps;

		switch (msg)
		{
		case WM_SIZE:
			userControl->OnResize();
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_PAINT:
			BeginPaint(hwnd, &ps);
			userControl->OnPaint();
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

	void UserControl::CreateUserControlClass()
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		UserControlClass = new WNDCLASSEX();

		UserControlClass->cbSize = sizeof(WNDCLASSEX);
		UserControlClass->style = 0;
		UserControlClass->lpfnWndProc = WndProc;
		UserControlClass->cbClsExtra = 0;
		UserControlClass->cbWndExtra = 0;
		UserControlClass->hInstance = hInstance;
		UserControlClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);
		UserControlClass->hCursor = LoadCursor(NULL, IDC_ARROW);
		UserControlClass->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		UserControlClass->lpszMenuName = NULL;
		UserControlClass->lpszClassName = "NativeUIUserControl";
		UserControlClass->hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(UserControlClass))
		{
			MessageBox(NULL, "UserControl Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		}
	}

	UserControl::UserControl(Control* arg_parent)
		: Control(arg_parent)
	{
		if (UserControlClass == NULL)
		{
			CreateUserControlClass();
		}

		mHwnd = CreateWindow("NativeUIUserControl", "", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 50, 50, arg_parent->GetHwnd(), NULL, GetModuleHandle(NULL), NULL);
		ShowWindow(mHwnd, TRUE);
		UpdateWindow(mHwnd);

		if (mHwnd == NULL)
		{
			MessageBox(NULL, "UserControl Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		}
		else
		{
			RegisteredUserControls[mHwnd] = this;
		}
	}

	void UserControl::OnPaint()
	{

	}
}
