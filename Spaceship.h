//
// Created by Quyen on 4/19/2022.
//

#ifndef SPACESHOOTER_SPACESHIP_H
#define SPACESHOOTER_SPACESHIP_H

#include "Common.h"
#include "Bullet.h"
#include <vector>
#include "Texture.h"

class Spaceship : public Texture
{
protected:
    float posX;
    float posY;

    float velX;
    float velY;

    unsigned long long currentTime;
    unsigned long long lastTime;

    SDL_FRect hitBox;

    int hp;

public:
    Spaceship();

    void setPos( const float &x, const float &y );

    float getPosX() const
    {
        return posX;
    }

    float getPosY() const
    {
        return posY;
    }

    SDL_FRect getHitBox() const
    {
        return hitBox;
    }

    void decreaseHP()
    {
        hp--;
    }

    void IncreaseHP()
    {
        hp++;
    }

    int getHP() const
    {
        return hp;
    }

    void SetHP( const int &rhsHP )
    {
        hp = rhsHP;
    }
};

#endif // SPACESHOOTER_SPACESHIP_H
