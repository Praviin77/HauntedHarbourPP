#include "GraphicsObject.h"

GraphicsObject::GraphicsObject(CString fileName, int xPos, int yPos, int w, int h)
{
	ID = fileName;
	this->width = w;
	this->height = h;

	hitWidth = width;
	hitHeight = height;

	this->xPos = xPos;
	this->yPos = yPos;

	picX = 0;
	picY = 0;

	startCell = 0;
	currentCell = 0;
	endCell = 0;

	bLoopCells = false;

	image.Load(ID);
}

GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::Draw(HDC offScreenDC)
{
	//Set the pink color for corresponding RGB values
	image.SetTransparentColor(RGB(255, 174, 201));

	// Draw on the screen
	image.TransparentBlt(offScreenDC, //Destination Device Context 
		xPos- mapPosition,          // x position of the destination DC
		yPos,                       // y position of the destination DC
		width,                      // width of the dest DC
		height,                     // height of the dest DC
		picX,                       // x position of the source DC
		picY,                       // y position of the source DC
		width,                      // width of the src DC
		height);                    // height of the src DC
}

void GraphicsObject::Animate()
{
	// update current cell
	currentCell++;

	// look back to the begining
	if (currentCell >= endCell)
	{
		if (bLoopCells == true)
		{
			currentCell = startCell;
		}
		else
		{
			currentCell = endCell;
		}
	}

	// Update the drawing position
	picX = width * currentCell;
}

bool GraphicsObject::isColliding(GraphicsObject* entity)
{
	if ((this->xPos + hitWidth > entity->xPos) &&
		(this->xPos < entity->xPos + entity->hitWidth))
	{
		if ((this->yPos + hitHeight > entity->yPos) &&
			(this->yPos < entity->yPos + entity->hitHeight))
		{
			return true;
		}
	}
	return false;
}
