#include "button_widget.h"

#include "UI/Visual/image_visual.h"
#include "UI/Visual/colour_visual.h"

namespace Retro3D
{
	ButtonWidget::ButtonWidget()
	{
		mTextWidget = new TextWidget();
		mBackgroundImageWidget = new ImageWidget();

		//mBackgroundStyle = new ImageWidgetStyle();
		//mBackgroundStyleOnHover = new ImageWidgetStyle();
		//mBackgroundStyleOnClick = new ImageWidgetStyle();

		mTextWidget->SetText("");

		AddChildWidget(mTextWidget.Get());
		AddChildWidget(mBackgroundImageWidget.Get());
	}

	TextWidget* ButtonWidget::GetTextWidget()
	{
		return mTextWidget.Get();
	}

	void ButtonWidget::SetText(const std::string& arg_text)
	{
		mTextWidget->SetText(arg_text);
	}

	void ButtonWidget::CreateContent()
	{

	}

	void ButtonWidget::RefreshBackgroundImage()
	{
		ImageWidgetStyle activeStyle = mBackgroundStyle;
		if (mIsMouseDown /*&& mBackgroundStyleOnClick != nullptr*/)
			activeStyle = mBackgroundStyleOnClick;
		else if (mIsMouseHovering /*&& mBackgroundStyleOnHover != nullptr*/)
			activeStyle = mBackgroundStyleOnHover;

		if (/*activeStyle != nullptr*/ true)
		{
			mBackgroundImageWidget->SetImageWidgetStyle(activeStyle);
		}
	}

	void ButtonWidget::SetBackgroundStyle(ImageWidgetStyle& arg_style)
	{
		mBackgroundStyle = arg_style;
		RefreshBackgroundImage();
	}

	void ButtonWidget::SetBackgroundStyleOnHover(ImageWidgetStyle& arg_style)
	{
		mBackgroundStyleOnHover = arg_style;
		RefreshBackgroundImage();
	}

	void ButtonWidget::SetBackgroundStyleOnClick(ImageWidgetStyle& arg_style)
	{
		mBackgroundStyleOnClick = arg_style;
		RefreshBackgroundImage();
	}


	void ButtonWidget::OnMouseButtonDown(MouseButtonID arg_button)
	{
		Widget::OnMouseButtonDown(arg_button);
		if (arg_button == 0)
		{
			mIsMouseDown = true;
			RefreshBackgroundImage();
		}
	}

	void ButtonWidget::OnMouseButtonUp(MouseButtonID arg_button)
	{
		Widget::OnMouseButtonUp(arg_button);
		if (arg_button == 0)
		{
			mIsMouseDown = false;
			RefreshBackgroundImage();
		}
	}

}
