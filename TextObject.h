//
// Created by Quyen on 5/18/2022.
//

#ifndef SPACESHOOTER_TEXTOBJECT_H
#define SPACESHOOTER_TEXTOBJECT_H

#include "Texture.h"

enum Color
{
RED_TEXT = 0,
BLUE_TEXT = 1,
WHITE_TEXT = 2,
};

class TextObject : public Texture
{
protected:
    std::string content;
    SDL_Color textColor;

public:
    TextObject();

    void createTexture( TTF_Font *font, SDL_Renderer *screen );

    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    void setColor( Color color );

    void renderText( SDL_Renderer *screen, float x, float y, SDL_Rect *clip = nullptr, double angle = 0.0,
                     SDL_FPoint *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );

    void setContent( const std::string &text )
    {
        content = text;
    }

    std::string getWord() const
    {
        return content;
    }
};

#endif // SPACESHOOTER_TEXTOBJECT_H
