//
// Created by Quyen on 4/24/2022.
//

#include "Enemy.h"

Enemy::Enemy()
{
    hp = 0;
    hitStatus = false;
    enemyType = 0;
    xLimit = 1000;
    yLimit = 1000;
    lastTime = SDL_GetTicks();
    isDead = false;
    point = 0;
    canSpawnBullet = false;
    angleMove = 0;
    angleBullet = 0;
    immortal = true;
}

void Enemy::render(SDL_Renderer *screen)
{
    SDL_FRect renderquad{posX, posY, mTextureWidth, mTextureHeight};
    SDL_RenderCopyF(screen, mTexture, nullptr, &renderquad);
    // Render boss health bar
    if (enemyType == 100)
    {
        const float outterRectWidth = 500;
        const float outterRectHeight = 30;
        float innerRectWidth = (float)hp / 500 * (outterRectWidth - 4);
        const float innerRectHeight = outterRectHeight - 4;
        SDL_SetRenderDrawBlendMode(screen, SDL_BLENDMODE_BLEND);
        SDL_FRect outterRect = {(float)SCREEN_WIDTH / 2 - outterRectWidth / 2, 60, outterRectWidth, outterRectHeight};
        SDL_FRect innnerRect = {2 + outterRect.x, 2 + outterRect.y, innerRectWidth, innerRectHeight};
        SDL_SetRenderDrawColor(screen, 255, 255, 255, 255 / 2);
        SDL_RenderFillRectF(screen, &outterRect);
        SDL_SetRenderDrawColor(screen, 255, 0, 0, 255 / 2);
        SDL_RenderFillRectF(screen, &innnerRect);
        SDL_SetRenderDrawBlendMode(screen, SDL_BLENDMODE_NONE);
    }
}

void Enemy::spawnBullet(SDL_Renderer *screen, std::vector<Bullet *> &enemyBulletList, const Character &player)
{
    if (enemyType == 01 || enemyType == 02)
    {
        int delayTime = 700;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            srand(SDL_GetTicks());
            angleBullet = rand() % 90 + 30;
            Bullet *enemyBullet = new Bullet;
            enemyBullet->loadTexture("img/enemyBullet0.png", screen);
            enemyBullet->setIsMove(true);
            enemyBullet->setPos(posX + (mTextureWidth - enemyBullet->getTextureWidth()) / 2,
                                posY + mTextureHeight);
            enemyBullet->updateBoundingBox();
            enemyBullet->setXVel(2 * cos(angleBullet / 180 * PI));
            enemyBullet->setYVel(2 * sin(angleBullet / 180 * PI));
            enemyBulletList.push_back(enemyBullet);
            lastTime = currentTime;
        }
    }
    else if (enemyType == 11 || enemyType == 12)
    {
        int delayTime = 700;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            for (int i = 0; i < 2; i++)
            {
                angleBullet = 60 + 60 * i;
                auto enemyBullet = new Bullet;
                enemyBullet->loadTexture("img/enemyBullet1.png", screen);
                enemyBullet->setIsMove(true);
                enemyBullet->setPos(posX + (mTextureWidth - enemyBullet->getTextureWidth()) / 2,
                                    posY + mTextureHeight);
                enemyBullet->updateBoundingBox();
                enemyBullet->setYVel(2 * sin(angleBullet / 180 * PI));
                enemyBullet->setXVel(2 * cos(angleBullet / 180 * PI));
                enemyBulletList.push_back(enemyBullet);
            }
            lastTime = currentTime;
        }
    }
    else if (enemyType == 21 || enemyType == 22)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vector normVector(x - posX, y - posY);
        normVector.normalizeVector();
        int delayTime = 700;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            auto enemyBullet = new Bullet;
            enemyBullet->loadTexture("img/enemyBullet2.png", screen);
            enemyBullet->setIsMove(true);
            enemyBullet->setPos(posX + (mTextureWidth - enemyBullet->getTextureWidth()) / 2,
                                posY + mTextureHeight);
            enemyBullet->updateBoundingBox();
            enemyBullet->setYVel(2 * normVector.getY());
            enemyBullet->setXVel(2 * normVector.getX());
            enemyBulletList.push_back(enemyBullet);
            lastTime = currentTime;
        }
    }
    if (enemyType == 31 || enemyType == 32)
    {
        int delayTime = 500;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            int bulletNums = 25;
            for (int i = 0; i < bulletNums; i++)
            {
                angleBullet = 0 + 360 / (bulletNums - 1) * i;
                auto enemyBullet = new Bullet;
                enemyBullet->loadTexture("img/enemyBullet3.png", screen);
                enemyBullet->setIsMove(true);
                enemyBullet->setPos(posX + (mTextureWidth - enemyBullet->getTextureWidth()) / 2,
                                    posY + (mTextureHeight - enemyBullet->getTextureHeight()) / 2);
                enemyBullet->updateBoundingBox();
                enemyBullet->setYVel(2 * sin(angleBullet / 180 * PI));
                enemyBullet->setXVel(2 * cos(angleBullet / 180 * PI));
                enemyBulletList.push_back(enemyBullet);
            }
            lastTime = currentTime;
        }
    }
    if (enemyType == 41 || enemyType == 42)
    {
        int delayTime = 700;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            angleBullet = rand() % 60 + 40;
            for (int i = 0; i < 3; i++)
            {
                auto enemyBullet = new Bullet;
                enemyBullet->loadTexture("img/enemyBullet5.png", screen);
                enemyBullet->setIsMove(true);
                if (i == 0 || i == 2)
                {
                    enemyBullet->setPos(posX + mTextureWidth / 2 - 3 * enemyBullet->getTextureWidth() / 2 +
                                            i * enemyBullet->getTextureWidth(),
                                        posY + mTextureHeight);
                }
                else if (i == 1)
                {
                    enemyBullet->setPos(posX + mTextureWidth / 2 - 3 * enemyBullet->getTextureWidth() / 2 +
                                            i * enemyBullet->getTextureWidth(),
                                        posY + mTextureHeight + 2 * enemyBullet->getTextureWidth());
                }
                enemyBullet->updateBoundingBox();
                enemyBullet->setYVel(2 * sin(angleBullet / 180 * PI));
                enemyBullet->setXVel(2 * cos(angleBullet / 180 * PI));
                enemyBulletList.push_back(enemyBullet);
            }
            lastTime = currentTime;
        }
    }
    if (enemyType == 51 || enemyType == 52)
    {
        int delayTime = 100;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            for (int i = 0; i < 1; i++)
            {
                auto bullet = new Bullet;
                bullet->loadTexture("img/enemyBullet5.png", screen);
                bullet->setIsMove(true);
                bullet->setPos(posX + mTextureWidth / 2 - bullet->getTextureWidth() / 2,
                               posY + mTextureHeight / 2 - bullet->getTextureHeight() / 2);
                bullet->updateBoundingBox();
                bullet->setIsMove(true);
                bullet->setYVel(2 * sin(angleBullet / 180 * PI));
                bullet->setXVel(2 * cos(angleBullet / 180 * PI));
                enemyBulletList.push_back(bullet);
                angleBullet += 20;
            }
            lastTime = currentTime;
        }
    }
    else if (enemyType == 100 && canSpawnBullet)
    {
        spawnBossBullet(enemyBulletList, screen);
    }
}

void Enemy::move()
{
    if (enemyType % 10 == 1)
    {
        posX += velX;
        posY += velY;
        if (posX >= xLimit)
            posX = xLimit;
        if (posY >= yLimit)
            posY = yLimit;
        if (posX >= xLimit && posY >= yLimit)
        {
            canSpawnBullet = true;
            immortal = false;
        }
    }
    else if (enemyType % 10 == 2)
    {
        posX += velX;
        posY += velY;
        if (posX <= xLimit)
            posX = xLimit;
        if (posY <= yLimit)
            posY = yLimit;
        if (posX <= xLimit && posY <= yLimit)
        {
            canSpawnBullet = true;
            immortal = false;
        }
    }
    else if (enemyType == 100)
    {
        posY += velY;
        if (posY >= yLimit)
        {
            canSpawnBullet = true;
            immortal = false;
            posY = yLimit;
            moveAround();
        }
    }
    updateHitbox();
}

void Enemy::updateHitbox()
{
    hitBox.x = posX;
    hitBox.y = posY;
    hitBox.w = mTextureWidth;
    hitBox.h = mTextureHeight;
}

void Enemy::spawnBulletOnDie(std::vector<Bullet *> &enemyBulletList, SDL_Renderer *screen)
{
    int bulletNum = 10;
    int dAngle = 360 / (bulletNum - 1);
    for (int i = 0; i < bulletNum; i++)
    {
        angleBullet = dAngle * i;
        auto bullet = new Bullet;
        if (enemyType / 10 == 0)
        {
            bullet->loadTexture("img/enemyBullet0.png", screen);
        }
        else if (enemyType / 10 == 1)
        {
            bullet->loadTexture("img/enemyBullet1.png", screen);
        }
        else if (enemyType / 10 == 2)
        {
            bullet->loadTexture("img/enemyBullet2.png", screen);
        }
        else if (enemyType / 10 == 3)
        {
            bullet->loadTexture("img/enemyBullet3.png", screen);
        }
        else if (enemyType / 10 == 4 || enemyType / 10 == 5)
        {
            bullet->loadTexture("img/enemyBullet5.png", screen);
        }
        bullet->setIsMove(true);
        bullet->setPos(posX + (mTextureWidth - bullet->getTextureWidth()) / 2, posY + mTextureHeight);
        bullet->updateBoundingBox();
        bullet->setIsMove(true);
        bullet->setYVel(5 * sin(angleBullet));
        bullet->setXVel(5 * cos(angleBullet));
        enemyBulletList.push_back(bullet);
    }
}

void Enemy::spawnSupportItem(std::vector<SupportItem *> &itemList, SDL_Renderer *screen)
{
    int n = rand() % 10 + 1;
    if (n == 5)
    {
        auto item = new SupportItem;
        int type = rand() % 3;
        if (type == 0)
        {
            item->setType(HEALTH);
            item->loadTexture("img/Health_item.png", screen);
        }
        else if (type == 1)
        {
            item->setType(SHIELD);
            item->loadTexture("img/Shield_item.png", screen);
        }
        else
        {
            item->setType(BULLET);
            item->loadTexture("img/Bullet_item.png", screen);
        }
        item->setPos(posX + (mTextureWidth - item->getTextureWidth()) / 2,
                     posY + (mTextureHeight - item->getTextureHeight()) / 2);
        item->updateBoundingBox();
        item->setIsMove(true);
        item->setXVel(0);
        item->setYVel(1);
        itemList.push_back(item);
    }
}

void Enemy::spawnBossBullet(std::vector<Bullet *> &enemyBulletList, SDL_Renderer *screen)
{
    if (hp >= 400 && hp <= 500)
    {
        int delayTime = 500;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            int bulletNum = 24;
            for (int i = 0; i < bulletNum; i++)
            {
                angleBullet = 15 * i;
                auto bullet = new Bullet;
                bullet->loadTexture("img/enemyBullet5.png", screen);
                bullet->setIsMove(true);
                bullet->setPos(posX + (mTextureWidth - bullet->getTextureWidth()) / 2,
                               posY + (mTextureHeight - bullet->getTextureHeight()) / 2);
                bullet->updateBoundingBox();
                bullet->setYVel(2 * sin(angleBullet / 180 * PI));
                bullet->setXVel(1 * cos(angleBullet / 180 * PI));
                enemyBulletList.push_back(bullet);
            }
            for (int i = 0; i < bulletNum; i++)
            {
                angleBullet = 15 * i;
                auto bullet = new Bullet;
                bullet->loadTexture("img/enemyBullet2.png", screen);
                bullet->setIsMove(true);
                bullet->setPos(posX + (mTextureWidth - bullet->getTextureWidth()) / 2,
                               posY + (mTextureHeight - bullet->getTextureHeight()) / 2);
                bullet->updateBoundingBox();
                bullet->setYVel(1 * sin(angleBullet / 180 * PI));
                bullet->setXVel(2 * cos(angleBullet / 180 * PI));
                enemyBulletList.push_back(bullet);
            }
            lastTime = currentTime;
        }
    }
    else if (hp >= 300 && hp < 400)
    {
        int delayTime = 150;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            int bulletNum = 10;
            int disance = 130;
            for (int i = 0; i < bulletNum; i++)
            {
                auto bullet = new Bullet;
                bullet->loadTexture("img/enemyBullet1.png", screen);
                bullet->setPos(0, 50 + disance * i);
                bullet->setIsMove(true);
                bullet->updateBoundingBox();
                bullet->setXVel(2);
                bullet->setYVel(0);
                enemyBulletList.push_back(bullet);
            }
            for (int i = 0; i < bulletNum; i++)
            {
                auto bullet = new Bullet;
                bullet->loadTexture("img/enemyBullet1.png", screen);
                bullet->setPos(50 + disance * i, 0);
                bullet->setIsMove(true);
                bullet->updateBoundingBox();
                bullet->setXVel(0);
                bullet->setYVel(2);
                enemyBulletList.push_back(bullet);
            }
            lastTime = currentTime;
        }
    }
    else if (hp >= 200 && hp < 300)
    {
        int delayTime = 200;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            for (int i = 0; i < 4; i++)
            {
                auto bullet = new Bullet;
                bullet->loadTexture("img/enemyBullet0.png", screen);
                bullet->setType(SINE_TYPE);
                bullet->setIsMove(true);
                bullet->setPos(10 + 200 * i, -30);
                bullet->setStartPos(10 + 200 * i);
                bullet->updateBoundingBox();
                bullet->setYVel(1);
                enemyBulletList.push_back(bullet);
            }
            lastTime = currentTime;
        }
    }
    else if (hp >= 100 && hp < 200)
    {
        int bulletNum = 20;
        int dAngle = 360 / (bulletNum - 1);
        int delayTime = 400;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            for (int i = 0; i < bulletNum; i++)
            {
                angleBullet = dAngle * i;
                auto bullet = new Bullet;
                bullet->loadTexture("img/enemyBullet3.png", screen);
                bullet->setIsMove(true);
                bullet->setPos(posX + (mTextureWidth - bullet->getTextureWidth()) / 2,
                               posY + (mTextureHeight - bullet->getTextureHeight()) / 2);
                bullet->updateBoundingBox();
                double velocity = 2;
                bullet->setYVel(velocity * sin(angleBullet / 180 * PI));
                bullet->setXVel(velocity * cos(angleBullet / 180 * PI));
                enemyBulletList.push_back(bullet);
            }
            lastTime = currentTime;
        }
    }
    else if (hp < 100)
    {
        double angleSpeed = 10;
        int delayTime = 150;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= delayTime && canSpawnBullet)
        {
            for (int i = 0; i < 10; i++)
            {
                auto bullet = new Bullet;
                bullet->loadTexture("img/enemyBullet5.png", screen);
                bullet->setIsMove(true);
                bullet->setPos(posX + (mTextureWidth - bullet->getTextureWidth()) / 2,
                               posY + (mTextureHeight - bullet->getTextureHeight()) / 2);
                bullet->updateBoundingBox();
                double velocity = 2;
                bullet->setYVel(velocity * sin((angleBullet + 36 * i) / 180 * PI));
                bullet->setXVel(velocity * cos((angleBullet + 36 * i) / 180 * PI));
                enemyBulletList.push_back(bullet);
                angleBullet += angleSpeed;
                if (angleBullet >= 360)
                {
                    angleBullet -= 360;
                }
            }
            lastTime = currentTime;
        }
        srand(SDL_GetTicks());
        int spawnMore = rand() % 500;
        if (spawnMore == 5)
        {
            auto missile = new Bullet;
            missile->loadTexture("img/missile.png", screen);
            missile->updateBoundingBox();
            float randomX = rand() % SCREEN_WIDTH;
            missile->setPos(randomX, -100);
            missile->setYVel(10);
            missile->setXVel(0);
            enemyBulletList.push_back(missile);
        }
    }
}

void Enemy::moveAround()
{
    float range = SCREEN_WIDTH - 200 - mTextureWidth;
    posX = (100 + range / 2) + range / 2 * cos(angleMove / 180 * PI);
    angleMove += 1;
    if (angleMove >= 360)
        angleMove = 0;
    updateHitbox();
}