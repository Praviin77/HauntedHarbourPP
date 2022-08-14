#include "BulletObject.h"

BulletObject::BulletObject(CString fileName, int w, int h) : GraphicsObject(fileName, 0, 0, w, h)
{
	bIsFired = false;
	bIsExploding = false;

	this->width = w;
	this->height = h;

	distanceTravelled = 0;
	maxDistance = 300;

	xSpeed = 0;
	ySpeed = 0;
}

BulletObject::~BulletObject()
{
}

void BulletObject::Move()
{
	Animate();

	if (this->bIsExploding == true)
	{
		if (currentCell == endCell)
		{
			ResetBullet();
		}
	}
	else
	{
		xPos += xSpeed;
		yPos += ySpeed;

		distanceTravelled += abs(xSpeed) + abs(ySpeed);

		if (distanceTravelled >= maxDistance)
		{
			bIsFired = false;
			distanceTravelled = 0;
		}
	}
}

void BulletObject::SetExplode()
{
	
}

void BulletObject::ResetBullet()
{
	
}

