//
// Created by Quyen on 5/18/2022.
//

#include "TextObject.h"


TextObject::TextObject()
{
    textColor.r = 0;
    textColor.g = 0;
    textColor.b = 0;
}

void TextObject::createTexture( TTF_Font *font, SDL_Renderer *screen )
{
    free();
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, content.c_str(), textColor);
    if ( textSurface != nullptr )
    {
        mTexture = SDL_CreateTextureFromSurface(screen, textSurface);
        mTextureWidth = textSurface->w;
        mTextureHeight = textSurface->h;
        SDL_FreeSurface(textSurface);
    }
}

void TextObject::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
}

void TextObject::setColor( Color color )
{
    if ( color == RED_TEXT )
    {
        SDL_Color redColor = { 255, 0, 0 };
        textColor = redColor;
    }
    else if ( color == BLUE_TEXT )
    {
        SDL_Color blueColor = { 0, 128, 255 };
        textColor = blueColor;
    }
    else if ( color == WHITE_TEXT )
    {
        SDL_Color whiteColor = { 255, 255, 255 };
        textColor = whiteColor;
    }
}

void TextObject::renderText( SDL_Renderer *screen, float x, float y, SDL_Rect *clip, double angle, SDL_FPoint *center,
                             SDL_RendererFlip flip )
{
    SDL_FRect renderQuad = { (float)x, (float)y, mTextureWidth, mTextureHeight };
    if ( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyExF(screen, mTexture, clip, &renderQuad, angle, center, flip);
}
