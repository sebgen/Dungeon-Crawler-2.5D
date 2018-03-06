#include "text_visual.h"

#include "UI/Interfaces/widget_renderer.h"
#include "Engine/game_engine.h"
#include "Resource/resource_manager.h"

namespace Retro3D
{
	TextVisual::TextVisual()
	{
		SetTextStyle(mTextStyle); // to load the resource
	}

	void TextVisual::SetTextStyle(TextStyle arg_style)
	{
		mTextStyle = arg_style;
		std::string resourceParam = mTextStyle.GetFontName() + std::string(":") + std::to_string(mTextStyle.GetFontSize());
		mFontRes = GGameEngine->GetResourceManager()->LoadResource<FontRes>(resourceParam);
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