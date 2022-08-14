#include "GroundEnemy.h"

GroundEnemy::GroundEnemy() : EnemyObject("../Pics/SkullCrab.bmp", 200, 200, 28, 35)
{
	xSpeed = 5;

	currentCell = 0;
	startCell = 0;
	endCell = 10;
	bLoopCells = true;
	picX = 0;
	picY = 37;

	numBullets = 5;
	for (int i = 0; i < numBullets; i++)
	{
		bullets[i] = new GreenBullet(10);
	}
}

GroundEnemy::~GroundEnemy()
{

}

void GroundEnemy::Move(PlayerObject* player)
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
				FireBullet(xPos + 10, yPos + 20, -10, 0);
			}
			else if (xSpeed > 0)
			{
				FireBullet(xPos + 10, yPos + 20, 10, 0);
			}

		}
	}

	Animate();
}

void GroundEnemy::OnHit(BulletObject* projectile)
{
	xPos += projectile->xSpeed;

	currentCell = 0;
	endCell = 0;
	bLoopCells = false;

	if (xSpeed < 0)
	{
		picY = 70;
	}
	else
	{
		picY = 105;
	}

	bIsAlive = false;
	xSpeed = 0;
}

void GroundEnemy::CheckCollisionWithCrate(GraphicsObject* crate)
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
			this->picY = 35;
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
