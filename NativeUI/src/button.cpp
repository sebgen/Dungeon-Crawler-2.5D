#include "button.h"

namespace NativeUI
{
	Button::Button(Control* arg_parent)
		: Control(arg_parent)
	{
		mHwnd = CreateWindow("BUTTON", "", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 50, 50, arg_parent->GetHwnd(), NULL, GetModuleHandle(NULL), NULL);
		SetSize(Point(80.0f, 40.0f));
		ShowWindow(mHwnd, TRUE);
		UpdateWindow(mHwnd);
	}

	void Button::SetText(const char* arg_text)
	{
		SetWindowText(mHwnd, arg_text);
	}
}
