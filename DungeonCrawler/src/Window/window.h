#ifndef RETRO3D_WINDOW_H
#define RETRO3D_WINDOW_H

/*=============================================================================================
Window interface.

==============================================================================================*/

namespace Retro3D
{
	class IWindow
	{
	public:
		/** Gets the size (in pixels) of the Window. */
		virtual void GetWindowSize(int& out_width, int& out_height) = 0;

		virtual void* GetOSWindowHandle() = 0;

		virtual bool HasFocus() = 0;
	};
}

#endif
