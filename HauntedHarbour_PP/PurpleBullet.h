#pragma once

#include "BulletObject.h"

class PurpleBullet :
    public BulletObject
{
public:

    PurpleBullet(int dmg);
    ~PurpleBullet();

    void SetExplode();
    void ResetBullet();
};

