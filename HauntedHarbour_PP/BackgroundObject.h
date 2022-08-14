#pragma once

#include "GraphicsObject.h"

class BackgroundObject :
    public GraphicsObject
{
public:
    double scrollSpeed;

    BackgroundObject(CString fileName, int xPos, int yPos, int width, int height, double scrSpd);
    ~BackgroundObject();

    void Draw(HDC offScreenDC);
};

