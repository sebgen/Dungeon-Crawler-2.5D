#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "sdl2/SDL.h"
#include "sdl2/sdl_image.h"
#include <iostream>
#include <vector>
#include <math.h>

#include "Engine/game_engine.h"
#include "Graphics/scene_renderer.h"
#include "World/level.h"
#include "Actor/actor.h"
#include "Actor/player.h"
#include "Component/component.h"
#include "Component/camera_component.h"
#include "Misc/st_assert.h"
#include "Actor/player_controller.h"
#include "World/world.h"
#include "Component/sprite_component.h"
#include "Component/script_component.h"


// UI test
#include "UI/Widgets/visual_widget.h"
#include "UI/Managers/WidgetManager.h"
#include "UI/Widgets/text_widget.h"
#include "UI/Widgets/image_widget.h"


#include <typeinfo>

#include "Engine/script_manager.h"

#undef main // TEMP - TODO


int main(int argc, char** argv)
{
	LOG_INFO() << "starting from main";

	using namespace Retro3D;

	GameEngine* engine = GameEngine::CreateGameEngine();

	// TODO: initialise from file
	engine->GetScriptManager()->RegisterScript("resources//chaiscript//TestClass.chai");
	engine->GetScriptManager()->RegisterScript("resources//chaiscript//TestLevel.chai");

	GGameEngine->GetCurrentLevel()->LoadLevel("level1");
	engine->GetSceneRenderer()->SetLevel(GGameEngine->GetCurrentLevel()); // todo: do in engine

	Player* player = new Player();
	player->GetTransform().SetPosition(glm::vec3(2.0f, 1.0f, 0.5f));

	CameraComponent* camComp = new CameraComponent();
	player->AddComponent(camComp);

	GGameEngine->GetPlayerController()->SetPlayer(player);

	GGameEngine->GetSceneRenderer()->SetCameraComponent(camComp); // TODO: make this automatic
	
	// UI Widget rendering test
	ImageWidget* colWidget = new ImageWidget();
	colWidget->SetPosition(0.0f, 0.0f);
	colWidget->SetSize(1.0f, 0.12f);
	colWidget->SetColour(Colour(0.0f, 0.0f, 1.0f, 0.3f));
	GGameEngine->GetWidgetManager()->AddWidget(colWidget);
	
	TextWidget* txtWidget = new TextWidget();
	txtWidget->SetPosition(0.5f, 0.0f);
	txtWidget->SetPivot(0.5f, 0.0f);
	txtWidget->SetSize(0.6f, 0.9f);
	txtWidget->SetText("Dungeon Crawler");
	txtWidget->GetTextStyle().SetColour(Colour(1.0f, 1.0f, 1.0f));
	colWidget->AddChildWidget(txtWidget);

	engine->StartEngine();

	SDL_Quit();

	return 0;
}
