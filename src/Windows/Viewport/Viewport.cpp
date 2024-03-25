//
// Created by aelliixx on 2024-03-22.
//

#include "Viewport.h"
#include "../../libs/imgui/imgui.h"
#include "../../libs/Coloforma/Println.h"

namespace alx {

void Viewport::Tick(const float DeltaTime)
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove;
	ImGui::Begin("Viewport", nullptr, flags);
	ImGui::End();
}
void Viewport::Begin() { Window::Begin(); }
} // alx