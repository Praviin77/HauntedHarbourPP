#pragma once

#include "GreenBullet.h"
#include "EnemyObject.h"
#include "PlayerObject.h"

class GroundEnemy :
    public EnemyObject
{
public:
    GroundEnemy();
    ~GroundEnemy();

    void Move(PlayerObject* player);
    void OnHit(BulletObject* projectile);
    void CheckCollisionWithCrate(GraphicsObject* crate);
};

