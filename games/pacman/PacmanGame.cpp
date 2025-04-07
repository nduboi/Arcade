/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** PacmanGame
*/

#include "PacmanGame.hpp"
#include "VoidEntity.hpp"
#include "WallEntity.hpp"
#include "PacmanEntity.hpp"
#include "DotEntity.hpp"

#include "ScoreEntityHUD.hpp"
#include "HighScoreEntityHUD.hpp"
#include "TimeEntityHUD.hpp"
#include "BigTextEntityHUD.hpp"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 25;
const int MAP_LAYER = 2;

PacmanGame::PacmanGame()
{
    this->_highScore = 0;
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now();

    this->_entities.resize(MAP_HEIGHT);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        this->_entities[y].resize(MAP_WIDTH);
        for (int x = 0; x < MAP_WIDTH; x++) {
            this->_entities[y][x].resize(MAP_LAYER);
        }
    }
    this->setLayerBackground();
    this->setLayerEntities();
}

void PacmanGame::setLayerBackground()
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
                this->_entities[y][x][0] = std::make_shared<VoidEntity>("assets/pacman/walls/void.png", 0, "", std::make_pair(x, y));
        }
    }
}

void PacmanGame::setLayerEntities()
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            this->_entities[y][x][1] = std::make_shared<VoidEntity>("assets/pacman/walls/void.png", 0, "", std::make_pair(x, y));
        }
    }

    this->setLayerWalls();
    this->_entities[14][12][1] = std::make_shared<PacmanEntity>(4, "", std::make_pair(12, 14));
    // this->setLayerApple();
}

void PacmanGame::setLayerWalls()
{
    this->setLayerHub();
    this->setLayerBorders();
    this->setLayerPortal();
    this->setLayerModules();
}

void PacmanGame::setLayerHub()
{
    this->_entities[13][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftdot.png", 1, "", std::make_pair(10, 13));
    this->_entities[13][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(11, 13));
    this->_entities[13][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(12, 13));
    this->_entities[13][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(13, 13));
    this->_entities[13][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightdot.png", 1, "", std::make_pair(14, 13));
    this->_entities[12][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(10, 12));
    this->_entities[12][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(14, 12));
    this->_entities[11][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(10, 11));
    this->_entities[11][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(14, 11));
    this->_entities[10][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftdot.png", 1, "", std::make_pair(10, 10));
    this->_entities[10][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightdot.png", 1, "", std::make_pair(14, 10));
    this->_entities[10][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(11, 10));
    this->_entities[10][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/barrier.png", 1, "", std::make_pair(12, 10));
    this->_entities[10][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(13, 10));
}

void PacmanGame::setLayerBorders()
{
    this->_entities[0][1][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(1, 0));
    this->_entities[0][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(2, 0));
    this->_entities[0][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(3, 0));
    this->_entities[0][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(4, 0));
    this->_entities[0][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(5, 0));
    this->_entities[0][6][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(6, 0));
    this->_entities[0][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(7, 0));
    this->_entities[0][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(8, 0));
    this->_entities[0][9][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(9, 0));
    this->_entities[0][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(10, 0));
    this->_entities[0][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(11, 0));
    this->_entities[0][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(12, 0));
    this->_entities[0][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(13, 0));
    this->_entities[0][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(14, 0));
    this->_entities[0][15][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(15, 0));
    this->_entities[0][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(16, 0));
    this->_entities[0][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(17, 0));
    this->_entities[0][18][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(18, 0));
    this->_entities[0][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(19, 0));
    this->_entities[0][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(20, 0));
    this->_entities[0][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(21, 0));
    this->_entities[0][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(22, 0));
    this->_entities[0][23][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(23, 0));

    this->_entities[22][1][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(1, 22));
    this->_entities[22][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(2, 22));
    this->_entities[22][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(3, 22));
    this->_entities[22][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(4, 22));
    this->_entities[22][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(5, 22));
    this->_entities[22][6][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(6, 22));
    this->_entities[22][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(7, 22));
    this->_entities[22][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(8, 22));
    this->_entities[22][9][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(9, 22));
    this->_entities[22][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(10, 22));
    this->_entities[22][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(11, 22));
    this->_entities[22][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(12, 22));
    this->_entities[22][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(13, 22));
    this->_entities[22][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(14, 22));
    this->_entities[22][15][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(15, 22));
    this->_entities[22][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(16, 22));
    this->_entities[22][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(17, 22));
    this->_entities[22][18][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(18, 22));
    this->_entities[22][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(19, 22));
    this->_entities[22][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(20, 22));
    this->_entities[22][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(21, 22));
    this->_entities[22][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(22, 22));
    this->_entities[22][23][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(23, 22));

    this->_entities[0][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftdouble.png", 1, "", std::make_pair(0, 0));
    this->_entities[1][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 1));
    this->_entities[2][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 2));
    this->_entities[3][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 3));
    this->_entities[4][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 4));
    this->_entities[5][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 5));
    this->_entities[6][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 6));
    this->_entities[7][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftdouble.png", 1, "", std::make_pair(0, 7));
    this->_entities[7][1][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(1, 7));
    this->_entities[7][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(2, 7));
    this->_entities[7][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(3, 7));
    this->_entities[7][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(4, 7));
    this->_entities[7][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightdot.png", 1, "", std::make_pair(5, 7));
    this->_entities[8][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(5, 8));
    this->_entities[9][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(5, 9));

    this->_entities[22][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftdouble.png", 1, "", std::make_pair(0, 22));
    this->_entities[21][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 21));
    this->_entities[20][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 20));
    this->_entities[19][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 19));
    this->_entities[18][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 18));
    this->_entities[17][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 17));
    this->_entities[16][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, 16));
    this->_entities[15][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftdouble.png", 1, "", std::make_pair(0, 15));
    this->_entities[15][1][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(1, 15));
    this->_entities[15][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(2, 15));
    this->_entities[15][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(3, 15));
    this->_entities[15][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(4, 15));
    this->_entities[15][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightdot.png", 1, "", std::make_pair(5, 15));
    this->_entities[14][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(5, 14));
    this->_entities[13][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(5, 13));

    this->_entities[0][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightdouble.png", 1, "", std::make_pair(0, 0));
    this->_entities[1][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 1));
    this->_entities[2][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 2));
    this->_entities[3][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 3));
    this->_entities[4][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 4));
    this->_entities[5][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 5));
    this->_entities[6][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 6));
    this->_entities[7][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightdouble.png", 1, "", std::make_pair(0, 7));
    this->_entities[7][23][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(1, 7));
    this->_entities[7][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(2, 7));
    this->_entities[7][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(3, 7));
    this->_entities[7][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(4, 7));
    this->_entities[7][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftdot.png", 1, "", std::make_pair(5, 7));
    this->_entities[8][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(5, 8));
    this->_entities[9][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(5, 9));

    this->_entities[22][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightdouble.png", 1, "", std::make_pair(0, 22));
    this->_entities[21][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 21));
    this->_entities[20][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 20));
    this->_entities[19][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 19));
    this->_entities[18][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 18));
    this->_entities[17][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 17));
    this->_entities[16][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(0, 16));
    this->_entities[15][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightdouble.png", 1, "", std::make_pair(0, 15));
    this->_entities[15][23][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(1, 15));
    this->_entities[15][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(2, 15));
    this->_entities[15][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(3, 15));
    this->_entities[15][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(4, 15));
    this->_entities[15][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftdot.png", 1, "", std::make_pair(5, 15));
    this->_entities[14][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(5, 14));
    this->_entities[13][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(5, 13));
}

void PacmanGame::setLayerModules()
{
    this->_entities[10][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(7, 10));
    this->_entities[10][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(8, 10));
    this->_entities[9][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 9));
    this->_entities[9][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(8, 9));
    this->_entities[8][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 8));
    this->_entities[8][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(8, 8));
    this->_entities[8][9][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(9, 8));
    this->_entities[7][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 7));
    this->_entities[7][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(8, 7));
    this->_entities[7][9][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(9, 7));
    this->_entities[6][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 6));
    this->_entities[6][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(8, 6));
    this->_entities[5][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(7, 5));
    this->_entities[5][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(8, 5));

    this->_entities[10][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(16, 10));
    this->_entities[10][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(17, 10));
    this->_entities[9][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(16, 9));
    this->_entities[9][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 9));
    this->_entities[8][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(16, 8));
    this->_entities[8][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 8));
    this->_entities[8][15][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(15, 8));
    this->_entities[7][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(16, 7));
    this->_entities[7][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 7));
    this->_entities[7][15][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(15, 7));
    this->_entities[6][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(16, 6));
    this->_entities[6][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 6));
    this->_entities[5][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(16, 5));
    this->_entities[5][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(17, 5));

    this->_entities[12][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(7, 12));
    this->_entities[12][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(8, 12));
    this->_entities[13][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 13));
    this->_entities[13][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(8, 13));
    this->_entities[14][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 14));
    this->_entities[14][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(8, 14));
    this->_entities[15][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 15));
    this->_entities[15][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(8, 15));
    this->_entities[15][9][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(9, 15));
    this->_entities[16][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 16));
    this->_entities[16][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(8, 16));
    this->_entities[16][9][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(9, 16));
    this->_entities[17][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 17));
    this->_entities[17][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(8, 17));
    this->_entities[18][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(7, 18));
    this->_entities[18][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(8, 18));

    this->_entities[12][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(16, 12));
    this->_entities[12][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(17, 12));
    this->_entities[13][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(16, 13));
    this->_entities[13][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 13));
    this->_entities[14][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(16, 14));
    this->_entities[14][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 14));
    this->_entities[15][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(16, 15));
    this->_entities[15][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(17, 15));
    this->_entities[15][15][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(15, 15));
    this->_entities[16][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(16, 16));
    this->_entities[16][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 16));
    this->_entities[16][15][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(15, 16));
    this->_entities[17][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(16, 17));
    this->_entities[17][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 17));
    this->_entities[18][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(16, 18));
    this->_entities[18][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(17, 18));
}

void PacmanGame::setLayerPortal()
{
    this->_entities[10][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(0, 10));
    this->_entities[10][1][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(1, 10));
    this->_entities[10][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(2, 10));
    this->_entities[10][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(3, 10));
    this->_entities[10][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(4, 10));
    this->_entities[10][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightdot.png", 1, "", std::make_pair(5, 10));

    this->_entities[12][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(0, 12));
    this->_entities[12][1][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(1, 12));
    this->_entities[12][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(2, 12));
    this->_entities[12][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(3, 12));
    this->_entities[12][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(4, 12));
    this->_entities[12][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightdot.png", 1, "", std::make_pair(5, 12));

    this->_entities[10][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(24, 10));
    this->_entities[10][23][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(23, 10));
    this->_entities[10][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(22, 10));
    this->_entities[10][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(21, 10));
    this->_entities[10][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(20, 10));
    this->_entities[10][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftdot.png", 1, "", std::make_pair(19, 10));

    this->_entities[12][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(24, 12));
    this->_entities[12][23][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(23, 12));
    this->_entities[12][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(22, 12));
    this->_entities[12][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(21, 12));
    this->_entities[12][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(20, 12));
    this->_entities[12][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftdot.png", 1, "", std::make_pair(19, 12));
}

void PacmanGame::setLayerApple()
{
    // Create apple at random position
    srand(time(NULL));
    std::pair<size_t, size_t> newPos = {rand() % MAP_WIDTH, rand() % MAP_HEIGHT};
    while (!std::dynamic_pointer_cast<VoidEntity>(this->_entities[newPos.second][newPos.first][1])) {
        newPos = {rand() % MAP_WIDTH, rand() % MAP_HEIGHT};
    }

    this->_entities[newPos.second][newPos.first][1] = std::make_shared<DotEntity>(newPos);
}

std::vector<std::shared_ptr<IEntity>> PacmanGame::getHUD() const
{
    std::vector<std::shared_ptr<IEntity>> hud;

    hud.push_back(std::make_shared<ScoreEntityHUD>(this->getScore(), std::make_pair(10, 15)));
    hud.push_back(std::make_shared<HighScoreEntityHUD>(this->getHighScore(), std::make_pair(10, 55)));

    std::size_t secondsElapsed = this->getTime();
    hud.push_back(std::make_shared<TimeEntityHUD>(secondsElapsed, std::make_pair(350, 35)));


    if (this->getIsStarted() == false)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Press any direction to start", std::make_pair(250, 850)));
    if (this->getGameState() == LOSE)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Game Over", std::make_pair(350, 850)));
    if (this->getGameState() == WIN)
        hud.push_back(std::make_shared<BigTextEntityHUD>("You Win", std::make_pair(350, 850)));
    return hud;
}
