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
    this->setLayerDot();
    this->_entities[14][12][1] = std::make_shared<PacmanEntity>(4, "", std::make_pair(12, 14));
}

void PacmanGame::setLayerWalls()
{
    this->setLayerHub();
    this->setLayerBorders();
    this->setLayerPortal();
    this->setLayerModules();
    this->setLayerSquareModules();
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
    for (int x = 0; x < MAP_WIDTH; x++) {
        this->_entities[0][x][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(x, 0));
        this->_entities[MAP_HEIGHT - 1 - 2][x][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(x, MAP_HEIGHT - 1 - 2));
    }
    this->_entities[0][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/jointopright.png", 1, "", std::make_pair(7, 0));
    this->_entities[0][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/jointopleft.png", 1, "", std::make_pair(8, 0));
    this->_entities[1][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 1));
    this->_entities[1][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(8, 1));
    this->_entities[2][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 2));
    this->_entities[2][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(8, 2));
    this->_entities[3][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(7, 3));
    this->_entities[3][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(8, 3));

    this->_entities[0][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/jointopright.png", 1, "", std::make_pair(16, 0));
    this->_entities[0][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/jointopleft.png", 1, "", std::make_pair(17, 0));
    this->_entities[1][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(16, 1));
    this->_entities[1][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 1));
    this->_entities[2][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(16, 2));
    this->_entities[2][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 2));
    this->_entities[3][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(16, 3));
    this->_entities[3][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(17, 3));

    this->_entities[0][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/jointopright.png", 1, "", std::make_pair(10, 0));
    this->_entities[0][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/topbar.png", 1, "", std::make_pair(11, 0));
    this->_entities[0][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/topbar.png", 1, "", std::make_pair(12, 0));
    this->_entities[0][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/topbar.png", 1, "", std::make_pair(13, 0));
    this->_entities[0][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/jointopleft.png", 1, "", std::make_pair(14, 0));
    this->_entities[1][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(10, 1));
    this->_entities[1][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(14, 1));
    this->_entities[2][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(10, 2));
    this->_entities[2][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(11, 2));
    this->_entities[2][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(12, 2));
    this->_entities[2][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(13, 2));
    this->_entities[2][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(14, 2));

    this->_entities[21][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(10, 0));
    this->_entities[21][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(11, 21));
    this->_entities[21][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(12, 21));
    this->_entities[21][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(13, 21));
    this->_entities[21][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(14, 21));
    this->_entities[22][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/joinbotright.png", 1, "", std::make_pair(10, 22));
    this->_entities[22][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/botbar.png", 1, "", std::make_pair(11, 22));
    this->_entities[22][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/botbar.png", 1, "", std::make_pair(12, 22));
    this->_entities[22][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/botbar.png", 1, "", std::make_pair(13, 22));
    this->_entities[22][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/joinbotleft.png", 1, "", std::make_pair(14, 22));

    this->_entities[20][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(7, 20));
    this->_entities[20][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(8, 20));
    this->_entities[21][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(7, 21));
    this->_entities[21][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(8, 21));
    this->_entities[22][7][1] = std::make_shared<WallEntity>("assets/pacman/walls/joinbotright.png", 1, "", std::make_pair(7, 22));
    this->_entities[22][8][1] = std::make_shared<WallEntity>("assets/pacman/walls/joinbotleft.png", 1, "", std::make_pair(8, 22));

    this->_entities[20][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(16, 20));
    this->_entities[20][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(17, 20));
    this->_entities[21][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(16, 21));
    this->_entities[21][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(17, 21));
    this->_entities[22][16][1] = std::make_shared<WallEntity>("assets/pacman/walls/joinbotright.png", 1, "", std::make_pair(16, 22));
    this->_entities[22][17][1] = std::make_shared<WallEntity>("assets/pacman/walls/joinbotleft.png", 1, "", std::make_pair(17, 22));

    this->_entities[0][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftdouble.png", 1, "", std::make_pair(0, 0));
    for (int x = 1; x < 7; x++)
        this->_entities[x][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, x));
    this->_entities[7][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftdouble.png", 1, "", std::make_pair(0, 7));
    for (int x = 1; x < 5; x++)
        this->_entities[7][x][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(x, 7));
    this->_entities[7][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightdot.png", 1, "", std::make_pair(5, 7));
    this->_entities[8][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(5, 8));
    this->_entities[9][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(5, 9));

    this->_entities[22][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftdouble.png", 1, "", std::make_pair(0, 22));
    for (int x = 21; x > 15; x--)
        this->_entities[x][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(0, x));
    this->_entities[15][0][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftdouble.png", 1, "", std::make_pair(0, 15));
    for (int x = 1; x < 5; x++)
        this->_entities[15][x][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(x, 15));
    this->_entities[15][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightdot.png", 1, "", std::make_pair(5, 15));
    this->_entities[14][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(5, 14));
    this->_entities[13][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftvertical.png", 1, "", std::make_pair(5, 13));

    this->_entities[0][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightdouble.png", 1, "", std::make_pair(0, 0));
    for (int x = 1; x < 7; x++)
        this->_entities[x][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(24, x));
    this->_entities[7][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightdouble.png", 1, "", std::make_pair(0, 7));
    for (int x = 23; x > 19; x--)
        this->_entities[7][x][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontal.png", 1, "", std::make_pair(x, 7));
    this->_entities[7][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftdot.png", 1, "", std::make_pair(5, 7));
    this->_entities[8][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(5, 8));
    this->_entities[9][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(5, 9));

    this->_entities[22][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightdouble.png", 1, "", std::make_pair(0, 22));
    for (int x = 21; x > 15; x--)
        this->_entities[x][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightvertical.png", 1, "", std::make_pair(24, x));
    this->_entities[15][24][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightdouble.png", 1, "", std::make_pair(0, 15));
    for (int x = 23; x > 19; x--)
        this->_entities[15][x][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontal.png", 1, "", std::make_pair(x, 15));
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

    this->_entities[8][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(11, 8));
    this->_entities[8][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(12, 8));
    this->_entities[8][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(13, 8));
    this->_entities[7][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(11, 7));
    this->_entities[7][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(13, 7));
    this->_entities[6][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(11, 6));
    this->_entities[6][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(13, 6));
    this->_entities[5][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(11, 5));
    this->_entities[5][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(10, 5));
    this->_entities[5][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(13, 5));
    this->_entities[5][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(14, 5));
    this->_entities[4][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(10, 5));
    this->_entities[4][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(11, 5));
    this->_entities[4][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(12, 5));
    this->_entities[4][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(13, 5));
    this->_entities[4][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(14, 5));

    this->_entities[15][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(11, 15));
    this->_entities[15][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(12, 15));
    this->_entities[15][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(13, 15));
    this->_entities[16][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(11, 16));
    this->_entities[16][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(13, 16));
    this->_entities[17][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(11, 17));
    this->_entities[17][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(13, 17));
    this->_entities[18][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(11, 18));
    this->_entities[18][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(10, 18));
    this->_entities[18][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(13, 18));
    this->_entities[18][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(14, 18));
    this->_entities[19][10][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(10, 18));
    this->_entities[19][11][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(11, 19));
    this->_entities[19][12][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(12, 19));
    this->_entities[19][13][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(13, 19));
    this->_entities[19][14][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(14, 19));
}

void PacmanGame::setLayerSquareModules()
{
    this->_entities[5][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(2, 5));
    this->_entities[4][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(2, 4));
    this->_entities[5][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(3, 5));
    this->_entities[5][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(4, 5));
    this->_entities[5][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(2, 5));
    this->_entities[4][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(2, 4));
    this->_entities[3][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(2, 3));
    this->_entities[2][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(2, 2));
    this->_entities[2][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(3, 2));
    this->_entities[2][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(4, 2));
    this->_entities[3][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(2, 3));
    this->_entities[2][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(2, 2));

    this->_entities[17][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(2, 17));
    this->_entities[18][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(2, 18));
    this->_entities[17][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(3, 17));
    this->_entities[17][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(4, 17));
    this->_entities[17][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(2, 17));
    this->_entities[18][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(2, 18));
    this->_entities[19][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(2, 19));
    this->_entities[20][2][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(2, 20));
    this->_entities[20][3][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(3, 20));
    this->_entities[20][4][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(4, 20));
    this->_entities[19][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(2, 19));
    this->_entities[20][5][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(2, 20));

    this->_entities[4][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(19, 4));
    this->_entities[5][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(19, 5));
    this->_entities[5][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(20, 5));
    this->_entities[5][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(21, 5));
    this->_entities[5][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(22, 5));
    this->_entities[4][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(22, 4));
    this->_entities[3][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(19, 3));
    this->_entities[2][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(19, 2));
    this->_entities[2][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(20, 2));
    this->_entities[2][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(21, 2));
    this->_entities[3][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(22, 3));
    this->_entities[2][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(22, 2));

    this->_entities[17][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/botleftround.png", 1, "", std::make_pair(19, 17));
    this->_entities[18][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(19, 18));
    this->_entities[17][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(20, 17));
    this->_entities[17][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/tophorizontalsimple.png", 1, "", std::make_pair(21, 17));
    this->_entities[17][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/botrightround.png", 1, "", std::make_pair(22, 17));
    this->_entities[18][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(22, 18));
    this->_entities[19][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/leftverticalsimple.png", 1, "", std::make_pair(19, 19));
    this->_entities[20][19][1] = std::make_shared<WallEntity>("assets/pacman/walls/toprightround.png", 1, "", std::make_pair(19, 20));
    this->_entities[20][20][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(20, 20));
    this->_entities[20][21][1] = std::make_shared<WallEntity>("assets/pacman/walls/bothorizontalsimple.png", 1, "", std::make_pair(21, 20));
    this->_entities[19][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/rightverticalsimple.png", 1, "", std::make_pair(22, 19));
    this->_entities[20][22][1] = std::make_shared<WallEntity>("assets/pacman/walls/topleftround.png", 1, "", std::make_pair(22, 20));
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

void PacmanGame::setLayerDot()
{
    std::vector<std::pair<size_t, size_t>> positions = {
        {0, 11},
        {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 11}, {1, 16}, {1, 17}, {1, 18}, {1, 19}, {1, 20}, {1, 21},
        {2, 1}, {2, 6}, {2, 11}, {2, 16}, {2, 21},
        {3, 1}, {3, 6}, {3, 11}, {3, 16}, {3, 21},
        {4, 1}, {4, 6}, {4, 11}, {4, 16}, {4, 21},
        {5, 1}, {5, 6}, {5, 11}, {5, 16}, {5, 21},
        {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6},{6, 7}, {6, 8}, {6, 9}, {6, 10}, {6, 11}, {6, 12}, {6, 13}, {6, 14}, {6, 15}, {6, 16}, {6, 17}, {6, 18}, {6, 19}, {6, 20}, {6, 21},
        {7, 4}, {7, 11}, {7, 19},
        {8, 4}, {8, 11}, {8, 19},
        {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5}, {9, 6}, {9, 9}, {9, 10}, {9, 11}, {9, 12}, {9, 13}, {9, 14}, {9, 17}, {9, 18}, {9, 19}, {9, 20}, {9, 21},
        {10, 3}, {10, 6}, {10, 7}, {10, 8}, {10, 9}, {10, 14}, {10, 15}, {10, 16}, {10, 17}, {10, 20},
        {11, 3}, {11, 9}, {11, 14}, {11, 20},
        {12, 3}, {12, 9}, {12, 20},
        {13, 3}, {13, 9}, {13, 14}, {13, 20},
        {14, 3}, {14, 6}, {14, 7}, {14, 8}, {14, 9}, {14, 14}, {14, 15}, {14, 16}, {14, 17}, {14, 20},
        {15, 1}, {15, 2}, {15, 3}, {15, 4}, {15, 5}, {15, 6}, {15, 9}, {15, 10}, {15, 11}, {15, 12}, {15, 13}, {15, 14}, {15, 17}, {15, 18}, {15, 19}, {15, 20}, {15, 21},
        {16, 4}, {16, 11}, {16, 19},
        {17, 4}, {17, 11}, {17, 19},
        {18, 1}, {18, 2}, {18, 3}, {18, 4}, {18, 5}, {18, 6}, {18, 7}, {18, 8}, {18, 9}, {18, 10}, {18, 11}, {18, 12}, {18, 13}, {18, 14}, {18, 15}, {18, 16}, {18, 17}, {18, 18},  {18, 19}, {18, 20}, {18, 21},
        {19, 1}, {19, 6}, {19, 11}, {19, 16}, {19, 21},
        {20, 1}, {20, 6}, {20, 11}, {20, 16}, {20, 21},
        {21, 1}, {21, 6}, {21, 11}, {21, 16}, {21, 21},
        {22, 1}, {22, 6}, {22, 11}, {22, 16}, {22, 21},
        {23, 1}, {23, 1}, {23, 2}, {23, 3}, {23, 4}, {23, 5}, {23, 6}, {23, 11}, {23, 16}, {23, 17}, {23, 18}, {23, 19}, {23, 20}, {23, 21},
        {24, 11},
    };

    for (const auto &pos : positions) {
        this->_entities[pos.second][pos.first][1] = std::make_shared<DotEntity>(pos);
    }
    this->setLayerBigDot();
}

void PacmanGame::setLayerBigDot()
{
    // TODO
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
