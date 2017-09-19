#include "chai_bindings.h"

#include "Engine/game_engine.h"
#include "Actor/actor.h"
#include "Actor/player.h"
#include "Component/component.h"
#include "Component/script_component.h"
#include "Component/sprite_component.h"
#include "Component/camera_component.h"
#include "World/level.h"
#include "glm/glm.hpp"
#include "Engine/input_manager.h"
#include "Engine/script_manager.h"
#include "Text/config_reader.h"
#include "World/world.h"
#include "UI/Widgets/image_widget.h"
#include "UI/Widgets/text_widget.h"
#include "UI/Managers/WidgetManager.h"
#include "Actor/player_controller.h"
#include "Object/weak_objectptr.h"

namespace Retro3D
{
	GameEngine* scripthelper_getengine() { return GGameEngine; }

	Actor* scripthelper_CreateActor() { return new Actor(); }

	ScriptComponent* scripthelper_CreateScriptComponent() { return new ScriptComponent(); }
	CameraComponent* scripthelper_CreateCameraComponent() { return new CameraComponent(); }
	SpriteComponent* scripthelper_CreateSpriteComponent() { return new SpriteComponent(); }


	void ChaiBindings::AddBindings(chaiscript::ChaiScript* arg_chaiscript)
	{
		arg_chaiscript->add(chaiscript::user_type<GameEngine>(), "GameEngine");
		arg_chaiscript->add(chaiscript::fun(&GameEngine::GetDeltaTime), "GetDeltaTime");
		arg_chaiscript->add(chaiscript::fun(&GameEngine::GetCurrentLevel), "GetCurrentLevel");
		arg_chaiscript->add(chaiscript::fun(&GameEngine::GetInputManager), "GetInputManager");
		arg_chaiscript->add(chaiscript::fun(&GameEngine::GetScriptManager), "GetScriptManager");
		arg_chaiscript->add(chaiscript::fun(&GameEngine::GetWidgetManager), "GetWidgetManager");
		arg_chaiscript->add(chaiscript::fun(&GameEngine::GetGameConfig), "GetGameConfig");

		arg_chaiscript->add(chaiscript::user_type<Level>(), "Level");
		//arg_chaiscript->add(chaiscript::fun(&Level::LoadLevel), "LoadLevel");

		
		arg_chaiscript->add(chaiscript::user_type<ConfigReader>(), "ConfigReader");
		arg_chaiscript->add(chaiscript::fun(&ConfigReader::GetString_string), "GetString");
		arg_chaiscript->add(chaiscript::fun(&ConfigReader::GetInt_string), "GetInt");
		arg_chaiscript->add(chaiscript::fun(&ConfigReader::GetFloat_string), "GetFloat");


		// Actors
		arg_chaiscript->add(chaiscript::user_type<Actor>(), "Actor");
		//arg_chaiscript->add(chaiscript::constructor<Actor()>(), "Actor");
		arg_chaiscript->add(chaiscript::fun(&Actor::AddComponent), "AddComponent");
		arg_chaiscript->add(chaiscript::fun(&Actor::GetTransform), "GetTransform");
		arg_chaiscript->add(chaiscript::fun(&Actor::SetActorName), "SetActorName");
		arg_chaiscript->add(chaiscript::fun(&Actor::GetActorName), "GetActorName");
		arg_chaiscript->add(chaiscript::fun([](Actor & o, std::string arg_name)
		{
			for (ScriptComponent* comp : o.GetComponents<ScriptComponent>())
			{
				if (comp->GetScriptClassName() == arg_name)
					return comp;
			}
			return (ScriptComponent*)nullptr;
		}), "GetScriptComponentByClass");

		// Player
		arg_chaiscript->add(chaiscript::user_type<Player>(), "Player");
		arg_chaiscript->add(chaiscript::base_class<Actor, Player>());

		// PlayerController
		arg_chaiscript->add(chaiscript::user_type<PlayerController>(), "PlayerController");
		arg_chaiscript->add(chaiscript::fun(&PlayerController::GetPlayer), "GetPlayer");
		arg_chaiscript->add(chaiscript::fun(&PlayerController::SetPlayer), "SetPlayer");


		// ChaiScriptObject
		arg_chaiscript->add(chaiscript::fun([](chaiscript::Boxed_Value boxedValue)
		{
			auto iter = ScriptComponent::ScriptObjectMap.find(boxedValue.get_ptr());
			if (iter != ScriptComponent::ScriptObjectMap.end())
			{
				return (*iter).second;
			}
			return (ScriptComponent*)nullptr;
		}), "GetScriptComponent");

		// Components
		arg_chaiscript->add(chaiscript::user_type<Component>(), "Component");

		arg_chaiscript->add(chaiscript::user_type<ScriptComponent>(), "ScriptComponent");
		arg_chaiscript->add(chaiscript::fun(&ScriptComponent::SetScriptClass), "SetScriptClass");
		arg_chaiscript->add(chaiscript::fun(&ScriptComponent::GetScriptClassName), "GetScriptClassName");
		arg_chaiscript->add(chaiscript::base_class<Component, ScriptComponent>());
		arg_chaiscript->add(chaiscript::fun(&ScriptComponent::GetScriptObject), "GetScriptObject");

		arg_chaiscript->add(chaiscript::user_type<SpriteComponent>(), "SpriteComponent");
		arg_chaiscript->add(chaiscript::fun(&SpriteComponent::SetTexture), "SetTexture");
		arg_chaiscript->add(chaiscript::base_class<Component, SpriteComponent>());

		arg_chaiscript->add(chaiscript::user_type<CameraComponent>(), "CameraComponent");
		arg_chaiscript->add(chaiscript::base_class<Component, CameraComponent>());


		// ObjectPtr
		arg_chaiscript->add(chaiscript::user_type<WeakObjectPtr<Actor>>(), "ActorPtr");
		arg_chaiscript->add(chaiscript::base_class<ObjectPtrBase<Actor>, WeakObjectPtr<Actor>>());
		arg_chaiscript->add(chaiscript::constructor<WeakObjectPtr<Actor>(Actor*)>(), "ActorPtr");
		arg_chaiscript->add(chaiscript::fun(&WeakObjectPtr<Actor>::Get), "Get");


		// Managers
		arg_chaiscript->add(chaiscript::user_type<InputManager>(), "InputManager");
		arg_chaiscript->add(chaiscript::fun(&InputManager::GetKey_String), "GetKey");
		arg_chaiscript->add(chaiscript::fun(&InputManager::GetKeyDown_String), "GetKeyDown");
		arg_chaiscript->add(chaiscript::fun(&InputManager::GetKeyUp_String), "GetKeyUp");
		arg_chaiscript->add(chaiscript::fun(&InputManager::GetMousePressed), "GetMousePressed");
		arg_chaiscript->add(chaiscript::fun(&InputManager::GetMouseReleased), "GetMouseReleased");
		arg_chaiscript->add(chaiscript::fun(&InputManager::GetMousePosition), "GetMousePosition");

		arg_chaiscript->add(chaiscript::user_type<ScriptManager>(), "ScriptManager");
		arg_chaiscript->add(chaiscript::fun(&ScriptManager::RegisterScript), "RegisterScript");


		arg_chaiscript->add(chaiscript::user_type<WidgetManager>(), "WidgetManager");
		arg_chaiscript->add(chaiscript::fun(&WidgetManager::AddWidget), "AddWidget");


		// Widgets
		arg_chaiscript->add(chaiscript::user_type<Widget>(), "Widget");
		arg_chaiscript->add(chaiscript::fun(&Widget::AddVisual), "AddVisual");
		arg_chaiscript->add(chaiscript::fun(&Widget::AddChildWidget), "AddChildWidget");
		arg_chaiscript->add(chaiscript::fun([](Widget& widget, const float x, const float y) { widget.SetSize(x, y); }), "SetSize");
		arg_chaiscript->add(chaiscript::fun([](Widget& widget, const float x, const float y) { widget.SetPosition(x, y); }), "SetPosition");
		arg_chaiscript->add(chaiscript::fun([](Widget& widget, const float x, const float y) { widget.SetPivot(x, y); }), "SetPivot");
		arg_chaiscript->add(chaiscript::fun(&Widget::SetWidgetScriptClass), "SetWidgetScriptClass");

		arg_chaiscript->add(chaiscript::user_type<ImageWidget>(), "ImageWidget");
		arg_chaiscript->add(chaiscript::fun(&ImageWidget::SetColour), "SetColour");
		arg_chaiscript->add(chaiscript::fun(&ImageWidget::SetImagePath), "SetImagePath");
		arg_chaiscript->add(chaiscript::base_class<Widget, ImageWidget>());

		arg_chaiscript->add(chaiscript::user_type<TextWidget>(), "TextWidget");
		arg_chaiscript->add(chaiscript::base_class<Widget, TextWidget>());
		arg_chaiscript->add(chaiscript::fun(&TextWidget::SetText), "SetText");
		arg_chaiscript->add(chaiscript::fun(&TextWidget::GetTextStyle), "GetTextStyle");
		arg_chaiscript->add(chaiscript::fun(&TextWidget::SetTextStyle), "SetTextStyle");

		arg_chaiscript->add(chaiscript::user_type<TextStyle>(), "TextStyle");
		arg_chaiscript->add(chaiscript::fun(&TextStyle::SetColour), "SetColour");
		arg_chaiscript->add(chaiscript::fun(&TextStyle::SetFontName), "SetFontName");
		arg_chaiscript->add(chaiscript::fun(&TextStyle::SetFontSize), "SetFontSize");
		arg_chaiscript->add(chaiscript::fun(&TextStyle::SetWrapText), "SetWrapText");

		arg_chaiscript->add(chaiscript::user_type<Colour>(), "Colour");
		arg_chaiscript->add(chaiscript::constructor<Colour(float, float, float)>(), "Colour");
		arg_chaiscript->add(chaiscript::constructor<Colour(float, float, float, float)>(), "Colour");


		// Transform
		arg_chaiscript->add(chaiscript::user_type<Transform>(), "Transform");
		arg_chaiscript->add(chaiscript::fun(&Transform::GetPosition), "GetPosition");
		arg_chaiscript->add(chaiscript::fun(&Transform::SetPosition), "SetPosition");


		// glm
		arg_chaiscript->add(chaiscript::user_type<glm::vec3>(), "vec3");
		arg_chaiscript->add(chaiscript::constructor<glm::vec3(float, float, float)>(), "vec3");
		arg_chaiscript->add(chaiscript::fun([](glm::vec3 a, glm::vec3 b) { return a + b; }), "+");


		// glm
		arg_chaiscript->add(chaiscript::user_type<glm::vec2>(), "vec2");
		arg_chaiscript->add(chaiscript::constructor<glm::vec2(float, float)>(), "vec2");
		arg_chaiscript->add(chaiscript::fun([](glm::vec2 a, glm::vec2 b) { return a + b; }), "+");


		// helper functions
		arg_chaiscript->add(chaiscript::fun(&scripthelper_getengine), "GetGameEngine");
		arg_chaiscript->add(chaiscript::fun(&scripthelper_CreateActor), "CreateActor");
		arg_chaiscript->add(chaiscript::fun(&scripthelper_CreateScriptComponent), "CreateScriptComponent");
		arg_chaiscript->add(chaiscript::fun(&scripthelper_CreateSpriteComponent), "CreateSpriteComponent");
		arg_chaiscript->add(chaiscript::fun(&scripthelper_CreateCameraComponent), "CreateCameraComponent");

		// TEMP - TODO: Create a CreateWidget(typename) function
		arg_chaiscript->add(chaiscript::fun([]()
		{
			ImageWidget* widget = new ImageWidget();
			return widget;
		}), "CreateImageWidget");
		// TEMP - TODO: Create a CreateWidget(typename) function
		arg_chaiscript->add(chaiscript::fun([]()
		{
			TextWidget* widget = new TextWidget();
			return widget;
		}), "CreateTextWidget");
		// TEMP - TODO: Create a CreateWidget(typename) function
		arg_chaiscript->add(chaiscript::fun([](const std::string& scriptclass)
		{
			Widget* widget = new Widget();
			widget->SetWidgetScriptClass(scriptclass.c_str());
			return widget;
		}), "CreateScriptWidget");

		arg_chaiscript->add(chaiscript::fun([](const std::string& name)
		{
			for (ObjectPtr<Actor> actor : GGameEngine->GetWorld()->GetActors())
			{
				if (actor->GetActorName() == name)
					return actor.Get();
			}
			return (Actor*)nullptr;
		}), "GetActorByName");

		// ChaiScriptObject
		arg_chaiscript->add(chaiscript::fun([](chaiscript::Boxed_Value boxedValue)
		{
			return GGameEngine->GetWidgetManager()->CurrentWidget;
		}), "GetWidget");

	}


}
