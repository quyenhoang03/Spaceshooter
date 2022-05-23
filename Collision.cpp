//
// Created by Quyen on 5/19/2022.
//

#include "Collision.h"

bool checkCollision( const SDL_FRect &object1, const SDL_FRect &object2 )
{
    if ( object1.x + object1.w >= object2.x && object2.x + object2.w >= object1.x
         && object1.y + object1.h >= object2.y && object2.y + object2.h >= object1.y )
    {
        return true;
    }
    return false;
}