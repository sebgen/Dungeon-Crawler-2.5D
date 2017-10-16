#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#define SDL_MAIN_HANDLED

#include <iostream>
#include <sdl2/SDL.h>
#include <Windows.h>
#include "window.h"
#include "button.h"
#include "panel.h"
#include "table_layout_panel.h"
#include "game_view.h"

#include "Engine/game_engine.h"
#include "Actor/player.h"
#include "Actor/player_controller.h"
#include "World/level.h"
#include "Graphics/scene_renderer.h"
#include "Component/camera_component.h"

int main()
{
	// Initialize SDL.
	//if (SDL_Init(SDL_INIT_VIDEO) < 0)
	//	return 1;

	Retro3D::GameEngine* engine = Retro3D::GameEngine::CreateGameEngine();

	engine->GetCurrentLevel()->LoadLevel("level1");
	engine->GetSceneRenderer()->SetLevel(engine->GetCurrentLevel()); // todo: do in engine

	Retro3D::Player* player = new Retro3D::Player();
	player->GetTransform().SetPosition(glm::vec3(2.0f, 1.0f, 0.5f));

	Retro3D::CameraComponent* camComp = new Retro3D::CameraComponent();
	player->AddComponent(camComp);

	engine->GetPlayerController()->SetPlayer(player);

	engine->GetSceneRenderer()->SetCameraComponent(camComp); // TODO: make this automatic

	// Window
	NativeUI::Window* window = new NativeUI::Window();
	window->SetTitle("Editor window");
	window->Show();
	window->Maximize();
	
#define IDM_FILE_NEW 0
#define IDM_FILE_OPEN 1
#define IDM_FILE_QUIT 2
#define IDM_FILE_QUIT 3

	HMENU hMenubar = CreateMenu();
	HMENU hMenu = CreateMenu();
	HMENU hMenuHelp = CreateMenu();

	AppendMenuW(hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
	AppendMenuW(hMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
	AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Quit");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");

	AppendMenuW(hMenuHelp, MF_STRING, IDM_FILE_QUIT, L"&Help");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenuHelp, L"&Help");

	SetMenu(window->GetHwnd(), hMenubar);

	// Main panel
	NativeUI::TableLayoutPanel* mainPanel = new NativeUI::TableLayoutPanel(window, 1, 2);
	mainPanel->SetRowHeight(0, 0.12f);
	mainPanel->SetRowHeight(1, 0.87f);
	NativeUI::TableLayoutCell* toolbarCell = mainPanel->GetCell(0, 0);
	NativeUI::TableLayoutCell* editorMainCell = mainPanel->GetCell(0, 1);

	// Below toolbar
	NativeUI::TableLayoutPanel* editorMainPanel = new NativeUI::TableLayoutPanel(editorMainCell->mContainerPanel, 3, 1);
	editorMainPanel->SetColumnWidth(0, 0.2f);
	editorMainPanel->SetColumnWidth(1, 0.6f);
	editorMainPanel->SetColumnWidth(2, 0.2f);
	NativeUI::TableLayoutCell* contentBrowserCell = editorMainPanel->GetCell(0, 0);
	NativeUI::TableLayoutCell* viewContainerCell = editorMainPanel->GetCell(1, 0);
	NativeUI::TableLayoutCell* propertyInspectorCell = editorMainPanel->GetCell(2, 0);

	// Test buttons
	NativeUI::Button* testBtnToolbar = new NativeUI::Button(toolbarCell->mContainerPanel);
	testBtnToolbar->SetText("Toolbar");
	testBtnToolbar->SetSize(1.0f, 1.0f);
	testBtnToolbar->SetVerticalSizeMode(NativeUI::SizeMode::Relative);
	testBtnToolbar->SetHorizontalSizeMode(NativeUI::SizeMode::Relative);
	
	Retro3D::GameView* gameView = new Retro3D::GameView(viewContainerCell->mContainerPanel);
	gameView->SetSize(1.0f, 1.0f);
	gameView->SetVerticalSizeMode(NativeUI::SizeMode::Relative);
	gameView->SetHorizontalSizeMode(NativeUI::SizeMode::Relative);
	
	std::function<void(float)> tickCallback = [&] (float)
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

	engine->SetRenderTargetWindow(gameView);
	engine->SetTickCallback(tickCallback);
	engine->StartEngine();

	/*
	MSG msg;
	msg.message = ~WM_QUIT;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	*/

	return 0;
}