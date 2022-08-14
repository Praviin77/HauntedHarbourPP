#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(CString fileName, int xPos, int yPos, int width, int height, double scrSpd): GraphicsObject(fileName, xPos, yPos, width, height)
{
	this->width = width;
	this->height = height;
	this->scrollSpeed = scrSpd;

}

BackgroundObject::~BackgroundObject()
{
}

void BackgroundObject::Draw(HDC offScreenDC)
{
	int _relativeX = (int)((xPos - mapPosition) * scrollSpeed) % width;

	//Set the pink color for corresponding RGB values
	image.SetTransparentColor(RGB(255, 174, 201));

	// Draw on the screen
	image.TransparentBlt(offScreenDC, _relativeX, yPos, width, height, 0, 0, width, height); // Center                    
	image.TransparentBlt(offScreenDC, _relativeX + width, yPos, width, height, 0, 0, width, height); // right
	image.TransparentBlt(offScreenDC, _relativeX - width, yPos, width, height, 0, 0, width, height); // left
}
