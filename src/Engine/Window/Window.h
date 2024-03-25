//
// Created by aelliixx on 2024-03-22.
//

#pragma once

#include <string>
namespace alx {

class Window
{
	friend class Engine;
protected:
	virtual void Begin() {};
	virtual void Tick(float DeltaTime) = 0;
	virtual void End() {};
	
public:
	virtual ~Window() { End(); };
};

} // alx
