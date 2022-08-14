#pragma once

#include "EnemyObject.h"
#include "PlayerObject.h"
#include "RedBullet.h"

class LightHouseKeeper :
    public EnemyObject
{
public:
    LightHouseKeeper();
    ~LightHouseKeeper();

    void Move(PlayerObject* player);
    void OnHit(BulletObject* projectile);
    void CheckCollisionWithCrate(GraphicsObject* crate);
};

