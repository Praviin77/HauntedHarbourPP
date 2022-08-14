#include "RedBullet.h"

RedBullet::RedBullet(int dmg) : BulletObject("../Pics/VBullet.bmp", 7, 7)
{
	hitWidth = width;
	hitHeight = height;

	this->damage = dmg;
}

RedBullet::~RedBullet()
{

}

void RedBullet::SetExplode()
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

void RedBullet::ResetBullet()
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
