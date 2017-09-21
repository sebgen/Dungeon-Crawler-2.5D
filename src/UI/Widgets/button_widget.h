#ifndef RETRO3D_BUTTONWIDGET_H
#define RETRO3D_BUTTONWIDGET_H

/*=============================================================================================
Button Widget.

A clickable Widget.

TODO: WORK IN PROGRESS

==============================================================================================*/

#include "visual_widget.h"
#include "UI/Widgets/text_widget.h"

namespace Retro3D
{
	class ButtonWidget : public VisualWidget
	{
	protected:
		TextWidget mTextWidget;

	public:
		ButtonWidget();

		/** Gets the TextWidget, containing the button's text. */
		TextWidget GetTextWidget();

		virtual void CreateContent() override;

	};
}

#endif
