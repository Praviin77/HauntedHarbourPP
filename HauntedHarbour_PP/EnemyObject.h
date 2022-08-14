#pragma once

#include "WeaponsObject.h"
#include "PlayerObject.h"

class EnemyObject :
    public WeaponsObject
{
public:
    bool bIsAlive;

    EnemyObject(CString fileName, int xPos, int yPos, int w, int h) : WeaponsObject(fileName, xPos, yPos, w, h)
    {
        bIsAlive = true;

        xSpeed = 0;
        ySpeed = 0;
    }

    ~EnemyObject() {}

    virtual void Move(PlayerObject* player) = 0;
    virtual void OnHit(BulletObject* projectile) = 0;
    virtual void CheckCollisionWithCrate(GraphicsObject* crate) = 0;
};

