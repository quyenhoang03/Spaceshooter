//
// Created by Quyen on 4/25/2022.
//

#ifndef SPACESHOOTER_ENEMYWAVE_H
#define SPACESHOOTER_ENEMYWAVE_H

#include "Enemy.h"
#include <vector>
#include "Collision.h"
#include "Character.h"

void generateArray0(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void generateArray1(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void generateArray2(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void generateArray3(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void generateArray4(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void generateArray5(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void generateArray6(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void generateArray7(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void generateArray8(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void generateBoss(std::vector<Enemy *> &enemyList, SDL_Renderer *screen);

void spawnEnemy(std::vector<Enemy *> &enemyWave, SDL_Renderer *screen, int &wave, int &previousWave);

#endif // SPACESHOOTER_ENEMYWAVE_H
