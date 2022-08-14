#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(PlayerObject* target, int cX, int cY) : EnemyObject("../Pics/SeaHag.bmp", 200, 200, 28, 39)
{
	this->viktor = target;

	currentHealth = 30;
	totalHealth = 30;

	currentCell = 0;
	endCell = 4;
	startCell = 0;

	bLoopCells = true;

	xSpeed = -5;
	ySpeed = 0;

	radius = 20;
	centerX = cX;
	centerY = cY;
	angle = 0;

	shootDelay = 30;
	shootTick = 0;

	numBullets = 20;

	for (int i = 0; i < numBullets; i++)
	{
		bullets[i] = new RedBullet(20);
		bullets[i]->maxDistance = 400;
	}
}

FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::Move(PlayerObject* player)
{
	if (this->bIsAlive == true)
	{
		double _radians = (double)angle / 180 * M_PI;

		xPos = centerX + radius * cos(_radians);
		yPos = centerY + radius * sin(_radians);

		angle += 10; // move counter clockwise

		if (angle >= 360)
		{
			angle = 0;
		}

		shootTick++;

		if (shootTick == shootDelay)
		{
			Fire();
			shootTick = 0;
		}
	}

	Animate();
}

void FlyingEnemy::OnHit(BulletObject* projectile)
{
	this->currentHealth -= projectile->damage;

	if (this->currentHealth <= 0)
	{
		currentCell = 0;
		startCell = 0;
		endCell = 6;

		width = 32;
		height = 28;

		picX = 0;
		picY = 156;

		bLoopCells = false;
		bIsAlive = false;
	}
}

void FlyingEnemy::CheckCollisionWithCrate(GraphicsObject* crate)
{
}

void FlyingEnemy::Fire()
{
	double _xDistance = abs((this->xPos + width / 2) - (viktor->xPos + viktor-> width / 2));
	double _yDistance = abs((this->yPos + height / 2) - (viktor->yPos + viktor->height / 2));

	int _xSide = 1;
	int _ySide = 1;

	if (viktor->xPos < this->xPos)
	{
		_xSide = -1;
	}
	if (viktor->yPos < this->yPos)
	{
		_ySide = -1;
	}

	if (_xDistance > _yDistance)
	{
		FireBullet(
			this->xPos + this->width / 2, 
			this->yPos + this->height / 2, 
			10 * _xSide, 
			10 * _yDistance / _xDistance * _ySide);
	}
	else
	{
		FireBullet(
			this->xPos + this->width / 2,
			this->yPos + this->height / 2,
			10 * _xDistance / _yDistance * _xSide,
			10 * _ySide);
	}
}
