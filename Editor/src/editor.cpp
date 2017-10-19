#include "editor.h"

#include <iostream>
#include <Windows.h>
#include <sdl2/SDL.h>

#include "Engine/game_engine.h"
#include "Actor/player.h"
#include "Actor/player_controller.h"
#include "World/level.h"
#include "Graphics/scene_renderer.h"
#include "Component/camera_component.h"

namespace Retro3D
{
	Editor* GEditor = nullptr;

	Editor::Editor()
	{

	}

	Editor* Editor::CreateEditor()
	{
		if (GEditor != nullptr)
		{
			delete GEditor;
		}
		GEditor = new Editor();
		return GEditor;
	}

	void Editor::RunEditor()
	{
		Retro3D::GameEngine* engine = Retro3D::GameEngine::CreateGameEngine();

		engine->GetCurrentLevel()->LoadLevel("level1");
		engine->GetSceneRenderer()->SetLevel(engine->GetCurrentLevel()); // todo: do in engine

		Retro3D::Player* player = new Retro3D::Player();
		player->GetTransform().SetPosition(glm::vec3(2.0f, 1.0f, 0.5f));

		Retro3D::CameraComponent* camComp = new Retro3D::CameraComponent();
		player->AddComponent(camComp);

		engine->GetPlayerController()->SetPlayer(player);

		engine->GetSceneRenderer()->SetCameraComponent(camComp); // TODO: make this automatic

		mEditorWinndow = new EditorWindow();

		std::function<void(float)> tickCallback = [&](float)
		{
			MSG msg;
			msg.message = ~WM_QUIT;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if (msg.message == WM_QUIT)
			{
				engine->Shutdown();
			}
		};

		engine->SetRenderTargetWindow(mEditorWinndow->GetGameView());
		engine->SetTickCallback(tickCallback);
		engine->StartEngine();
		
		while (false)
		{
			tickCallback(0.1f);
		}
	}

}
