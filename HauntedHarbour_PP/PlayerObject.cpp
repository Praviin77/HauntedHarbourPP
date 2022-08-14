#include "PlayerObject.h"

PlayerObject::PlayerObject() : WeaponsObject("../Pics/ViktorTesla.bmp", 100, 100, 54, 42)
{
	setStandRight();

	lives = 3;
	
	xSpeed = 0;
	ySpeed = 0;

	currentHealth = 100;
	totalHealth = 100;

	bIsStoppedLeft = false;
	bIsStoppedRight = true;

	numBullets = 10; // max number of bullets to be fired by viktor at once

	for (int i = 0; i < numBullets; i++)
	{
		bullets[i] = new PurpleBullet(30);
	}
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::Move()
{
	prevX = xPos;
	prevY = yPos;

	xPos += xSpeed;
	yPos += ySpeed;

	ySpeed += GRAVITY;

	if (yPos > GROUND - height)
	{
		if (state == JUMP_RIGHT && bIsStoppedRight == true)
			setStandRight();
		else if (state == JUMP_LEFT && bIsStoppedLeft == true)
			setStandLeft();
		else if (state == JUMP_RIGHT && bIsStoppedRight == false)
			setMoveRight();
		else if (state == JUMP_LEFT && bIsStoppedLeft == false)
			setMoveLeft();

		yPos = GROUND - height;
		ySpeed = 0;
	}
	if ((xPos - mapPosition < 100 && xSpeed < 0) || (xPos - mapPosition> 350 && xSpeed > 0))
	{
		mapPosition += xSpeed;
	}

	Animate();
}

void PlayerObject::setMoveRight()
{
	width = 54;
	height = 42;
	picX = 60;
	picY = 0;
	//currentCell = 0;
	startCell = 1;
	endCell = 9;
	bLoopCells = true;
	xSpeed = 10;
	//ySpeed = ySpeed;
	state = MOVE_RIGHT;
}

void PlayerObject::setMoveLeft()
{
	width = 54;
	height = 42;
	picX = 0;
	picY = 42; //y position in the sprite strip
	//currentCell = 0;
	startCell = 1;
	endCell = 9;
	bLoopCells = true;
	xSpeed = -10;
	// ySpeed = ySpeed;
	state = MOVE_LEFT;

}

void PlayerObject::setStandRight()
{
	width = 54;
	height = 42;
	picX = 0;
	picY = 0; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 0;
	bLoopCells = false;
	xSpeed = 0;
	// ySpeed = ySpeed;
	state = STAND_RIGHT;

}

void PlayerObject::setStandLeft()
{
	width = 54;
	height = 42;
	picX = 0;
	picY = 42; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 0;
	bLoopCells = false;
	xSpeed = 0;
	//ySpeed = ySpeed;
	state = STAND_LEFT;

}

void PlayerObject::setJumpRight()
{
	width = 48;
	height = 56;
	picX = 0;
	picY = 86; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 5;
	bLoopCells = false;
	//xSpeed = -10;
	ySpeed = -30;
	state = JUMP_RIGHT;

}

void PlayerObject::setJumpLeft()
{
	width = 48;
	height = 56;
	picX = 0;
	picY = 146; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 5;
	bLoopCells = false;
	//xSpeed = -10;
	ySpeed = -30;
	state = JUMP_LEFT;

}

void PlayerObject::setShootRight()
{
	width = 60;
	height = 38;
	picX = 0;
	picY = 199; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 0;
	bLoopCells = false;
	xSpeed = 0;
	//ySpeed = -30;
	state = SHOOT_RIGHT;

}

void PlayerObject::setShootLeft()
{
	width = 60;
	height = 38;
	picX = 0;
	picY = 237; //y position in the sprite strip
	currentCell = 0;
	startCell = 0;
	endCell = 0;
	bLoopCells = false;
	xSpeed = 0;
	//ySpeed = -30;
	state = SHOOT_LEFT;

}

void PlayerObject::CheckPlayerCollisionWithEntity(GraphicsObject* entity)
{
	if (isColliding(entity))
	{
		// from object's left
		if (this->prevX + this->hitWidth <= entity->xPos)
		{
			this->xPos = entity->xPos - this->hitWidth;
		}
		// from object's right
		else if (this->prevX >= entity->xPos + entity->hitWidth)
		{
			this->xPos = entity->xPos + entity->hitWidth;
		}
		// from object's top
		else if (this->prevY + this->hitHeight <= entity->yPos)
		{
			if (state == JUMP_RIGHT && bIsStoppedRight == true)
			{
				setStandRight();
			}
			else if (state == JUMP_LEFT && bIsStoppedLeft == true)
			{
				setStandLeft();
			}
			else if (state == JUMP_RIGHT && bIsStoppedRight == false)
			{
				setMoveRight();
			}
			else if (state == JUMP_LEFT && bIsStoppedLeft == false)
			{
				setMoveLeft();
			}

			this->yPos = entity->yPos - this->hitHeight;
			this->ySpeed = 0;
		}
		// from object's bottom
		else if (this->prevY >= entity->yPos + entity->hitHeight)
		{
			this->yPos = entity->yPos + entity->hitHeight;
			this->ySpeed = 0;
		}
	}
}

void PlayerObject::OnHit(BulletObject* projectile)
{
	xPos += projectile->xSpeed;
	this->currentHealth -= projectile->damage;

	if (this->currentHealth <= 0)
	{
		xPos = 100;
		yPos = 100;

		xSpeed = 0;
		ySpeed = 0;

		setStandRight();

		mapPosition = 0;

		currentHealth = totalHealth;

		lives--;
	}
}

bool PlayerObject::IsJumping()
{
	return (state == JUMP_RIGHT || state == JUMP_LEFT);
}
