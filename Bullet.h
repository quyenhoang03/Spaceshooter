//
// Created by Quyen on 4/19/2022.
//

#ifndef SPACESHOOTER_BULLET_H
#define SPACESHOOTER_BULLET_H

#include "Common.h"
#include "Texture.h"

#define BULLET_FRAME_WIDTH 18
#define BULLET_FRAME_HEIGHT 33

enum BulletType
{
NORMAL_TYPE = 0,
SINE_TYPE = 1,
};

class Bullet : public Texture
{
protected:
    float posX;
    float posY;

    float xVel;
    float yVel;

    bool isMove;
    SDL_FRect boundingBox;

    BulletType type;
    float startPos;

public:
    Bullet();

    void setIsMove( const bool &move )
    {
        isMove = move;
    }

    bool getIsMove() const
    {
        return isMove;
    }

    void setXVel( const float &x )
    {
        xVel = x;
    }

    void setYVel( const float &y )
    {
        yVel = y;
    }

    void handleMove( const int &xBorder, const int &yBorder );

    void render( SDL_Renderer *des );

    SDL_FRect getBoudingBox() const
    {
        return boundingBox;
    }

    void setPos( const float &x, const float &y )
    {
        posX = x;
        posY = y;
    }

    float getPosX() const
    {
        return posX;
    }

    float getPosY() const
    {
        return posY;
    }

    void updateBoundingBox()
    {
        boundingBox.x = posX;
        boundingBox.y = posY;
        boundingBox.w = mTextureWidth;
        boundingBox.h = mTextureHeight;
    }

    void setType( const BulletType &t )
    {
        type = t;
    }

    void setStartPos( const float &start )
    {
        startPos = start;
    }
};

#endif // SPACESHOOTER_BULLET_H
