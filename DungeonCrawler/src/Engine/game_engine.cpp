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
#include <SDL2/SDL_mixer.h>
#include "Audio/audio_manager.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace Retro3D
{
	GameEngine* GGameEngine = nullptr;

	GameEngine::GameEngine()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		atexit(AtExit);

		if (TTF_Init() != 0) {
			LOG_ERROR() << "failed to initialise TTF";
		}

		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			LOG_ERROR() << "Failed to initialise SDL_Mixer";
		}

		GGameEngine = this;
		mCurrentLevel = nullptr;
		mResourceManager = new ResourceManager();
		mInputManager = new InputManager();
		mScriptManager = new ScriptManager();
		mWindow = new Window();
		mWidgetRenderer = new SDLWidgetRenderer();
		mWidgetManager = new WidgetManager();
		mAudioManager = new AudioManager();
		mSceneRenderer = new SceneRenderer();
		mWorldMessageBus = new WorldMessageBus();
		mWorld = new World();
		mPlayerController = new PlayerController();

		SetCurrentLevel(new Level());

		// Read game config
		if (!mGameConfig.ReadFile("resources//config//GameConfig.ini"))
			LOG_ERROR() << "Failed to read config game file: ";

		// Read resources.ini
	}

	GameEngine::~GameEngine()
	{
		delete mSceneRenderer;
		mSceneRenderer = nullptr;
		delete mWidgetRenderer;
		mWidgetRenderer = nullptr;
		delete mWindow;
		mWindow = nullptr;
		delete mWorldMessageBus;
		mWorldMessageBus = nullptr;
		delete mCurrentLevel;
		mCurrentLevel = nullptr;
		delete mScriptManager;
		mScriptManager = nullptr;
		delete mInputManager;
		mInputManager = nullptr;
		delete mAudioManager;
		mAudioManager = nullptr;

		SDL_Quit();
	}

	void GameEngine::AtExit()
	{
		if (GGameEngine != nullptr)
		{
			delete GGameEngine;
			GGameEngine = nullptr;
		}
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

		std::string gameManagerScriptClass;
		mGameConfig.GetString("game", "GameManager", gameManagerScriptClass);

		if (!gameManagerScriptClass.empty())
		{
			chaiscript::ChaiScript* chaiScriptCore = GGameEngine->GetScriptManager()->GetChaiScriptCore();
			std::string createInstanceCall = gameManagerScriptClass + std::string("();");
			chaiscript::Boxed_Value gameManagerScriptObject;
			try
			{
				gameManagerScriptObject = chaiScriptCore->eval(createInstanceCall); // will exist as long as mScriptObject
				mScriptManager->SetGameManagerScriptObject(gameManagerScriptObject);
			}
			catch (std::exception ex)
			{
				LOG_ERROR() << "Failed to create script object for " << gameManagerScriptClass << ". Exception: " << ex.what();
				return;
			}
			try
			{
				std::function<void(chaiscript::Boxed_Value&)> funcStartGame = chaiScriptCore->eval<std::function<void(chaiscript::Boxed_Value&)>>("StartGame");
				funcStartGame(gameManagerScriptObject);
			}
			catch (std::exception ex) {}
		}
		else
		{
			LOG_ERROR() << "No game manager set in game config";
		}


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
		delete this;
		GGameEngine = nullptr; // TODO
#endif
	}

	void GameEngine::TickEngine()
	{
		const Uint64 start = SDL_GetPerformanceCounter();

		if (mTickCallback != nullptr)
			mTickCallback(mDeltaTime);

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

	void GameEngine::Shutdown()
	{
		LOG_INFO() << "Shutting down game engine";
		mIsRunning = false;
	}

	float GameEngine::GetDeltaTime()
	{
		return mDeltaTime;
	}

	void GameEngine::SetCurrentLevel(Level* arg_level)
	{
		if (mCurrentLevel != nullptr && mCurrentLevel != arg_level)
		{
			delete mCurrentLevel;
		}
		mCurrentLevel = arg_level;
		mSceneRenderer->SetLevel(arg_level);
	}

}
