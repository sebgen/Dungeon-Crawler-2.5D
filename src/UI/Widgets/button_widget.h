#ifndef RETRO3D_BUTTONWIDGET_H
#define RETRO3D_BUTTONWIDGET_H

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

		TextWidget GetTextWidget();

		virtual void CreateContent() override;

	};
}

#endif
