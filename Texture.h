//
// Created by Quyen on 4/21/2022.
//

#ifndef SPACESHOOTER_TEXTURE_H_INCLUDED
#define SPACESHOOTER_TEXTURE_H_INCLUDED


#include "Common.h"

class Texture
{
public:
    Texture();

    ~Texture();

    float getTextureWidth() const;

    float getTextureHeight() const;

    bool loadTexture( const std::string &path, SDL_Renderer *screen );

    void free();

    void scrollTexture( int &scroll, SDL_Renderer *screen );

    SDL_Texture *getTexture();

    void renderFullScreen( SDL_Renderer *screen );

protected:
    SDL_Texture *mTexture;

    float mTextureWidth;
    float mTextureHeight;
};

#endif //SPACESHOOTER_TEXTURE_H_INCLUDED