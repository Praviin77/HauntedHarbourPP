#include "WeaponsObject.h"

WeaponsObject::WeaponsObject(CString fileName, int xPos, int yPos, int w, int h) : GraphicsObject(fileName, xPos, yPos, w, h)
{
	this->width = w;
	this->height = h;
}

WeaponsObject::~WeaponsObject()
{

}

void WeaponsObject::FireBullet(int xPos, int yPos, int xSpd, int ySpd)
{
	for (int i = 0; i < numBullets; i++)
	{
		if (bullets[i]->bIsFired == false)
		{
			bullets[i]->xPos = xPos;
			bullets[i]->yPos = yPos;
			bullets[i]->xSpeed = xSpd;
			bullets[i]->ySpeed = ySpd;

			bullets[i]->bIsFired = true;
			bullets[i]->distanceTravelled = 0;

			break;
		}
	}
}

void WeaponsObject::DrawBullet(HDC offScreenDc)
{
	for (int i = 0; i < numBullets; i++)
	{
		if (bullets[i]->bIsFired == true)
		{
			bullets[i]->Draw(offScreenDc);
		}
	}
}

void WeaponsObject::MoveBullets()
{
	for (int i = 0; i < numBullets; i++)
	{
		if (bullets[i]->bIsFired == true)
		{
			bullets[i]->Move();
		}
	}
}

void WeaponsObject::CheckBulletCollisionWithEntity(WeaponsObject* entity)
{
	for (int i = 0; i < numBullets; i++)
	{
		if (bullets[i] != nullptr && bullets[i]->bIsFired == true)
		{
			if (bullets[i]->isColliding(entity) == true && bullets[i]->bIsExploding == false)
			{
				if (abs(bullets[i]->xPos - entity->xPos) < abs(bullets[i]->xPos - (entity->xPos + entity->width)))
				{
					bullets[i]->xPos = entity->xPos;
				}
				else if (abs(bullets[i]->xPos - entity->xPos) > abs(bullets[i]->xPos - (entity->xPos + entity->width)))
				{
					bullets[i]->xPos = entity->xPos + entity->width;
				}

				entity->OnHit(bullets[i]);
				bullets[i]->SetExplode();
			}
		}
	}
}

void WeaponsObject::CheckBulletCollisionWithCrate(GraphicsObject* crate)
{
	for (int i = 0; i < numBullets; i++)
	{
		if (bullets[i] != nullptr && bullets[i]->bIsFired == true)
		{
			if (bullets[i]->isColliding(crate) == true && bullets[i]->bIsExploding == false)
			{
				if (abs(bullets[i]->xPos - crate->xPos) < abs(bullets[i]->xPos - (crate->xPos + crate->width)))
				{
					bullets[i]->xPos = crate->xPos;
				}
				else if (abs(bullets[i]->xPos - crate->xPos) > abs(bullets[i]->xPos - (crate->xPos + crate->width)))
				{
					bullets[i]->xPos = crate->xPos + crate->width;
				}

				bullets[i]->SetExplode();
			}
		}
	}
}
