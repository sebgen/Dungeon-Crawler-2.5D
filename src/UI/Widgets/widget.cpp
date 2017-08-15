#include "widget.h"
#include "UI/Interfaces/widget_renderer.h"
#include "Misc/st_assert.h"

namespace Retro3D
{
	Widget::Widget()
		: mTransform()
	{
		mTransformIsDirty = true;
		mTransform.mSize = glm::vec2(1.0f, 1.0f);
	}

	void Widget::SetTransformDirty()
	{
		mTransformIsDirty = true;
	}

	void Widget::AddChildWidget(Widget* arg_widget)
	{
		__AssertComment(arg_widget != nullptr, "Called Widget::AddChildWidget with a null-widget in parameters.");

		ObjectPtr<Widget> widget(arg_widget);

		if (arg_widget->mParentWidget.IsValid())
		{
			bool removed = arg_widget->mParentWidget->RemoveChildWidget(arg_widget);
			__AssertComment(removed, "Widget not contained in its parent's child widget container");
		}
		arg_widget->mParentWidget = this;
		mChildWidgets.push_back(widget);
	}

	bool Widget::RemoveChildWidget(Widget* arg_widget)
	{
		for (size_t i = 0; i < mChildWidgets.size(); i++)
		{
			ObjectPtr<Widget>& widget = mChildWidgets[i];
			if (widget == arg_widget)
			{
				mChildWidgets.erase(mChildWidgets.begin() + i);
				return true;
			}
		}
		return false;
	}

	void Widget::AddVisual(Visual* arg_visual)
	{
		mVisuals.push_back(arg_visual);
	}

	void Widget::CreateContent()
	{

	}

	void Widget::OnInitialise()
	{

	}

	void Widget::OnTick(float arg_deltatime)
	{

	}

	void Widget::SetPosition(glm::vec2 arg_pos)
	{
		mTransform.mPosition = arg_pos;
		SetTransformDirty();
	}

	void Widget::SetSize(glm::vec2 arg_size)
	{
		mTransform.mSize = arg_size;
		SetTransformDirty();
	}

	void Widget::SetPivot(glm::vec2 arg_pivot)
	{
		mTransform.mPivot = arg_pivot;
		SetTransformDirty();
	}

	void Widget::SetVerticalPositioning(WidgetPositioningMode arg_mode)
	{
		mTransform.mVerticalPositioning = arg_mode;
		SetTransformDirty();
	}

	void Widget::SetHorizontalPositioning(WidgetPositioningMode arg_mode)
	{
		mTransform.mHorizontalPositioning = arg_mode;
		SetTransformDirty();
	}

	void Widget::SetVerticalScaling(WidgetScalingMode arg_mode)
	{
		mTransform.mVerticalScaling = arg_mode;
		SetTransformDirty();
	}

	void Widget::SetHorizontalScaling(WidgetScalingMode arg_mode)
	{
		mTransform.mHorizontalScaling = arg_mode;
		SetTransformDirty();
	}

	const WidgetTransform& Widget::GetAbsoluteTransform()
	{
		const WidgetTransform* parentTrans = nullptr;
		if (mParentWidget.IsValid())
		{
			parentTrans = &mParentWidget->GetAbsoluteTransform();
		}
		mAbsoluteTransform = mTransform.CreateAbsoluteWidgetTransform(parentTrans);

		mTransformIsDirty = false;

		return mAbsoluteTransform; // return the re-calculated absolute transform of the widget
	}

	const size_t Widget::GetNumChildWidgets() const
	{
		return mChildWidgets.size();
	}

	ObjectPtr<Widget> Widget::GetChildWidgetAt(const size_t& arg_index) const
	{
		return mChildWidgets[arg_index];
	}

}
