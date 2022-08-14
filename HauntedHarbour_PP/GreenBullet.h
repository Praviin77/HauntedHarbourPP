#pragma once

#include "BulletObject.h"

class GreenBullet :
    public BulletObject
{
public:
    GreenBullet(int dmg);
    ~GreenBullet();

    void SetExplode();
    void ResetBullet();
};

