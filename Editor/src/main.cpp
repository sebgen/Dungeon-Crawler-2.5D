#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#define SDL_MAIN_HANDLED

#include <iostream>
#include <sdl2/SDL.h>
#include <Windows.h>
#include "window.h"
#include "button.h"
#include "panel.h"
#include "table_layout_panel.h"

SDL_Window* WindowSDLWindow;
SDL_Renderer* WindowSDLRenderer;


int main()
{
	NativeUI::Window* window = new NativeUI::Window();
	window->SetTitle("Editor window");
	window->Show();

	// Main panel
	NativeUI::TableLayoutPanel* mainPanel = new NativeUI::TableLayoutPanel(window, 1, 2);
	mainPanel->SetRowHeight(0, 0.2f);
	mainPanel->SetRowHeight(1, 0.8f);
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
	
	NativeUI::Button* testBtnViewContainer = new NativeUI::Button(viewContainerCell->mContainerPanel);
	testBtnViewContainer->SetText("View");
	testBtnViewContainer->SetSize(1.0f, 1.0f);
	testBtnViewContainer->SetVerticalSizeMode(NativeUI::SizeMode::Relative);
	testBtnViewContainer->SetHorizontalSizeMode(NativeUI::SizeMode::Relative);




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
	return 0;
}