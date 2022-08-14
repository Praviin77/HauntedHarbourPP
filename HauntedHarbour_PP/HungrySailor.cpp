#include "HungrySailor.h"

HungrySailor::HungrySailor() : EnemyObject("../Pics/HungrySailor3.bmp", 200, 200, 80, 95)
{
	currentHealth = 100;
	totalHealth = 100;

	xSpeed = 3;

	currentCell = 0;
	startCell = 0;
	endCell = 8;
	bLoopCells = true;
	picX = 15;
	picY = 95;

	moveDelay = 2;
	moveTick = 0;

	numBullets = 5;
	for (int i = 0; i < numBullets; i++)
	{
		bullets[i] = new GreenBullet(10);
	}
}

HungrySailor::~HungrySailor()
{
}

void HungrySailor::Move(PlayerObject* player)
{
	prevX = xPos;
	prevY = yPos;

	xPos += xSpeed;
	yPos += ySpeed += GRAVITY;

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
				FireBullet(xPos + 10, yPos + 30, -5, 0);
			}
			else if (xSpeed > 0)
			{
				FireBullet(xPos + 10, yPos + 30, 5, 0);
			}

		}
	}
	moveTick++;

	if (moveTick == moveDelay)
	{
		Animate();
		moveTick = 0;
	}
}

void HungrySailor::OnHit(BulletObject* projectile)
{
	this->currentHealth -= projectile->damage;

	if (this->currentHealth <= 0)
	{
		currentCell = 0;
		startCell = 9;
		endCell = 10;

		width = 80;
		height = 95;

		picX = 12;
		if (xSpeed < 0)
		{
			this->picY = 0;
		}
		else
		{
			this->picY = 95;
		}

		bLoopCells = false;
		bIsAlive = false;
	}
}

void HungrySailor::CheckCollisionWithCrate(GraphicsObject* crate)
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
			this->picY = 95;
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
