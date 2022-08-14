#pragma once

#include "EnemyObject.h"
#include "RedBullet.h"
#include "PlayerObject.h"
#define _USE_MATH_DEFINES
#include <math.h>

class FlyingEnemy :
    public EnemyObject
{
public:
    int radius, angle;
    int centerX, centerY;
    int shootTick, shootDelay;

    PlayerObject* viktor;

    FlyingEnemy(PlayerObject* target, int cX, int cY);
    ~FlyingEnemy();

    void Move(PlayerObject* player);
    void OnHit(BulletObject* projectile);
    void CheckCollisionWithCrate(GraphicsObject* crate);
    void Fire();
};

