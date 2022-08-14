#include "LightHouseKeeper.h"

LightHouseKeeper::LightHouseKeeper() : EnemyObject("../Pics/LightHouseKeeper.bmp", 200, 200, 50, 80)
{
	currentHealth = 70;
	totalHealth = 70;

	xSpeed = 10;

	currentCell = 0;
	startCell = 0;
	endCell = 10;
	bLoopCells = true;
	picX = 5;
	picY = 97;
}

LightHouseKeeper::~LightHouseKeeper()
{
}

void LightHouseKeeper::Move(PlayerObject* player)
{
	prevX = xPos;
	prevY = yPos;

	xPos += xSpeed;
	yPos += ySpeed += GRAVITY;

	if (isColliding(player))
	{
		if (player->currentHealth > 0);
		{
			player->currentHealth -= 50;
		}
		if (player->currentHealth <= 0)
		{
			player->xPos = 100;
			player->yPos = 100;

			player->xSpeed = 0;
			player->ySpeed = 0;

			//player->setStandRight();

			mapPosition = 0;

			player->currentHealth = player->totalHealth;

			player->lives--;
		}
	}

	if (this->yPos > GROUND - this->height)
	{
		this->yPos = GROUND - this->height;
		this->ySpeed = 0;
	}

	if (this->bIsAlive == true)
	{
		int _randNum = rand() % 30;

		if (_randNum == 1)
		{
			if (xSpeed < 0)
			{
				FireBullet(xPos + 10, yPos + 30, -15, 0);
			}
			else if (xSpeed > 0)
			{
				FireBullet(xPos + 10, yPos + 30, 15, 0);
			}

		}
	}

	Animate();
}

void LightHouseKeeper::OnHit(BulletObject* projectile)
{
	this->currentHealth -= projectile->damage;

	if (this->currentHealth <= 0)
	{
		currentCell = 0;
		startCell = 10;
		endCell = 16;

		width = 50;
		height = 80;

		picX = 0;
		if (xSpeed < 0)
		{
			this->picY = 0;
		}
		else
		{
			this->picY = 97;
		}

		bLoopCells = false;
		bIsAlive = false;
	}
}

void LightHouseKeeper::CheckCollisionWithCrate(GraphicsObject* crate)
{
	if (isColliding(crate))
	{
		// from object's left
		if (this->prevX + this->hitWidth <= crate->xPos)
		{
			// turn around
			xSpeed *= -1;
			this->xPos = crate->xPos - this->hitWidth;
			this->picY = 0;
		}
		// from object's right
		else if (this->prevX >= crate->xPos + crate->hitWidth)
		{
			xSpeed *= -1;
			this->xPos = crate->xPos + crate->hitWidth;
			this->picY = 97;
		}
		// from object's top
		else if (this->prevY + this->hitHeight <= crate->yPos)
		{
			ySpeed = 0;
			this->yPos = crate->yPos - this->hitHeight;
		}
		// from object's bottom
		else if (this->prevY >= crate->yPos + crate->hitHeight)
		{
			ySpeed = 0;
			this->yPos = crate->yPos + crate->hitHeight;
		}
	}
}
