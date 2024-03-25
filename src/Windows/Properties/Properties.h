//
// Created by aelliixx on 2024-03-22.
//

#pragma once

#include <string>
#include "../../Engine/Window/Window.h"
namespace alx {

class Properties final : public Window
{
protected:
	void Begin() override;
	void Tick(float DeltaTime) override;
};

} // alx

