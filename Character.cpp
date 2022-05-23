//
// Created by Quyen on 5/5/2022.
//

#include "Character.h"

Character::Character()
{
    dead = false;
    haveShield = false;
    bulletLevel = 1;
    shieldTime = 0;
}

void Character::render( SDL_Renderer *gRenderer, int &frame )
{
    frame++;
    if ( frame > 8 )
        frame = 1;
    SDL_Rect quad1 = { 0, 0, (int)mTextureWidth, (int)mTextureHeight };
    SDL_Rect quad2 = { 0 + (int)mTextureWidth, 0, (int)mTextureWidth, (int)mTextureHeight };
    SDL_FRect renderquad{ posX, posY, mTextureWidth, mTextureHeight };
    if ( frame > 0 && frame <= 4 )
    {
        SDL_RenderCopyF(gRenderer, mTexture, &quad1, &renderquad);
    }
    else if ( frame > 4 && frame <= 8 )
    {
        SDL_RenderCopyF(gRenderer, mTexture, &quad2, &renderquad);
    }
}

void Character::handleInputAction( SDL_Event &e )
{
    if ( e.type == SDL_MOUSEMOTION )
    {
        int x = e.motion.x;
        int y = e.motion.y;
        posX = x - mTextureWidth / 2;
        posY = y - mTextureHeight / 2;
        updateHitbox();
    }
}

void Character::spawnBullet( SDL_Renderer *screen, Mix_Chunk *shoot )
{
    currentTime = SDL_GetTicks();
    int delayTime = 150;
    if ( currentTime - lastTime >= delayTime )
    {
        Mix_PlayChannel(1, shoot, 0);
        for ( int i = 0; i < bulletLevel; i++ )
        {
            Bullet *bullet = new Bullet;
            bullet->loadTexture("img/bullet.png", screen);
            if ( bulletLevel == 3 && i == 1 )
            {
                bullet->setPos(posX + mTextureWidth / 2 -
                               ( bulletLevel * BULLET_FRAME_WIDTH ) / 2 + i * BULLET_FRAME_WIDTH,
                               posY - 30);
            }
            else
            {
                bullet->setPos(posX + mTextureWidth / 2 -
                               ( bulletLevel * BULLET_FRAME_WIDTH ) / 2 + i * BULLET_FRAME_WIDTH,
                               posY - 20);
            }

            bullet->setYVel(-5);
            bullet->setXVel(0);
            bullet->updateBoundingBox();
            characterBulletList.push_back(bullet);
            lastTime = currentTime;
        }
    }
}

void Character::handleBullet( SDL_Renderer *screen )
{
    for ( int i = 0; i < characterBulletList.size(); i++ )
    {
        auto playerBullet = characterBulletList[i];
        if ( playerBullet->getIsMove())
        {
            playerBullet->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            playerBullet->render(screen);
        }
        else
        {
            characterBulletList.erase(characterBulletList.begin() + i);
            if ( playerBullet != nullptr )
            {
                delete playerBullet;
                playerBullet = nullptr;
            }
        }
    }
}

void Character::powerUp( const SupportItem *s )
{
    if ( s->getSupportType() == HEALTH )
    {
        hp++;
        if ( hp >= 3 )
            hp = 3;
    }
    else if ( s->getSupportType() == BULLET )
    {
        bulletLevel++;
        if ( bulletLevel >= 3 )
            bulletLevel = 3;
    }
    else if ( s->getSupportType() == SHIELD )
    {
        haveShield = true;
        shieldTime = SDL_GetTicks();
    }
}

void Character::loadCharacter( SDL_Renderer *screen )
{
    if ( haveShield && SDL_GetTicks() - shieldTime >= 7000 )
    {
        haveShield = false;
    }
    if ( !haveShield )
    {
        loadTexture("img/Spaceship.png", screen);
        mTextureWidth = NORMAL_FRAME_EDGE;
        mTextureHeight = NORMAL_FRAME_EDGE;
    }
    else
    {
        loadTexture("img/shield_spaceship.png", screen);
        mTextureHeight = SHIELD_FRAME_EDGE;
        mTextureWidth = SHIELD_FRAME_EDGE;
    }
}

void Character::updateHitbox()
{
    if ( haveShield )
    {
        hitBox.w = SHIELD_FRAME_EDGE;
        hitBox.h = SHIELD_FRAME_EDGE;
        hitBox.x = posX;
        hitBox.y = posY;
    }
    else
    {
        hitBox.w = NORMAL_HITBOX_EDGE;
        hitBox.h = NORMAL_HITBOX_EDGE;
        hitBox.x = posX + ( NORMAL_FRAME_EDGE - NORMAL_HITBOX_EDGE ) / 2;
        hitBox.y = posY + ( NORMAL_FRAME_EDGE - NORMAL_HITBOX_EDGE ) / 2;
    }
}

void Character::setShieldTime( const unsigned long long &rhsShieldTime )
{
    shieldTime = rhsShieldTime;
}

void Character::reset()
{
    posX = SCREEN_WIDTH / 2 - mTextureWidth / 2;
    posY = SCREEN_HEIGHT - 100;
    hp = 3;
    bulletLevel = 1;
    haveShield = false;
    dead = false;
    characterBulletList.clear();
}