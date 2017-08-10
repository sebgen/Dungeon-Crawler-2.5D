#include "text_visual.h"

#include "UI/Interfaces/widget_renderer.h"

namespace Retro3D
{
	void TextVisual::SetTextStyle(TextStyle arg_style)
	{
		mTextStyle = arg_style;
	}

	void TextVisual::SetText(std::string arg_text)
	{
		mText = arg_text;
	}

	void TextVisual::RenderVisual(IWidgetRenderer *arg_renderer, const WidgetRenderParams& arg_renderparams)
	{
		arg_renderer->RenderText(this, arg_renderparams);
	}
}