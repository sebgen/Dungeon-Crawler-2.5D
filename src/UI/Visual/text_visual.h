#ifndef RETRO3D_UI_TEXT_VISUAL_H
#define RETRO3D_UI_TEXT_VISUAL_H

#include "UI/Visual/visual.h"
#include <string>
#include "UI/Core/text_style.h"
#include "Resource/res_ptr.h"
#include "Resource/font_res.h"

namespace Retro3D
{
	class TextVisual : public Retro3D::Visual
	{
	private:
		std::string mText;
		TextStyle mTextStyle;
		ResPtr<FontRes> mFontRes;

	public:
		TextVisual();

		const std::string& GetText() const { return mText; }
		TextStyle GetTextStyle() { return mTextStyle; }

		void SetTextStyle(TextStyle arg_style);
		void SetText(std::string arg_text);

		void RenderVisual(IWidgetRenderer *arg_renderer, const WidgetRenderParams& arg_renderparams) override;

		inline FontRes* GetFontRes() { return mFontRes.IsValid() ? mFontRes.Get() : nullptr; }

	};
}

#endif
