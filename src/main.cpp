#include "Engine/Engine.h"
#include "Windows/Properties/Properties.h"
#include "Windows/Viewport/Viewport.h"
#include "Engine/Window/Dockspace.h"
#include <memory>
int main()
{
	auto engine = std::make_unique<alx::Engine>("RealEngine v0.0.1", 1280, 720);
	engine->CreateWindow(std::make_shared<alx::Dockspace>());
	engine->CreateWindow(std::make_shared<alx::Properties>());
	engine->CreateWindow(std::make_shared<alx::Viewport>());
	
	engine->Start();
	return 0;
}