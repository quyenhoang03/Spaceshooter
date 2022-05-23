//
// Created by Quyen on 5/20/2022.
//

#include "Common.h"

std::string getHighscoreFromFile(const std::string &path)
{
    std::ifstream file;
    std::string highscore;
    file.open(path.c_str());
    file >> highscore;
    return highscore;
}

void updateHighscore(const std::string &path, const unsigned long long int &score)
{
    std::ifstream inFile;
    std::string oldHighscore;
    inFile.open(path.c_str());
    inFile >> oldHighscore;
    inFile.close();
    unsigned long long int highscore = 0;
    std::stringstream convert(oldHighscore);
    convert >> highscore;
    if (score > highscore)
    {
        highscore = score;
        std::ofstream outFile;
        outFile.open(path.c_str(), std::ios::out | std::ios::trunc);
        outFile << std::to_string(highscore);
        outFile.close();
    }
}