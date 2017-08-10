#include "text_widget.h"

namespace Retro3D
{
	TextWidget::TextWidget()
	{
		mTextVisual.SetText("");
		AddVisual(&mTextVisual);
	}

	void TextWidget::SetText(const std::string &arg_string)
	{
		mTextVisual.SetText(arg_string);
	}

	TextStyle& TextWidget::GetTextStyle()
	{
		return mTextVisual.GetTextStyle();
	}

	void TextWidget::CreateContent()
	{

	}
}
