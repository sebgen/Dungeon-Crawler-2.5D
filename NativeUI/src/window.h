#ifndef NATIVEUI_WINDOW
#define NATIVEUI_WINDOW

#include "control.h"
#include <unordered_map>

namespace NativeUI
{
	class Window : public Control
	{
	private:
		static std::unordered_map<HWND, Window*> mRegisteredWindows;
		static WNDCLASSEX* WindowClass;
		static void CreateWindowClass();

	public:
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		Window::Window();

		void Show();
		void SetTitle(const char* arg_title);
	};
}

#endif // NATIVEUI_WINDOW
