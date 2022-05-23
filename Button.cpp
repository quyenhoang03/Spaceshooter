//
// Created by Quyen on 5/18/2022.
//

#include "Button.h"

bool Button::checkMouseInside( SDL_Event &event )
{
    if ( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
    {
        int x = event.motion.x;
        int y = event.motion.y;
        if ( posX >= x || posX + mTextureWidth <= x || posY >= y || posY + mTextureHeight <= y )
        {
            false;
        }
        else return true;
    }
    return false;
}

void Button::handlePlayButton( SDL_Event &event, SDL_Renderer *screen, bool &menu, bool &play, TTF_Font *font )
{
    if ( checkMouseInside(event))
    {
        textColor = BLUE;
        createTexture(font, screen);
        if ( event.type == SDL_MOUSEBUTTONDOWN )
        {
            play = true;
            menu = false;
        }
    }
    else
    {
        textColor = WHITE;
        createTexture(font, screen);
    }
}

void Button::handleHelpButton( SDL_Event &event, SDL_Renderer *screen, bool &menu, bool &help, TTF_Font *font )
{
    if ( checkMouseInside(event))
    {
        textColor = BLUE;
        createTexture(font, screen);
        if ( event.type == SDL_MOUSEBUTTONDOWN )
        {
            help = true;
        }
    }
    else
    {
        textColor = WHITE;
        createTexture(font, screen);
    }
}

void Button::handleExitButton( SDL_Event &event, SDL_Renderer *screen, bool &menu, TTF_Font *font )
{
    if ( checkMouseInside(event))
    {
        textColor = BLUE;
        createTexture(font, screen);
        if ( event.type == SDL_MOUSEBUTTONDOWN )
        {
            menu = false;
        }
    }
    else
    {
        textColor = WHITE;
        createTexture(font, screen);
    }
}

void Button::handleBackButton( SDL_Event &event, SDL_Renderer *screen, bool &menu, bool &help, TTF_Font *font )
{
    if ( checkMouseInside(event))
    {
        textColor = BLUE;
        createTexture(font, screen);
        if ( event.type == SDL_MOUSEBUTTONDOWN )
        {
            menu = true;
            help = false;
        }
    }
    else
    {
        textColor = WHITE;
        createTexture(font, screen);
    }
}

void Button::handleRestartButton( SDL_Event event, SDL_Renderer *screen, vector<Enemy *> &enemyList,
                                  Character &spaceship, vector<Bullet *> &bulletList, vector<SupportItem *> &itemList,
                                  int &wave, int &previousWave, unsigned long long &score, bool &gameOver,
                                  SDL_Window *gWindow,
                                  TTF_Font *font )
{
    if ( checkMouseInside(event))
    {
        textColor = BLUE;
        createTexture(font, screen);
        if ( event.type == SDL_MOUSEBUTTONDOWN )
        {
            gameOver = false;
            score = 0;
            wave = 0;
            previousWave = -1;
            enemyList.clear();
            bulletList.clear();
            itemList.clear();
            spaceship.reset();
            SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH / 2 - spaceship.getTextureWidth() / 2, posY - 100);
            Mix_HaltMusic();
        }
    }
    else
    {
        textColor = WHITE;
        createTexture(font, screen);
    }
}

void Button::render( SDL_Renderer *screen )
{
    SDL_FRect quad = { posX, posY, mTextureWidth, mTextureHeight };
    SDL_RenderCopyF(screen, mTexture, nullptr, &quad);
}



