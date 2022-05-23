//
// Created by Quyen on 5/19/2022.
//

#include "EnemyWave.h"

void spawnEnemy(std::vector<Enemy *> &enemyWave, SDL_Renderer *screen, int &wave, int &previousWave)
{
    if (enemyWave.empty())
    {
        wave += 1;
        if (wave % 10 != 0)
        {
            srand(SDL_GetTicks());
            int randomwave = rand() % 9 + 1;
            if (randomwave == previousWave)
            {
                randomwave = (randomwave + 1) % 9;
            }
            if (randomwave % 10 == 1)
            {
                generateArray0(enemyWave, screen);
            }
            else if (randomwave % 10 == 2)
            {
                generateArray1(enemyWave, screen);
            }
            else if (randomwave % 10 == 3)
            {
                generateArray2(enemyWave, screen);
            }
            else if (randomwave == 4)
            {
                generateArray3(enemyWave, screen);
            }
            else if (randomwave == 5)
            {
                generateArray4(enemyWave, screen);
            }
            else if (randomwave == 6)
            {
                generateArray5(enemyWave, screen);
            }
            else if (randomwave == 7)
            {
                generateArray6(enemyWave, screen);
            }
            else if (randomwave == 8)
            {
                generateArray7(enemyWave, screen);
            }
            else if (randomwave == 9)
            {
                generateArray8(enemyWave, screen);
            }
            previousWave = randomwave;
        }
        else
        {
            generateBoss(enemyWave, screen);
        }
    }
}

void generateArray0(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    for (int i = 0; i < 3; i++)
    {
        Enemy *enemyRow1 = new Enemy;
        enemyRow1->setType(01);
        enemyRow1->setPoint(10);
        enemyRow1->loadTexture("img/enemy0.png", screen);
        enemyRow1->setPos(SCREEN_WIDTH / 2 - enemyRow1->getTextureWidth() / 2 +
                              (enemyRow1->getTextureWidth() + 10) * (i - 1),
                          -300);
        enemyRow1->updateHitbox();
        enemyRow1->setXLim(enemyRow1->getPosX());
        enemyRow1->setVelX(0);
        enemyRow1->setYLim(70);
        enemyRow1->setVelY(5);
        enemyRow1->setHP(5);
        enemyList.push_back(enemyRow1);
    }
    for (int i = 0; i < 2; i++)
    {
        Enemy *enemyRow2 = new Enemy;
        enemyRow2->setType(01);
        enemyRow2->setPoint(10);
        enemyRow2->loadTexture("img/enemy0.png", screen);
        enemyRow2->setPos(
            SCREEN_WIDTH / 2 - 5 - enemyRow2->getTextureWidth() + (enemyRow2->getTextureWidth() + 10) * i, -200);
        enemyRow2->updateHitbox();
        enemyRow2->setXLim(enemyRow2->getPosX());
        enemyRow2->setVelX(0);
        enemyRow2->setYLim(enemyRow2->getTextureHeight() + 5 + 70);
        enemyRow2->setVelY(5);
        enemyRow2->setHP(5);
        enemyList.push_back(enemyRow2);
    }
    for (int i = 0; i < 1; i++)
    {
        Enemy *enemyRow3 = new Enemy;
        enemyRow3->setType(01);
        enemyRow3->setPoint(10);
        enemyRow3->loadTexture("img/enemy0.png", screen);
        enemyRow3->setPos(SCREEN_WIDTH / 2 - enemyRow3->getTextureWidth() / 2 +
                              (enemyRow3->getTextureWidth() + 10) * (i),
                          -100);
        enemyRow3->updateHitbox();
        enemyRow3->setXLim(enemyRow3->getPosX());
        enemyRow3->setVelX(0);
        enemyRow3->setYLim(enemyRow3->getTextureHeight() + 5 + 111);
        enemyRow3->setVelY(5);
        enemyRow3->setHP(5);
        enemyList.push_back(enemyRow3);
    }
}

void generateArray1(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    int enemyNum = 4;
    for (int i = 0; i < enemyNum; i++)
    {
        Enemy *enemyRow1 = new Enemy;
        enemyRow1->setType(11);
        enemyRow1->setPoint(20);
        enemyRow1->loadTexture("img/enemy1.png", screen);
        enemyRow1->setPos(SCREEN_WIDTH / 2 - (enemyRow1->getTextureWidth() * enemyNum + 10 * (enemyNum - 1)) / 2 +
                              i * (enemyRow1->getTextureWidth() + 10),
                          -80 - 20 * i);
        enemyRow1->updateHitbox();
        enemyRow1->setVelX(0);
        enemyRow1->setXLim(enemyRow1->getPosX());
        enemyRow1->setVelY(5);
        enemyRow1->setYLim(70);
        enemyRow1->setHP(5);
        enemyList.push_back(enemyRow1);
    }

    for (int i = 0; i < enemyNum; i++)
    {
        Enemy *enemyRow2 = new Enemy;
        enemyRow2->setType(11);
        enemyRow2->setPoint(20);
        enemyRow2->loadTexture("img/enemy1.png", screen);
        enemyRow2->setPos(SCREEN_WIDTH / 2 - (enemyRow2->getTextureWidth() * enemyNum + 10 * (enemyNum - 1)) / 2 +
                              i * (enemyRow2->getTextureWidth() + 10),
                          -80 - 20 * i);
        enemyRow2->updateHitbox();
        enemyRow2->setVelX(0);
        enemyRow2->setXLim(enemyRow2->getPosX());
        enemyRow2->setVelY(5);
        enemyRow2->setYLim(70 + enemyRow2->getTextureHeight() + 10);
        enemyRow2->setHP(5);
        enemyList.push_back(enemyRow2);
    }
}

void generateArray2(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    for (int i = 0; i < 2; i++)
    {
        Enemy *enemyColumn1 = new Enemy;
        enemyColumn1->setType(21);
        enemyColumn1->setPoint(30);
        enemyColumn1->loadTexture("img/enemy2.png", screen);
        enemyColumn1->setPos(-enemyColumn1->getTextureWidth(), 70 + i * 80);
        enemyColumn1->updateHitbox();
        enemyColumn1->setYLim(enemyColumn1->getPosY());
        enemyColumn1->setVelY(0);
        enemyColumn1->setVelX(3);
        enemyColumn1->setXLim(100);
        enemyColumn1->setHP(5);
        enemyList.push_back(enemyColumn1);
    }

    for (int i = 0; i < 2; i++)
    {
        Enemy *enemyColumn2 = new Enemy;
        enemyColumn2->setType(22);
        enemyColumn2->setPoint(30);
        enemyColumn2->loadTexture("img/enemy2.png", screen);
        enemyColumn2->setPos(SCREEN_WIDTH, 70 + i * 80);
        enemyColumn2->updateHitbox();
        enemyColumn2->setXLim(SCREEN_WIDTH - 100 - enemyColumn2->getTextureWidth());
        enemyColumn2->setYLim(70 + i * 80);
        enemyColumn2->setVelX(-3);
        enemyColumn2->setVelY(0);
        enemyColumn2->setHP(5);
        enemyList.push_back(enemyColumn2);
    }
}

void generateArray3(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    for (int i = 0; i < 2; i++)
    {
        auto enemy = new Enemy;
        enemy->setType(31);
        enemy->setPoint(40);
        enemy->loadTexture("img/enemy3.png", screen);
        enemy->setPos(-enemy->getTextureWidth() - 100, -enemy->getTextureHeight() - 100);
        enemy->updateHitbox();
        enemy->setYLim(enemy->getTextureHeight() + 50);
        enemy->setXLim(
            SCREEN_WIDTH / 2 - 1 * (enemy->getTextureWidth() + 150) / 2 + i * (enemy->getTextureWidth() + 150));
        enemy->setVelX(3 + i);
        enemy->setVelY(3 + i);
        enemy->setHP(5);
        enemyList.push_back(enemy);
    }
}

void generateArray4(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    for (int i = 0; i < 9; i++)
    {
        int row = i / 3;
        int column = i % 3;
        auto enemy = new Enemy;
        enemy->setType(41);
        enemy->setPoint(50);
        enemy->loadTexture("img/enemy4.png", screen);
        enemy->setPos(-enemy->getTextureWidth() - 100, -enemy->getTextureHeight() - 100);
        enemy->updateHitbox();
        enemy->setYLim(70 + (enemy->getTextureHeight() + 20) * row);
        enemy->setXLim(SCREEN_WIDTH / 2 - 3 * (enemy->getTextureWidth() + 5) / 2 +
                       column * (enemy->getTextureWidth() + 20));
        enemy->setVelX(2 + column);
        enemy->setVelY(2 + row);
        enemy->setHP(5);
        enemyList.push_back(enemy);
    }
}

void generateArray5(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    for (int i = 0; i < 2; i++)
    {
        auto enemy = new Enemy;
        enemy->setType(52);
        enemy->setPoint(60);
        enemy->loadTexture("img/enemy5.png", screen);
        enemy->setPos(30, SCREEN_HEIGHT + enemy->getTextureHeight());
        enemy->updateHitbox();
        enemy->setXLim(100);
        enemy->setYLim(70 + (enemy->getTextureHeight() + 30) * i);
        enemy->setVelX(0);
        enemy->setVelY(-4 + i);
        enemy->setHP(5);
        enemyList.push_back(enemy);
    }
    for (int i = 0; i < 2; i++)
    {
        auto enemy = new Enemy;
        enemy->setType(52);
        enemy->setPoint(60);
        enemy->loadTexture("img/enemy5.png", screen);
        enemy->setPos(SCREEN_WIDTH - enemy->getTextureWidth() - 100, SCREEN_HEIGHT + enemy->getTextureHeight());
        enemy->updateHitbox();
        enemy->setXLim(SCREEN_WIDTH - enemy->getTextureWidth() - 100);
        enemy->setYLim(70 + (enemy->getTextureHeight() + 30) * i);
        enemy->setVelX(0);
        enemy->setVelY(-4 + i);
        enemy->setHP(5);
        enemyList.push_back(enemy);
    }
}

void generateArray6(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    generateArray2(enemyList, screen);
    Enemy *enemy = new Enemy;
    enemy->setType(31);
    enemy->setPoint(40);
    enemy->loadTexture("img/enemy3.png", screen);
    enemy->setPos(-enemy->getTextureWidth() - 100, -enemy->getTextureHeight() - 100);
    enemy->updateHitbox();
    enemy->setYLim(enemy->getTextureHeight() + 50);
    enemy->setXLim(SCREEN_WIDTH / 2 - (enemy->getTextureWidth()) / 2);
    enemy->setVelX(3);
    enemy->setVelY(3);
    enemy->setHP(5);
    enemyList.push_back(enemy);
}

void generateArray7(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    generateArray0(enemyList, screen);
    Enemy *enemy = new Enemy;
    enemy->setType(31);
    enemy->setPoint(40);
    enemy->loadTexture("img/enemy3.png", screen);
    enemy->setPos(-enemy->getTextureWidth() - 100, -enemy->getTextureHeight() - 100);
    enemy->updateHitbox();
    enemy->setYLim(SCREEN_HEIGHT / 2 - enemy->getTextureHeight() / 2);
    enemy->setXLim(SCREEN_WIDTH / 2 - enemy->getTextureWidth() / 2);
    enemy->setVelX(3);
    enemy->setVelY(3);
    enemy->setHP(5);
    enemyList.push_back(enemy);
}

void generateArray8(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    generateArray1(enemyList, screen);
    generateArray2(enemyList, screen);
}

void generateBoss(std::vector<Enemy *> &enemyList, SDL_Renderer *screen)
{
    Enemy *boss = new Enemy;
    boss->setType(100);
    boss->setPoint(1000);
    boss->loadTexture("img/Boss.png", screen);
    boss->setPos(SCREEN_WIDTH / 2 - boss->getTextureWidth() / 2, -1000);
    float range = SCREEN_WIDTH - 200 - boss->getTextureWidth();
    boss->setAngleMove(acos((boss->getPosX() - 100 - range / 2) / (range / 2)) * 180 / PI);
    boss->updateHitbox();
    boss->setYLim(30);
    boss->setVelX(3);
    boss->setVelY(5);
    boss->setHP(500);
    enemyList.push_back(boss);
}
