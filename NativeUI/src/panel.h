#ifndef NATIVEUI_PANEL
#define NATIVEUI_PANEL
#include "control.h"

#include <unordered_map>

namespace NativeUI
{
	class Panel : public Control
	{
	private:
		static std::unordered_map<HWND, Panel*> RegisteredPanels;
		static WNDCLASSEX* PanelClass;
		static void CreatePanelClass();

	public:
		static LRESULT CALLBACK Panel::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		Panel(Control* arg_parent);
	};
}

#endif
