//
// Created by Quyen on 4/19/2022.
//

#include "Bullet.h"

Bullet::Bullet()
{
    xVel = 0;
    yVel = 0;
    isMove = true;
    type = NORMAL_TYPE;
    startPos = 0;
    posX = 0;
    posY = 0;
}

void Bullet::handleMove( const int &xBorder, const int &yBorder )
{
    if ( type == SINE_TYPE )
    {
        posY += yVel;
        posX = startPos + 50 * sin(posY / 180 * PI);
    }
    else
    {
        posX += xVel;
        posY += yVel;
    }

    if ( posX > xBorder + 150 || posY > yBorder + 150 || posX < -150 || posY < -150 )
    {
        isMove = false;
    }
    boundingBox.x = posX;
    boundingBox.y = posY;
}

void Bullet::render( SDL_Renderer *des )
{
    SDL_FRect quad = { posX, posY, mTextureWidth, mTextureHeight };
    SDL_RenderCopyF(des, mTexture, nullptr, &quad);
}