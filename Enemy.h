//
// Created by Quyen on 4/24/2022.
//
#ifndef SPACESHOOTER_ENEMY_H
#define SPACESHOOTER_ENEMY_H

#include "Texture.h"
#include <vector>
#include "Bullet.h"
#include "Character.h"
#include "Support.h"

class Enemy : public Spaceship
{
protected:
    bool hitStatus;

    int enemyType;

    float yLimit;
    float xLimit;

    bool isDead;

    unsigned int point;

    bool canSpawnBullet;
    float angleMove;
    float angleBullet;
    bool immortal;
public:
    Enemy();

    void setVelX( const float &x )
    {
        velX = x;
    }

    void setVelY( const float &y )
    {
        velY = y;
    }

    void render( SDL_Renderer *screen );

    void spawnBullet( SDL_Renderer *screen, std::vector<Bullet *> &enemyBulletList, const Character &player );

    void setHP( const int &health )
    {
        hp = health;
    }

    bool getHitStatus() const
    {
        return hitStatus;
    }

    void setHitStatus( const bool &status )
    {
        hitStatus = status;
    }

    void setType( const int &t )
    {
        enemyType = t;
    }

    int getEnemyType() const
    {
        return enemyType;
    }

    void setYLim( const float &y )
    {
        yLimit = y;
    }

    void setXLim( const float &x )
    {
        xLimit = x;
    }

    float getXLimit() const
    {
        return xLimit;
    }

    float getYLimit() const
    {
        return yLimit;
    }

    float getVelX() const
    {
        return velX;
    }

    float getVelY() const
    {
        return velY;
    }

    void move();

    void updateHitbox();

    void setIsDead( const bool &dead )
    {
        isDead = dead;
    }

    bool getIsDead() const
    {
        return isDead;
    }

    void setPoint( const unsigned int &p )
    {
        point = p;
    }

    unsigned int getPoint() const
    {
        return point;
    }

    void SetCanSpawnBullet( const bool &canSpawn )
    {
        canSpawnBullet = canSpawn;
    }

    bool GetCanSpawnBullet() const
    {
        return canSpawnBullet;
    }

    void spawnBulletOnDie( std::vector<Bullet *> &enemyBulletList, SDL_Renderer *screen );

    void spawnSupportItem( std::vector<SupportItem *> &itemList, SDL_Renderer *screen );

    void spawnBossBullet( std::vector<Bullet *> &enemyBulletList, SDL_Renderer *screen );

    void moveAround();

    void setAngleMove( const float &moveAngle )
    {
        angleMove = moveAngle;
    }

    void setAngle( const float &angleOfBullet )
    {
        angleBullet = angleOfBullet;
    }

    bool checkImmortal() const
    { return immortal; }
};

#endif // SPACESHOOTER_ENEMY_H
