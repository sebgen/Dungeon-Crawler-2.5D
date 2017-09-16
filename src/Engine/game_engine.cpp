#include "game_engine.h"

#include "Resource/resource_manager.h"
#include "Engine/input_manager.h"
#include "Graphics/scene_renderer.h"
#include "World/level.h"
#include "Window/window.h"
#include "World/world.h"
#include <SDL2/SDL.h>
#include "Actor/actor.h"
#include "Actor/player_controller.h"
#include "World/world_messagebus.h"
#include "script_manager.h"
#include "Misc/debug.h"
#include "API/SDL/SDLWidgetRenderer.h"
#include "UI/Managers/WidgetManager.h"
#include <SDL2/SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace Retro3D
{
	GameEngine* GGameEngine = nullptr;

	GameEngine::GameEngine()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		atexit(SDL_Quit);

		if (TTF_Init() != 0) {
			LOG_ERROR() << "failed to initialise TTF";
			//logSDLError(std::cout, "TTF_Init");
			SDL_Quit();
			//return 1;
		}

		GGameEngine = this;
		mResourceManager = new ResourceManager();
		mInputManager = new InputManager();
		mScriptManager = new ScriptManager();
		mWindow = new Window();
		mWidgetRenderer = new SDLWidgetRenderer();
		mWidgetManager = new WidgetManager();
		mSceneRenderer = new SceneRenderer();
		mWorldMessageBus = new WorldMessageBus();
		mWorld = new World();
		mCurrentLevel = new Level();
		mPlayerController = new PlayerController();
		if (!mGameConfig.ReadFile("resources//config//GameConfig.ini"))
			LOG_ERROR() << "Failed to read config game file: ";
	}

	GameEngine* GameEngine::CreateGameEngine()
	{
		LOG_INFO() << "Creating game engine";
		GGameEngine = new GameEngine();
		return GGameEngine;
	}

#ifdef __EMSCRIPTEN__
	void emscriptenMainLoop()
	{
		GGameEngine->TickEngine();
	}
#endif

	void GameEngine::StartEngine()
	{
		LOG_INFO() << "Starting game engine";

		mInputManager->RegisterInputListener(mWidgetManager); // TODO: do this in WidgetManager instead?

		mResourceManager->OnStart();

		mPlayerController->OnStart();

		for (const ObjectPtr<Actor> actor : mWorld->GetActors())
		{
			actor->OnStart();
		}

		LOG_INFO() << "Entering main loop";

		mIsRunning = true;

#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop(emscriptenMainLoop, 0, 1);
#else
		while (mIsRunning) // TODO
		{
			TickEngine();
		}
#endif
	}

	void GameEngine::TickEngine()
	{
		const Uint64 start = SDL_GetPerformanceCounter();

		mWorld->TickWorld(mDeltaTime);
		mWorldMessageBus->Clear();

		mInputManager->CaptureInput();

		// Tick all actors and components
		mPlayerController->OnTick(mDeltaTime);
		for (const ObjectPtr<Actor> actor : mWorld->GetActors())
		{
			actor->OnTick(mDeltaTime);
		}

		// Update all widgets
		mWidgetManager->TickWidgets(mDeltaTime);

		// Clear screen
		mWindow->PrepareRender();

		// Render the world
		mSceneRenderer->RenderScene();

		// Render UI
		mWidgetManager->RenderWidgets(mWindow);

		// Update the screen
		mWindow->Render();

		mResourceManager->ProcessCompletedAsyncLoads();

		const Uint64 end = SDL_GetPerformanceCounter();
		const static Uint64 freq = SDL_GetPerformanceFrequency();
		mDeltaTime = (end - start) / static_cast< float >(freq);
		//std::cout << "Frame time: " << mDeltaTime * 1000.0 << "ms" << std::endl;
	}

	float GameEngine::GetDeltaTime()
	{
		return mDeltaTime;
	}

}
