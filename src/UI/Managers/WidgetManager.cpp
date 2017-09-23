#include "WidgetManager.h"

#include "Engine/game_engine.h"
#include "UI/Interfaces/widget_renderer.h"
#include "Engine/input_manager.h"

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
		if (!arg_widget->mHasCreatedContent)
		{
			arg_widget->CreateContent();
		}
	}

	void WidgetManager::TickWidgets(float arg_deltatime)
	{
		if (mRootWidget != nullptr)
		{
			tickWidgetRecursive(mRootWidget.Get(), arg_deltatime);
		}
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
		
		for (ObjectPtrBase<Visual> visual : arg_widget->mVisuals)
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

	void WidgetManager::tickWidgetRecursive(Widget* arg_widget, float arg_deltatime)
	{
		CurrentWidget = arg_widget;
		arg_widget->OnTick(arg_deltatime);

		// TODO: forward mouse and input

		CurrentWidget = nullptr;

		for (ObjectPtr<Widget> child : arg_widget->mChildWidgets)
		{
			tickWidgetRecursive(child.Get(), arg_deltatime);
		}
	}

	void WidgetManager::OnKeyDown(const char* arg_key)
	{
		// TODO: forward to selected/highlighted widget
	}

	void WidgetManager::OnKeyUp(const char* arg_key)
	{
		// TODO: forward to selected/highlighted widget
	}

	void WidgetManager::OnMouseButtonDown(MouseButtonID arg_button)
	{
		int win_w;
		int win_h;
		GGameEngine->GetWindow()->GetWindowSize(win_w, win_h);
		if (mRootWidget != nullptr)
			mouseEventRecursive(mRootWidget.Get(), GGameEngine->GetInputManager()->GetMousePosition() / glm::vec2(win_w, win_h), 1, arg_button);
	}

	void WidgetManager::OnMouseButtonUp(MouseButtonID arg_button)
	{
		int win_w;
		int win_h;
		GGameEngine->GetWindow()->GetWindowSize(win_w, win_h);
		if (mRootWidget != nullptr)
			mouseEventRecursive(mRootWidget.Get(), GGameEngine->GetInputManager()->GetMousePosition() / glm::vec2(win_w, win_h), 2, arg_button);
	}

	void WidgetManager::OnMouseMotion(const glm::vec2& arg_motion)
	{

	}

	void WidgetManager::mouseEventRecursive(Widget* arg_widget, const glm::vec2& arg_mousepos, int arg_mouseevent, MouseButtonID arg_button)
	{ // TODO: USE LAMBDA
		const glm::vec2 widgetPos = arg_widget->mAbsoluteTransform.mPosition;
		const glm::vec2 widgetRBPos = arg_widget->mAbsoluteTransform.mSize + widgetPos;

		if (arg_mousepos.x > widgetPos.x && arg_mousepos.x < widgetRBPos.x && arg_mousepos.y > widgetPos.y && arg_mousepos.y < widgetRBPos.y)
		{
			switch (arg_mouseevent)
			{
			case 1:
				arg_widget->OnMouseButtonDown(arg_button);
				break;
			case 2:
				arg_widget->OnMouseButtonUp(arg_button);
				break;
			default:
				break;
			}
		}

		for (ObjectPtr<Widget> childWidget : arg_widget->mChildWidgets)
		{
			mouseEventRecursive(childWidget.Get(), arg_mousepos, arg_mouseevent, arg_button);
		}
	}
}