//
// Created by Quyen on 5/18/2022.
//

#ifndef SPACESHOOTER_OBJECTHANDLER_H
#define SPACESHOOTER_OBJECTHANDLER_H

#include "EnemyWave.h"

void handleEnemy( std::vector<Enemy *> &enemyWave, Character &player, std::vector<Bullet *> &enemyBulletList,
                  std::vector<SupportItem *> &itemList,
                  SDL_Renderer *screen, unsigned long long int &point, Mix_Chunk *spawnBulletOnDie );

void handleEnemyBullet( SDL_Renderer *des, std::vector<Bullet *> &enemyBulletList );

void handleCharacter( Character &player, std::vector<Bullet *> &enemyBulletList,
                      std::vector<Enemy *> &enemyWave, std::vector<SupportItem *> &itemList,
                      SDL_Renderer *screen, Mix_Chunk *hitted, Mix_Chunk *powerUp, Mix_Chunk *shoot, int &frame );


void handleItem( std::vector<SupportItem *> &itemList, SDL_Renderer *screen );


#endif //SPACESHOOTER_OBJECTHANDLER_H
