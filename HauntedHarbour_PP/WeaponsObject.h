#pragma once

#include "GraphicsObject.h"
#include "BulletObject.h"

class WeaponsObject :
    public GraphicsObject
{
public:
    int numBullets;
    int xSpeed, ySpeed;
    int currentHealth, totalHealth;

    BulletObject* bullets[50]; //Pointer variable, stores memory address

    WeaponsObject(CString fileName, int xPos, int yPos, int w, int h);
    ~WeaponsObject();

    void FireBullet(int xPos, int yPos, int xSpd, int ySpd);
    void DrawBullet(HDC offScreenDc);
    void MoveBullets();
    void CheckBulletCollisionWithEntity(WeaponsObject* entity);
    void CheckBulletCollisionWithCrate(GraphicsObject* crate);
    virtual void OnHit(BulletObject* projectile) {};
};

