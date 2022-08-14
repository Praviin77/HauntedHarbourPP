#pragma once

#include "GraphicsObject.h"
#include <math.h>

class BulletObject :
    public GraphicsObject
{
public:
    int xSpeed, ySpeed;
    int distanceTravelled, maxDistance;
    int damage;
    bool bIsFired;
    bool bIsExploding;

    BulletObject(CString fileName,int w, int h);
    ~BulletObject();

    void Move();
    virtual void SetExplode();
    virtual void ResetBullet();
};

