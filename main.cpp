#include <iostream>
#include "Common.h"
#include "Enemy.h"
#include "Character.h"
#include "TextObject.h"
#include "Button.h"
#include "ObjectHandler.h"

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
SDL_Event e;

Texture gameOverBackground;
Texture menuBackground;
Texture helpBackground;
Texture pauseBackground;
Texture background;

TTF_Font *font = nullptr;

Button playButton;
Button helpButton;
Button exitButton;
Button restartButton;
Button backButton;

Mix_Music *menuMusic = nullptr;
Mix_Music *playing = nullptr;
Mix_Chunk *shoot = nullptr;
Mix_Chunk *powerUp = nullptr;
Mix_Chunk *hitted = nullptr;
Mix_Chunk *spawnBulletOnDie = nullptr;

TextObject shieldRemainTime;
TextObject shieldRemainTimeValue;
TextObject health;
TextObject score;
TextObject scoreValue;
TextObject highscore;
TextObject highscoreValue;
TextObject waveText;
TextObject waveValue;

SupportItem healthList[3];

Character player;

bool init();

void prepareGameMaterial();

void cleanup();

int main( int argc, char *argv[] )
{
    if ( !init())
    {
        std::cout << "Failed to initialize \n";
    }
    prepareGameMaterial();
    int scroll = 0;
    int frame = 0;
    int wave = 0;
    int previousWave = -1;
    unsigned long long int point{ 0 };

    std::vector<Enemy *> enemyWave;
    std::vector<Bullet *> enemyBulletList;
    std::vector<SupportItem *> itemList;

    bool play = false;
    bool menu = true;
    bool help = false;
    while ( menu )
    {
        if ( Mix_PlayingMusic() == 0 )
        {
            Mix_PlayMusic(menuMusic, -1);
        }
        if ( !help )
        {
            menuBackground.renderFullScreen(gRenderer);
            playButton.setPos((float)SCREEN_WIDTH / 2 - playButton.getTextureWidth() / 2,
                              (float)SCREEN_HEIGHT / 2 + 10);
            helpButton.setPos((float)SCREEN_WIDTH / 2 - playButton.getTextureWidth() / 2,
                              (float)SCREEN_HEIGHT / 2 + 110);
            exitButton.setPos((float)SCREEN_WIDTH / 2 - playButton.getTextureWidth() / 2,
                              (float)SCREEN_HEIGHT / 2 + 210);
            while ( SDL_PollEvent(&e) != 0 )
            {
                if ( e.type == SDL_QUIT )
                {
                    menu = false;
                }
                playButton.handlePlayButton(e, gRenderer, menu, play, font);
                helpButton.handleHelpButton(e, gRenderer, menu, help, font);
                exitButton.handleExitButton(e, gRenderer, menu, font);
            }
            playButton.render(gRenderer);
            helpButton.render(gRenderer);
            exitButton.render(gRenderer);
            SDL_RenderPresent(gRenderer);
        }
        else
        {
            helpBackground.renderFullScreen(gRenderer);
            backButton.setPos(30, SCREEN_HEIGHT - backButton.getTextureHeight() - 30);
            playButton.setPos(SCREEN_WIDTH - playButton.getTextureWidth() - 30,
                              SCREEN_HEIGHT - playButton.getTextureHeight() - 30);
            while ( SDL_PollEvent(&e) != 0 )
            {
                if ( e.type == SDL_QUIT )
                {
                    menu = false;
                }
                playButton.handlePlayButton(e, gRenderer, menu, play, font);
                backButton.handleBackButton(e, gRenderer, menu, help, font);
            }
            backButton.render(gRenderer);
            playButton.render(gRenderer);
            SDL_RenderPresent(gRenderer);
        }
    }
    Mix_HaltMusic();
    bool paused = false;
    bool gameOver = false;
    while ( play )
    {
        if ( Mix_PlayingMusic() == 0 )
        {
            Mix_PlayMusic(playing, -1);
        }
        unsigned long long startTime = SDL_GetTicks();
        if ( !gameOver )
        {
            if ( !paused )
            {
                SDL_ShowCursor(SDL_DISABLE);
                while ( SDL_PollEvent(&e) != 0 )
                {
                    if ( e.type == SDL_QUIT )
                    {
                        play = false;
                    }
                    if ( e.type == SDL_WINDOWEVENT )
                    {
                        if ( e.window.event == SDL_WINDOWEVENT_MINIMIZED )
                        {
                            paused = true;
                        }
                    }
                    if ( e.type == SDL_KEYDOWN )
                    {
                        if ( e.key.keysym.sym == SDLK_p )
                        {
                            paused = true;
                            SDL_WarpMouseInWindow(gWindow, player.getPosX() + player.getTextureWidth() / 2,
                                                  player.getPosY() + player.getTextureHeight() / 2);
                        }
                        if ( e.key.keysym.sym == SDLK_ESCAPE )
                        {
                            play = false;
                        }
                    }
                    player.handleInputAction(e);
                }
                SDL_RenderClear(gRenderer);
                background.scrollTexture(scroll, gRenderer);
                spawnEnemy(enemyWave, gRenderer, wave, previousWave);
                if ( !player.getDead())
                {
                    handleCharacter(player, enemyBulletList, enemyWave, itemList, gRenderer, hitted, powerUp, shoot,
                                    frame);
                }
                else
                {
                    gameOver = true;
                }
                handleEnemy(enemyWave, player, enemyBulletList, itemList, gRenderer, point, spawnBulletOnDie);
                handleEnemyBullet(gRenderer, enemyBulletList);
                handleItem(itemList, gRenderer);
                for ( int i = 0; i < player.getHP(); i++ )
                {
                    healthList[i].render(gRenderer);
                }
                std::string scoreText = std::to_string(point);
                scoreValue.setContent(scoreText);
                scoreValue.createTexture(font, gRenderer);
                scoreValue.renderText(gRenderer, SCREEN_WIDTH - scoreValue.getTextureWidth(),
                                      score.getTextureHeight());
                score.renderText(gRenderer, SCREEN_WIDTH - score.getTextureWidth(), 0);
                health.renderText(gRenderer, 0, 0);
                waveText.renderText(gRenderer, 30,
                                    SCREEN_HEIGHT - waveText.getTextureHeight() - 30);
                waveValue.setContent(std::to_string(wave));
                waveValue.createTexture(font, gRenderer);
                waveValue.renderText(gRenderer, 30 + waveText.getTextureWidth() + 5,
                                     SCREEN_HEIGHT - waveValue.getTextureHeight() - 30);
                if ( player.getHaveShield())
                {
                    Uint32 remainTime = 7 - ( SDL_GetTicks() - player.getShieldTime()) / 1000;
                    shieldRemainTimeValue.setContent(std::to_string(remainTime));
                    shieldRemainTimeValue.createTexture(font, gRenderer);
                    shieldRemainTime.renderText(gRenderer,
                                                (float)SCREEN_WIDTH / 2 - shieldRemainTime.getTextureWidth() / 2,
                                                0);
                    shieldRemainTimeValue.renderText(gRenderer,
                                                     (float)SCREEN_WIDTH / 2 -
                                                     shieldRemainTimeValue.getTextureWidth() / 2,
                                                     (float)shieldRemainTime.getTextureHeight());
                }
                SDL_RenderPresent(gRenderer);
            }
            else if ( paused )
            {
                SDL_ShowCursor(SDL_ENABLE);
                pauseBackground.renderFullScreen(gRenderer);
                restartButton.setPos((float)SCREEN_WIDTH / 2 - restartButton.getTextureWidth() / 2,
                                     (float)SCREEN_HEIGHT / 2);
                exitButton.setPos((float)SCREEN_WIDTH / 2 - exitButton.getTextureWidth() / 2,
                                  (float)SCREEN_HEIGHT / 2 + 100);
                while ( SDL_PollEvent(&e) != 0 )
                {
                    if ( e.type == SDL_QUIT )
                    {
                        play = false;
                    }
                    if ( e.type == SDL_KEYDOWN )
                    {
                        if ( e.key.keysym.sym == SDLK_p )
                        {
                            paused = false;
                            SDL_WarpMouseInWindow(gWindow, player.getPosX() + player.getTextureWidth() / 2,
                                                  player.getPosY() + player.getTextureHeight() / 2);
                        }
                        if ( e.key.keysym.sym == SDLK_ESCAPE )
                        {
                            play = false;
                        }
                    }
                    restartButton.handleRestartButton(e, gRenderer, enemyWave, player, enemyBulletList, itemList, wave,
                                                      previousWave, point, paused, gWindow, font);
                    exitButton.handleExitButton(e, gRenderer, play, font);
                }

                restartButton.render(gRenderer);
                exitButton.render(gRenderer);
                SDL_RenderPresent(gRenderer);
            }
        }
        else
        {
            updateHighscore("highscore.txt", point);
            SDL_ShowCursor(SDL_ENABLE);
            gameOverBackground.renderFullScreen(gRenderer);
            restartButton.setPos(30, SCREEN_HEIGHT - restartButton.getTextureHeight() - 30);
            exitButton.setPos(SCREEN_WIDTH - exitButton.getTextureWidth() - 30,
                              SCREEN_HEIGHT - exitButton.getTextureHeight() - 30);

            highscoreValue.setContent(getHighscoreFromFile("highscore.txt"));
            highscoreValue.setColor(WHITE_TEXT);
            highscoreValue.createTexture(font, gRenderer);
            while ( SDL_PollEvent(&e) != 0 )
            {
                if ( e.type == SDL_QUIT )
                {
                    play = false;
                }
                restartButton.handleRestartButton(e, gRenderer, enemyWave, player, enemyBulletList, itemList, wave,
                                                  previousWave, point, gameOver, gWindow, font);
                exitButton.handleExitButton(e, gRenderer, play, font);
            }
            score.renderText(gRenderer, 100, (float)SCREEN_HEIGHT / 2);
            scoreValue.renderText(gRenderer, highscore.getTextureWidth() + 200, (float)SCREEN_HEIGHT / 2);
            highscore.renderText(gRenderer, 100, (float)SCREEN_HEIGHT / 2 + 100);
            highscoreValue.renderText(gRenderer, highscore.getTextureWidth() + 200, (float)SCREEN_HEIGHT / 2 + 100);
            restartButton.render(gRenderer);
            exitButton.render(gRenderer);
            SDL_RenderPresent(gRenderer);
        }
        unsigned long long passedTime = SDL_GetTicks() - startTime;
        if ( passedTime < 1000 / FPS )
        {
            SDL_Delay(1000 / FPS - passedTime);
        }
    }
    itemList.clear();
    enemyWave.clear();
    enemyBulletList.clear();
    cleanup();
    return 0;
}

bool init()
{
    bool success = true;
    if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0 )
    {
        std::cout << "Unable to initialize SDL \n";
        success = false;
    }
    else
    {
        if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled! \n";
        }
        gWindow = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if ( gWindow == nullptr )
        {
            std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if ( gRenderer == nullptr )
            {
                std::cout << "Renderer could not be created! Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
            int imgFlags = IMG_INIT_PNG;
            if ( !( IMG_Init(imgFlags) & imgFlags ))
            {
                std::cout << "SDL_Image could not initialize ! Error:" << SDL_GetError() << std::endl;
                success = false;
            }
            if ( TTF_Init() == -1 )
            {
                success = false;
            }
            font = TTF_OpenFont("font/pixel.ttf", 50);
            if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 1024) < 0 )
            {
                success = false;
            }
        }
        return success;
    }
}

void prepareGameMaterial()
{
    menuMusic = Mix_LoadMUS("sound/menu.mp3");
    hitted = Mix_LoadWAV("sound/hitted.wav");
    spawnBulletOnDie = Mix_LoadWAV("sound/spawnBulletOnDie.wav");
    powerUp = Mix_LoadWAV("sound/powerup.wav");
    shoot = Mix_LoadWAV("sound/shoot.wav");
    playing = Mix_LoadMUS("sound//playingBackground.mp3");
    if ( menuMusic == nullptr ||
         hitted == nullptr ||
         spawnBulletOnDie == nullptr ||
         powerUp == nullptr ||
         shoot == nullptr ||
         playing == nullptr )
    {
        std::cout << SDL_GetError() << std::endl;
    }
    pauseBackground.loadTexture("img/pause.png", gRenderer);
    helpBackground.loadTexture("img/help.png", gRenderer);
    menuBackground.loadTexture("img/mainMenu.png", gRenderer);
    gameOverBackground.loadTexture("img/gameover.png", gRenderer);
    background.loadTexture("img/background.png", gRenderer);
    playButton.setContent("PLAY");
    playButton.setColor(WHITE_TEXT);
    playButton.createTexture(font, gRenderer);
    helpButton.setContent("HELP");
    helpButton.setColor(WHITE_TEXT);
    helpButton.createTexture(font, gRenderer);
    exitButton.setContent("EXIT");
    exitButton.setColor(WHITE_TEXT);
    exitButton.createTexture(font, gRenderer);
    restartButton.setContent("RESTART");
    restartButton.setColor(WHITE_TEXT);
    restartButton.createTexture(font, gRenderer);
    backButton.setContent("BACK");
    backButton.setColor(WHITE_TEXT);
    backButton.createTexture(font, gRenderer);
    shieldRemainTime.setContent("SHIELD TIME");
    shieldRemainTime.setColor(WHITE_TEXT);
    shieldRemainTime.createTexture(font, gRenderer);
    health.setColor(WHITE_TEXT);
    health.setContent("HEALTH");
    health.createTexture(font, gRenderer);
    shieldRemainTimeValue.setColor(RED_TEXT);
    scoreValue.setContent("0");
    scoreValue.setColor(RED_TEXT);
    scoreValue.createTexture(font, gRenderer);
    score.setContent("SCORE");
    score.setColor(WHITE_TEXT);
    score.createTexture(font, gRenderer);
    highscore.setContent("HIGH-SCORE");
    highscore.setColor(WHITE_TEXT);
    highscore.createTexture(font, gRenderer);
    highscoreValue.setContent("0");
    highscoreValue.setColor(WHITE_TEXT);
    waveText.setContent("WAVE: ");
    waveText.setColor(WHITE_TEXT);
    waveText.createTexture(font, gRenderer);
    waveValue.setContent("0");
    waveValue.setColor(BLUE_TEXT);
    waveValue.createTexture(font, gRenderer);
    player.SetHP(3);
    player.loadCharacter(gRenderer);
    player.setPos((float)SCREEN_WIDTH / 2 - player.getTextureWidth() / 2,
                  (float)SCREEN_HEIGHT / 2 - player.getTextureHeight() / 2);

    Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
    Mix_VolumeChunk(hitted, MIX_MAX_VOLUME / 12);
    Mix_VolumeChunk(shoot, MIX_MAX_VOLUME / 12);
    Mix_VolumeChunk(spawnBulletOnDie, MIX_MAX_VOLUME / 12);
    Mix_VolumeChunk(powerUp, MIX_MAX_VOLUME / 12);

    for ( int i = 0; i < 3; i++ )
    {
        healthList[i].loadTexture("img/health_icon.png", gRenderer);
        healthList[i].setPos(( 2 + healthList->getTextureWidth()) * i, health.getTextureHeight());
        healthList[i].updateBoundingBox();
    }
}

void cleanup()
{
    player.free();
    background.free();
    gameOverBackground.free();
    menuBackground.free();
    helpBackground.free();
    pauseBackground.free();
    playButton.free();
    helpButton.free();
    exitButton.free();
    restartButton.free();
    backButton.free();
    shieldRemainTime.free();
    shieldRemainTimeValue.free();
    health.free();
    score.free();
    scoreValue.free();
    highscore.free();
    highscoreValue.free();
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    Mix_FreeMusic(menuMusic);
    menuMusic = nullptr;
    Mix_FreeMusic(playing);
    playing = nullptr;
    Mix_FreeChunk(shoot);
    shoot = nullptr;
    Mix_FreeChunk(spawnBulletOnDie);
    spawnBulletOnDie = nullptr;
    Mix_FreeChunk(powerUp);
    powerUp = nullptr;
    Mix_FreeChunk(hitted);
    hitted = nullptr;
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}