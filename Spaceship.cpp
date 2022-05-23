//
// Created by Quyen on 4/19/2022.
//

#include "Spaceship.h"

Spaceship::Spaceship()
{
    posX = 0;
    posY = 0;
    velX = 0;
    velY = 0;
    hp = 1;
    currentTime = 0;
    lastTime = 0;
}

void Spaceship::setPos(const float &x, const float &y)
{
    posX = x;
    posY = y;
}
