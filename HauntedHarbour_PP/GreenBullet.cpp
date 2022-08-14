#include "GreenBullet.h"

GreenBullet::GreenBullet(int dmg) : BulletObject("../Pics/GreenFire.bmp", 7, 7)
{
	hitWidth = width;
	hitHeight = height;

	this->damage = dmg;
}

GreenBullet::~GreenBullet()
{
}

void GreenBullet::SetExplode()
{
	bIsExploding = true;
	bLoopCells = false;

	endCell = 2;
	currentCell = 0;

	picX = 0;
	picY = 8;

	width = 15;
	height = 15;

	xPos -= 8;
	yPos -= 8;
}

void GreenBullet::ResetBullet()
{
	bIsFired = false;
	bIsExploding = false;

	currentCell = 0;
	endCell = 0;

	picX = 0;
	picY = 0;

	width = 7;
	height = 7;

	distanceTravelled = 0;
	xSpeed = 0;
	ySpeed = 0;
}
