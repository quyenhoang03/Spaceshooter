//
// Created by Quyen on 4/21/2022.
//

#include "Texture.h"

Texture::Texture()
{
    mTexture = nullptr;
    mTextureWidth = 0;
    mTextureHeight = 0;
}

Texture::~Texture()
{
    free();
}

float Texture::getTextureHeight() const
{
    return mTextureHeight;
}

float Texture::getTextureWidth() const
{
    return mTextureWidth;
}

bool Texture::loadTexture(const std::string &path, SDL_Renderer *screen)
{
    free();
    bool success = true;
    SDL_Surface *loadSurface = IMG_Load(path.c_str());
    if (loadSurface == nullptr)
    {
        std::cout << "Cannot load surface from " << path << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        mTextureWidth = loadSurface->w;
        mTextureHeight = loadSurface->h;
        mTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
        if (mTexture == nullptr)
        {
            std::cout << "Failed to create texture from surface " << SDL_GetError() << std::endl;
            success = false;
        }
    }
    SDL_FreeSurface(loadSurface);
    loadSurface = nullptr;
    return success;
}

void Texture::free()
{
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mTextureHeight = 0;
        mTextureWidth = 0;
    }
}

SDL_Texture *Texture::getTexture()
{
    return mTexture;
}

void Texture::scrollTexture(int &scroll, SDL_Renderer *screen)
{
    SDL_FRect bottom{0, (float)scroll, mTextureWidth, mTextureHeight};
    SDL_FRect top{0, (float)scroll - mTextureHeight, mTextureWidth, mTextureHeight};
    SDL_RenderCopyF(screen, mTexture, nullptr, &bottom);
    SDL_RenderCopyF(screen, mTexture, nullptr, &top);
    scroll++;
    if (scroll > mTextureHeight)
    {
        scroll = 0;
    }
}

void Texture::renderFullScreen(SDL_Renderer *screen)
{
    SDL_RenderCopyF(screen, mTexture, nullptr, nullptr);
}