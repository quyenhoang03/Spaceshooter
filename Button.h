//
// Created by Quyen on 5/18/2022.
//

#ifndef SPACESHOOTER_BUTTON_H
#define SPACESHOOTER_BUTTON_H

#include "Common.h"
#include "TextObject.h"
#include "EnemyWave.h"
#include <vector>

using namespace std;

#define WHITE {255, 255, 255}
#define BLUE {0,128,255}

class Button : public TextObject
{
private:
    float posX;
    float posY;
public:
    Button()
    {
        posX = 0;
        posY = 0;
    }

    void setPos( const float &x, const float &y )
    {
        posX = x;
        posY = y;
    }

    float getPosX() const
    { return posX; }


    float getPosY() const
    { return posY; }

    bool checkMouseInside( SDL_Event &event );

    void handlePlayButton( SDL_Event &event, SDL_Renderer *screen, bool &menu, bool &play, TTF_Font *font );

    void handleHelpButton( SDL_Event &event, SDL_Renderer *screen, bool &menu, bool &help, TTF_Font *font );

    void handleExitButton( SDL_Event &event, SDL_Renderer *screen, bool &menu, TTF_Font *font );

    void handleBackButton( SDL_Event &event, SDL_Renderer *screen, bool &menu, bool &help, TTF_Font *font );

    void handleRestartButton( SDL_Event event, SDL_Renderer *screen, vector<Enemy *> &enemyList,
                              Character &spaceship, vector<Bullet *> &bulletList,
                              vector<SupportItem *> &itemList, int &wave, int &previousWave, unsigned long long &score,
                              bool &gameOver, SDL_Window *gWindow, TTF_Font *font );

    void render( SDL_Renderer *screen );
};

#endif //SPACESHOOTER_BUTTON_H
