#include "PurpleBullet.h"

PurpleBullet::PurpleBullet(int dmg) : BulletObject("../Pics/Purplefire.bmp", 12, 12)
{
	hitWidth = width;
	hitHeight = height;

	this->damage = dmg;
}

PurpleBullet::~PurpleBullet()
{
}

void PurpleBullet::SetExplode()
{
	bIsExploding = true;
	bLoopCells = false;

	endCell = 2;
	currentCell = 0;

	picX = 0;
	picY = 12;

	width = 32;
	height = 32;

	xPos -= 12;
	yPos -= 12;
}

void PurpleBullet::ResetBullet()
{
	bIsFired = false;
	bIsExploding = false;

	currentCell = 0;
	endCell = 0;

	picX = 0;
	picY = 0;

	width = 12;
	height = 12;

	distanceTravelled = 0;
	xSpeed = 0;
	ySpeed = 0;
}
