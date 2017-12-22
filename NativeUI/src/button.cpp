#include "button.h"

namespace NativeUI
{
	Button::Button(Control* arg_parent)
		: Control(arg_parent)
	{
		mHwnd = CreateWindow("BUTTON", "", WS_CHILD | WS_VISIBLE | BS_BITMAP, 0, 0, 50, 50, arg_parent->GetHwnd(), NULL, GetModuleHandle(NULL), NULL);
		SetSize(Point(80.0f, 40.0f));
		ShowWindow(mHwnd, TRUE);
		UpdateWindow(mHwnd);

		HINSTANCE hInstance = GetModuleHandle(NULL);
		//HBITMAP hBitmap = LoadBitmap(hInstance, "wall1");
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "C:\\backup\\test.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if(hBitmap == NULL)
			MessageBox(NULL, "UserControl Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		SendMessage(mHwnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	}

	void Button::SetText(const char* arg_text)
	{
		SetWindowText(mHwnd, arg_text);
		SendMessage(mHwnd, WM_SETTEXT, 0, (LPARAM)"TEST");
		//UpdateWindow(mHwnd);

	}
}
