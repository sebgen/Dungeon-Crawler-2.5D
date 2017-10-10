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

#include <typeinfo>

#include "Engine/script_manager.h"


#undef main // TEMP - TODO

using namespace Retro3D;


int main(int argc, char** argv)
{
	LOG_INFO() << "starting from main";

#ifdef RETRO3D_OPTIMISATIONS_DISABLED
	LOG_INFO() << "Optimisations are disabled!";
#endif

	GameEngine* engine = GameEngine::CreateGameEngine();

	GGameEngine->GetCurrentLevel()->LoadLevel("level1");
	engine->GetSceneRenderer()->SetLevel(GGameEngine->GetCurrentLevel()); // todo: do in engine

	Player* player = new Player();
	player->GetTransform().SetPosition(glm::vec3(2.0f, 1.0f, 0.5f));

	CameraComponent* camComp = new CameraComponent();
	player->AddComponent(camComp);

	GGameEngine->GetPlayerController()->SetPlayer(player);

	GGameEngine->GetSceneRenderer()->SetCameraComponent(camComp); // TODO: make this automatic

	engine->StartEngine();

	SDL_Quit();

	return 0;
}
