#pragma once

#include "GraphicsObject.h"
#include "PlayerObject.h"

class LifeBar
{
public:
	PlayerObject* viktor;

	LifeBar(PlayerObject* v);
	~LifeBar();

	void Draw(HDC screen);
};

