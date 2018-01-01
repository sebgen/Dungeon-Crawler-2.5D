#ifndef RETRO3D_TEXTINPUTWIDGET_H
#define RETRO3D_TEXTINPUTWIDGET_H

#include "text_widget.h"

/*=============================================================================================
A Text Widget, for rendering text.

==============================================================================================*/

namespace Retro3D
{
	class TextInputWidget : public TextWidget
	{
	public:
		TextInputWidget();

		void AddText(std::string arg_text);

		virtual void OnKeyUp(const char* arg_key) override;

	};
}

#endif
