//
// Created by aelliixx on 2024-03-22.
//

#include "Properties.h"
#include "../../libs/imgui/imgui.h"
#include "../../libs/Coloforma/Println.h"

namespace alx {

void Properties::Tick(const float DeltaTime)
{
	ImGui::Begin("Properties");
	ImGui::Text("Frame time: %.0fms", DeltaTime * 1000);
	ImGui::End();
}
void Properties::Begin() { Window::Begin(); }
} // alx