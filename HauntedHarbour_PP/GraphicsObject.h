#pragma once

#include <atlstr.h>
#include <atlimage.h>
#include "framework.h"

class GraphicsObject
{
public:
	CString ID;
	CImage image;

	int width, height;
	int xPos, yPos;
	int picX, picY;
	int startCell, currentCell, endCell;
	int hitWidth, hitHeight;
	int prevX, prevY;
	int currentHealth;

	bool bLoopCells;

	GraphicsObject(CString fileName, int xPos, int yPos, int w, int h);
	~GraphicsObject();

	void Draw(HDC offScreenDC);
	void Animate();

	bool isColliding(GraphicsObject* entity);
};

