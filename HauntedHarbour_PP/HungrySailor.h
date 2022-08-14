#pragma once

#include "EnemyObject.h"
#include "GreenBullet.h"
#include "PlayerObject.h"

class HungrySailor :
    public EnemyObject
{
public:
    int moveDelay, moveTick;

    HungrySailor();
    ~HungrySailor();

    void Move(PlayerObject* player);
    void OnHit(BulletObject* projectile);
    void CheckCollisionWithCrate(GraphicsObject* crate);
};

