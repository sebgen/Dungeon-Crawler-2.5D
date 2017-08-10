#include "button_widget.h"

namespace Retro3D
{
	ButtonWidget::ButtonWidget()
	{
		mTextWidget.SetText("");
	}

	TextWidget ButtonWidget::GetTextWidget()
	{
		return mTextWidget;
	}

	void ButtonWidget::CreateContent()
	{

	}
}
