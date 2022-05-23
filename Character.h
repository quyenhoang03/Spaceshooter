//
// Created by Quyen on 5/5/2022.
//

#ifndef SPACESHOOTER_CHARACTER_H
#define SPACESHOOTER_CHARACTER_H

#include "Spaceship.h"
#include "Support.h"
#include <vector>

#define SHIELD_FRAME_EDGE 60
#define NORMAL_FRAME_EDGE 48
#define NORMAL_HITBOX_EDGE 5

class Character : public Spaceship
{
protected:
    std::vector<Bullet *> characterBulletList;
    bool dead;
    int bulletLevel;
    bool haveShield;
    unsigned long long shieldTime;

public:
    Character();

    void render( SDL_Renderer *screen, int &frame );

    void handleInputAction( SDL_Event &e );

    void spawnBullet( SDL_Renderer *screen, Mix_Chunk *shoot );

    void handleBullet( SDL_Renderer *screen );

    std::vector<Bullet *> getBulletList() const
    {
        return characterBulletList;
    }

    void setDead( bool d )
    {
        dead = d;
    }

    bool getDead() const
    {
        return dead;
    }

    void powerUp( const SupportItem *s );

    void increaseBulletLevel()
    {
        bulletLevel++;
    }

    void decreaseBulletLevel()
    {
        if ( bulletLevel > 1 )
        {
            bulletLevel--;
        }
    }

    void setBulletLevel( const int &level )
    {
        bulletLevel = level;
    }

    int getBulletLevel() const
    {
        return bulletLevel;
    }

    bool getHaveShield() const
    {
        return haveShield;
    }

    void setHaveShield( const bool &shield )
    {
        haveShield = shield;
    }

    void loadCharacter( SDL_Renderer *screen );

    void updateHitbox();

    void setShieldTime( const unsigned long long &rhsShieldTime );

    unsigned long long getShieldTime() const
    {
        return shieldTime;
    }

    void reset();
};

#endif // SPACESHOOTER_CHARACTER_H
