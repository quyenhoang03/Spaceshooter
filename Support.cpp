//
// Created by Quyen on 5/14/2022.
//

#include "Support.h"

SupportItem::SupportItem()
{
    posY = 0;
    posX = 0;
    xVel = 0;
    yVel = 0;
    isMove = false;
    type = HEALTH;
}

void SupportItem::move()
{
    posX += xVel;
    posY += yVel;
    if ( posX < 0 || posY < 0 || posX >= SCREEN_WIDTH || posY >= SCREEN_HEIGHT )
    {
        isMove = false;
    }
    updateBoundingBox();
}

void SupportItem::render( SDL_Renderer *screen )
{
    SDL_RenderCopyF(screen, mTexture, nullptr, &boundingBox);
}
