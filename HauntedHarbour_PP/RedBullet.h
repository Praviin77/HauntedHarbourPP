#pragma once

#include "BulletObject.h"

class RedBullet :
    public BulletObject
{
public:
    RedBullet(int dmg);
    ~RedBullet();

    void SetExplode();
    void ResetBullet();

};

