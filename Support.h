//
// Created by Quyen on 5/14/2022.
//

#ifndef SPACESHOOTER_SUPPORT_H
#define SPACESHOOTER_SUPPORT_H

#include "Texture.h"

enum SupportType
{
HEALTH = 0,
SHIELD = 1,
BULLET = 2,
};

class SupportItem : public Texture
{
protected:
    float posX;
    float posY;
    float xVel;
    float yVel;

    SDL_FRect boundingBox;

    SupportType type;

    bool isMove;

public:
    SupportItem();

    void setPos( const float &x, const float &y )
    {
        posX = x;
        posY = y;
    }

    void setXVel( const float &x )
    {
        xVel = x;
    }

    void setYVel( const float &y )
    {
        yVel = y;
    }

    float getPosX() const
    {
        return posX;
    }

    float getPosY() const
    {
        return posY;
    }

    float getXVel() const
    {
        return xVel;
    }

    float getYVel() const
    {
        return yVel;
    }

    void updateBoundingBox()
    {
        boundingBox.x = posX;
        boundingBox.y = posY;
        boundingBox.w = mTextureWidth;
        boundingBox.h = mTextureHeight;
    }

    void setType( const SupportType &t )
    {
        type = t;
    }

    SupportType getSupportType() const
    {
        return type;
    }

    void setIsMove( const bool &move )
    {
        isMove = move;
    }

    bool getIsMove()
    {
        return isMove;
    }

    void move();

    void render( SDL_Renderer *screen );

    SDL_FRect getBoundingBox() const
    {
        return boundingBox;
    }
};

#endif // SPACESHOOTER_SUPPORT_H
