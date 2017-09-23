#ifndef RETRO3D_BUTTONWIDGET_H
#define RETRO3D_BUTTONWIDGET_H

/*=============================================================================================
Button Widget.

A clickable Widget.

TODO: WORK IN PROGRESS

==============================================================================================*/

#include "visual_widget.h"
#include "image_widget.h"
#include "UI/Widgets/text_widget.h"
#include "Object/objectptr.h"
#include "image_widget_style.h"

namespace Retro3D
{
	class ButtonWidget : public VisualWidget
	{
	private:
		bool mIsMouseDown = false;
		bool mIsMouseHovering = false;

	protected:
		ObjectPtr<TextWidget> mTextWidget;
		ObjectPtr<ImageWidget> mBackgroundImageWidget;

		ImageWidgetStyle mBackgroundStyle;
		ImageWidgetStyle mBackgroundStyleOnHover;
		ImageWidgetStyle mBackgroundStyleOnClick;

	public:
		ButtonWidget();

		/** Gets the TextWidget, containing the button's text. */
		TextWidget* GetTextWidget();

		void SetText(const std::string& arg_text);

		virtual void CreateContent() override;

		void RefreshBackgroundImage();

		/** Sets the background style of the button. */
		void SetBackgroundStyle(ImageWidgetStyle& arg_style);

		/** Sets the background style used when mouse is hovering over the button. */
		void SetBackgroundStyleOnHover(ImageWidgetStyle& arg_style);

		/** Sets the background style used when mouse clicks the button. */
		void SetBackgroundStyleOnClick(ImageWidgetStyle& arg_style);

		inline ImageWidgetStyle GetBackgroundStyle() { return mBackgroundStyle; }
		inline ImageWidgetStyle GetBackgroundStyleOnHover() { return mBackgroundStyleOnHover; }
		inline ImageWidgetStyle GetBackgroundStyleOnClick() { return mBackgroundStyleOnClick; }


		// Input listener callbacks
		
		virtual void OnMouseButtonDown(MouseButtonID arg_button) override;
		virtual void OnMouseButtonUp(MouseButtonID arg_button) override;

	};
}

#endif
