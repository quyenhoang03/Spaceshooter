//
// Created by Quyen on 4/19/2022.
//

#ifndef SPACESHOOTER_COMMON_H
#define SPACESHOOTER_COMMON_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>

using std::istringstream;

#define FPS 60
#define PI 3.14159265359

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 800;

std::string getHighscoreFromFile(const std::string &path);

void updateHighscore(const std::string &path, const unsigned long long int &score);

class Vector
{
private:
    double x;
    double y;

public:
    Vector()
    {
        x = 1;
        y = 1;
    }

    Vector(const int &rhsX, const int &rhsY)
    {
        x = rhsX;
        y = rhsY;
    }

    ~Vector() = default;

    void normalizeVector()
    {
        int prevX = x;
        int prevY = y;
        x = prevX / sqrt(prevX * prevX + prevY * prevY);
        y = prevY / sqrt(prevX * prevX + prevY * prevY);
    }

    double getX() const
    {
        return x;
    }

    double getY() const
    {
        return y;
    }
};

#endif // SPACESHOOTER_COMMON_H
