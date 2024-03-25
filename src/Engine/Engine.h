//
// Created by aelliixx on 2024-03-22.
//

#pragma once

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_sdl2.h"
#include "../libs/imgui/imgui_impl_opengl3.h"
#include "Window/Window.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <memory>
#include <vector>

namespace alx {

class Engine final 
{
	const char* glslVersion = "#version 130";
	SDL_Window* window{};
	SDL_GLContext glContext{};
	bool loopDone{false};
	ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	
	std::string windowTitle;
	int screenWidth, screenHeight;
	
	std::vector<std::shared_ptr<Window>> windows;
	
public:
	Engine(std::string WindowTitle, int Width, int Height);
	
	void CreateWindow(std::shared_ptr<Window> Window);
	void Start();
	

protected:
	void TickWindows(float DeltaTime);
	void BeginWindows();
	
private:
	// Initialise SDL
	void Init(); 
	// Setup ImGui
	void SetupImGui();
	// Loop start: create new frame
	void PreRender(); 
	// Call tick, poll for SDL events
	void Loop();
	// Loop end: render
	void PostRender();
	// Post-loop: shut down opengl, SDL, destroy ImGui context, destroy window, quit.
	void Shutdown();
};

} // alx
