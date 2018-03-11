#ifndef RETRO3D_TEXTINPUTMETHODCONTEXT_H
#define RETRO3D_TEXTINPUTMETHODCONTEXT_H

#include <string>

namespace Retro3D
{
	class IWindow;

	class ITextInputMethodContext
	{
	public:
		virtual IWindow* GetIMContextWindow() = 0;
		virtual void HandleTextInputMethodResult(std::string arg_input) = 0;
	};
}

#endif
