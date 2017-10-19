#include "editor_window.h"

#include <Windows.h>
#include "window.h"
#include "button.h"
#include "panel.h"
#include "table_layout_panel.h"
#include "game_view.h"

#define IDM_FILE_NEW 0
#define IDM_FILE_OPEN 1
#define IDM_FILE_QUIT 2
#define IDM_FILE_QUIT 3

namespace Retro3D
{
	EditorWindow::EditorWindow()
		: NativeUI::Window()
	{
		NativeUI::Window* window = new NativeUI::Window();
		window->SetTitle("Editor window");
		window->Show();
		window->Maximize();

		// Menu
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

		// Panel containing game view, content browser and inspector
		NativeUI::TableLayoutPanel* editorMainPanel = new NativeUI::TableLayoutPanel(editorMainCell->mContainerPanel, 3, 1);
		editorMainPanel->SetColumnWidth(0, 0.2f);
		editorMainPanel->SetColumnWidth(1, 0.6f);
		editorMainPanel->SetColumnWidth(2, 0.2f);
		NativeUI::TableLayoutCell* contentBrowserCell = editorMainPanel->GetCell(0, 0);
		NativeUI::TableLayoutCell* viewContainerCell = editorMainPanel->GetCell(1, 0);
		NativeUI::TableLayoutCell* propertyInspectorCell = editorMainPanel->GetCell(2, 0);

		// Panel containing game view and map editor view
		NativeUI::TableLayoutPanel* viewportsPanel = new NativeUI::TableLayoutPanel(viewContainerCell->mContainerPanel, 1, 2);
		viewportsPanel->SetRowHeight(0, 0.5f);
		viewportsPanel->SetRowHeight(1, 0.5f);
		NativeUI::TableLayoutCell* mapEditorViewCell = viewportsPanel->GetCell(0, 0);
		NativeUI::TableLayoutCell* gameViewCell = viewportsPanel->GetCell(0, 1);

		// Test buttons
		NativeUI::Button* testBtnToolbar = new NativeUI::Button(toolbarCell->mContainerPanel);
		testBtnToolbar->SetText("Toolbar");
		testBtnToolbar->SetSize(1.0f, 1.0f);
		testBtnToolbar->SetVerticalSizeMode(NativeUI::SizeMode::Relative);
		testBtnToolbar->SetHorizontalSizeMode(NativeUI::SizeMode::Relative);

		// Map editor view
		mMapEditorView = new Retro3D::MapEditorView(mapEditorViewCell->mContainerPanel);
		mMapEditorView->SetSize(2000.0f, 2000.0f);
		mMapEditorView->SetVerticalSizeMode(NativeUI::SizeMode::Absolute);
		mMapEditorView->SetHorizontalSizeMode(NativeUI::SizeMode::Absolute);

		// Game view
		mGameView = new Retro3D::GameView(gameViewCell->mContainerPanel);
		mGameView->SetSize(1.0f, 1.0f);
		mGameView->SetVerticalSizeMode(NativeUI::SizeMode::Relative);
		mGameView->SetHorizontalSizeMode(NativeUI::SizeMode::Relative);

		mapEditorViewCell->mContainerPanel->ShowScrollbar(true);
	}
}
