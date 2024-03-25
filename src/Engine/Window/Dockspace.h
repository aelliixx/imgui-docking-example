//
// Created by aelliixx on 2024-03-22.
//

#pragma once

#include "Window.h"
namespace alx {

class Dockspace final : public Window
{
protected:
	void Tick(float DeltaTime) override;
};

} // alx
