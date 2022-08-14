#pragma once

#include "GraphicsObject.h"
#include "EnemyObject.h"

class LifeBarEnemy 
{
public:
	EnemyObject* enemy;

	LifeBarEnemy(EnemyObject* e);
	~LifeBarEnemy();

	void Draw(HDC screen);
};

