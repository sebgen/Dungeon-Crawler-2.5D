#ifndef NATIVEUI_USERCONTROL
#define NATIVEUI_USERCONTROL
#include "control.h"

#include <unordered_map>

namespace NativeUI
{
	class UserControl : public Control
	{
	private:
		static std::unordered_map<HWND, UserControl*> RegisteredUserControls;
		static WNDCLASSEX* UserControlClass;
		static void CreateUserControlClass();

	public:
		static LRESULT CALLBACK UserControl::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		virtual void OnPaint();

	public:
		UserControl(Control* arg_parent);
	};
}

#endif
