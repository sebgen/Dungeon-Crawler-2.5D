#include "WidgetManager.h"

#include "Engine/game_engine.h"
#include "UI/Interfaces/widget_renderer.h"

namespace Retro3D
{
	WidgetManager::WidgetManager()
	{
		mRootWidget = new Widget();
		mRootWidget->SetSize(1.0f, 1.0f);
	}

	void WidgetManager::AddWidget(Widget* arg_widget)
	{
		mRootWidget->AddChildWidget(arg_widget);
	}

	void WidgetManager::RenderWidgets(Window* arg_window)
	{
		IWidgetRenderer* widgetRenderer = GGameEngine->GetWidgetRenderer();
		widgetRenderer->SetWindow(arg_window);
		for (size_t i = 0; i < mRootWidget->GetNumChildWidgets(); i++)
		{
			ObjectPtr<Widget> currentWidget = mRootWidget->GetChildWidgetAt(i);
			renderWidgetRecursive(currentWidget.Get(), arg_window);
		}
		
	}

	void WidgetManager::renderWidgetRecursive(Widget* arg_widget, Window* arg_window)
	{
		__Assert(arg_widget->mParentWidget != nullptr);
		__Assert(arg_window != nullptr);

		IWidgetRenderer* widgetRenderer = GGameEngine->GetWidgetRenderer();
		const WidgetTransform& widgetTrans = arg_widget->GetAbsoluteTransform();
		const WidgetTransform& parentTrans = arg_widget->mParentWidget->GetAbsoluteTransform();

		// TODO: USE INT CALCULATION
		// Calculate content rect (rect to render widget in) and visible rect (usually the same, unless parent widget is smaller)
		const glm::vec2 contentXYBounds = widgetTrans.mPosition + widgetTrans.mSize;
		const glm::vec2 parentXYBounds = parentTrans.mPosition + parentTrans.mSize;
		const float visiblePosX = std::fminf(std::fmaxf(widgetTrans.mPosition.x, parentTrans.mPosition.x), parentXYBounds.x);
		const float visiblePosY = std::fminf(std::fmaxf(widgetTrans.mPosition.y, parentTrans.mPosition.y), parentXYBounds.y);
		const float visibleSizeW = std::fminf(contentXYBounds.x, parentXYBounds.x) - visiblePosX;
		const float visibleSizeH = std::fminf(contentXYBounds.y, parentXYBounds.y) - visiblePosY;
		WidgetRenderParams renderParams;
		renderParams.mContentRect = Rectangle(widgetTrans.mPosition, widgetTrans.mSize);
		renderParams.mVisibleRect = Rectangle(glm::vec2(visiblePosX, visiblePosY), glm::vec2(visibleSizeW, visibleSizeH));
		
		for (Visual* visual : arg_widget->mVisuals)
		{
			if(visual->IsActivated())
				visual->RenderVisual(widgetRenderer, renderParams);
		}

		for (size_t i = 0; i < arg_widget->GetNumChildWidgets(); i++)
		{
			ObjectPtr<Widget> currentWidget = arg_widget->GetChildWidgetAt(i);
			renderWidgetRecursive(currentWidget.Get(), arg_window);
		}
	}
}