//
// Created by Quyen on 5/20/2022.
//

#include "ObjectHandler.h"

void handleEnemy(std::vector<Enemy *> &enemyWave, Character &player, std::vector<Bullet *> &enemyBulletList,
                 std::vector<SupportItem *> &itemList,
                 SDL_Renderer *screen, unsigned long long int &point, Mix_Chunk *spawnBulletOnDie)
{
    std::vector<Bullet *> characterBullets = player.getBulletList();
    for (int i = 0; i < characterBullets.size(); i++)
    {
        auto bullet = characterBullets[i];

        for (int j = 0; j < enemyWave.size(); j++)
        {
            auto enemy = enemyWave[j];
            SDL_FRect enemyRect = enemy->getHitBox();
            SDL_FRect bulletRect = bullet->getBoudingBox();
            if (checkCollision(enemyRect, bulletRect))
            {
                bullet->setIsMove(false);
                if (!enemy->checkImmortal())
                {
                    enemy->decreaseHP();
                    if (enemy->getHP() <= 0)
                    {
                        if (enemy->getEnemyType() != 100)
                        {
                            enemy->spawnBulletOnDie(enemyBulletList, screen);
                        }
                        Mix_PlayChannel(4, spawnBulletOnDie, 0);
                        enemy->spawnSupportItem(itemList, screen);
                        point += enemy->getPoint();
                        enemyWave.erase(enemyWave.begin() + j);
                        if (enemy != nullptr)
                        {
                            delete enemy;
                            enemy = nullptr;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < enemyWave.size(); i++)
    {
        enemyWave[i]->move();
    }
    for (int i = 0; i < enemyWave.size(); i++)
    {
        enemyWave[i]->spawnBullet(screen, enemyBulletList, player);
        enemyWave[i]->render(screen);
    }
}

void handleEnemyBullet(SDL_Renderer *des, std::vector<Bullet *> &enemyBulletList)
{
    for (int i = 0; i < enemyBulletList.size(); i++)
    {
        Bullet *bullet = enemyBulletList[i];
        if (!bullet->getIsMove())
        {
            enemyBulletList.erase(enemyBulletList.begin() + i);
            if (bullet != nullptr)
            {
                delete bullet;
                bullet = nullptr;
            }
        }
        else
        {
            bullet->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            bullet->render(des);
        }
    }
}

void handleCharacter(Character &player, std::vector<Bullet *> &enemyBulletList,
                     std::vector<Enemy *> &enemyWave, std::vector<SupportItem *> &itemList,
                     SDL_Renderer *screen, Mix_Chunk *hitted, Mix_Chunk *powerUp, Mix_Chunk *shoot, int &frame)
{
    if (!player.getDead())
    {
        player.loadCharacter(screen);
        player.spawnBullet(screen, shoot);
        player.handleBullet(screen);
    }
    if (!player.getHaveShield())
    {
        for (int i = 0; i < enemyBulletList.size(); i++)
        {
            if (checkCollision(player.getHitBox(), enemyBulletList[i]->getBoudingBox()))
            {
                enemyBulletList[i]->setIsMove(false);
                player.decreaseHP();
                player.decreaseBulletLevel();
                Mix_PlayChannel(2, hitted, 0);
                if (player.getHP() <= 0)
                {
                    player.setDead(true);
                }
                else
                {
                    player.setHaveShield(true);
                    player.setShieldTime(SDL_GetTicks());
                }
                break;
            }
        }
        for (int i = 0; i < enemyWave.size(); i++)
        {
            if (checkCollision(player.getHitBox(), enemyWave[i]->getHitBox()))
            {
                if (!enemyWave[i]->checkImmortal())
                {
                    for (int j = 0; j < 10; j++)
                        enemyWave[i]->decreaseHP();
                }
                player.setDead(true);
            }
        }
    }
    else
    {
        for (int i = 0; i < enemyBulletList.size(); i++)
        {
            if (checkCollision(player.getHitBox(), enemyBulletList[i]->getBoudingBox()))
            {
                enemyBulletList[i]->setIsMove(false);
            }
        }
        for (int i = 0; i < enemyWave.size(); i++)
        {
            if (checkCollision(player.getHitBox(), enemyWave[i]->getHitBox()))
            {
                for (int j = 0; j < 10; j++)
                {
                    enemyWave[i]->decreaseHP();
                }
            }
        }
    }

    for (int i = 0; i < itemList.size(); i++)
    {
        if (checkCollision(player.getHitBox(), itemList[i]->getBoundingBox()))
        {
            Mix_PlayChannel(3, powerUp, 0);
            itemList[i]->setIsMove(false);
            player.powerUp(itemList[i]);
        }
    }
    player.render(screen, frame);
}

void handleItem(std::vector<SupportItem *> &itemList, SDL_Renderer *screen)
{
    for (int i = 0; i < itemList.size(); i++)
    {
        itemList[i]->move();
        auto item = itemList[i];
        if (!item->getIsMove())
        {
            itemList.erase(itemList.begin() + i);
            if (item != nullptr)
            {
                delete item;
                item = nullptr;
            }
        }
    }
    for (int i = 0; i < itemList.size(); i++)
    {
        itemList[i]->render(screen);
    }
}