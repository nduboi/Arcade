/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeGame
*/

#include "SnakeGame.hpp"
#include "VoidEntity.hpp"
#include "SnakeHeadEntity.hpp"
#include "SnakeBodyEntity.hpp"
#include "AppleEntity.hpp"

#include "ScoreEntityHUD.hpp"
#include "TimeEntityHUD.hpp"

const int MAP_HEIGHT = 17;
const int MAP_WIDTH = 17;
const int MAP_LAYER = 2;

SnakeGame::SnakeGame()
{
    this->_highScore = 0;
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now(); // Initialize with current time

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

void SnakeGame::setLayerBackground()
{
    bool grass = false;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (grass)
                this->_entities[y][x][0] = std::make_shared<VoidEntity>("assets/snake/grass_bright.png", 0, "", std::make_pair(x, y));
            else
                this->_entities[y][x][0] = std::make_shared<VoidEntity>("assets/snake/grass_dark.png", 0, "", std::make_pair(x, y));
            grass = !grass;
        }
    }
}

void SnakeGame::setLayerEntities()
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            this->_entities[y][x][1] = std::make_shared<VoidEntity>(this->_entities[y][x][0]->getSpriteName(), 0, "", std::make_pair(x, y));
        }
    }

    this->_entities[8][8][1] = std::make_shared<SnakeHeadEntity>(4, "O", std::make_pair(8, 8));
    this->setSnakeBody();
    this->setLayerApple();
}

void SnakeGame::setSnakeBody()
{
    this->_entities[8][7][1] = std::make_shared<SnakeBodyEntity>(3, "=", std::make_pair(7, 8), 0);
    this->_entities[8][6][1] = std::make_shared<SnakeBodyEntity>(3, "=", std::make_pair(6, 8), 1);
    this->_entities[8][5][1] = std::make_shared<SnakeBodyEntity>(3, "=", std::make_pair(5, 8), 2);

    auto body1 = std::dynamic_pointer_cast<SnakeBodyEntity>(this->_entities[8][7][1]);
    auto body2 = std::dynamic_pointer_cast<SnakeBodyEntity>(this->_entities[8][6][1]);
    auto body3 = std::dynamic_pointer_cast<SnakeBodyEntity>(this->_entities[8][5][1]);

    if (body1) body1->updateDirection(std::make_pair(7, 8), std::make_pair(8, 8), std::make_pair(6, 8));
    if (body2) body2->updateDirection(std::make_pair(6, 8), std::make_pair(7, 8), std::make_pair(5, 8));
    if (body3) body3->updateDirection(std::make_pair(5, 8), std::make_pair(6, 8), std::make_pair(100, 100));

    auto head = std::dynamic_pointer_cast<SnakeHeadEntity>(this->_entities[8][8][1]);
    if (head) {
        head->initializePreviousPositions({std::make_pair(5, 8), std::make_pair(6, 8),
                                        std::make_pair(7, 8), std::make_pair(8, 8)
        });
    }
}

void SnakeGame::setLayerApple()
{
    // Create apple at random position
    srand(time(NULL));
    std::pair<size_t, size_t> newPos = {rand() % MAP_WIDTH, rand() % MAP_HEIGHT};
    while (!std::dynamic_pointer_cast<VoidEntity>(this->_entities[newPos.second][newPos.first][1])) {
        newPos = {rand() % MAP_WIDTH, rand() % MAP_HEIGHT};
    }

    this->_entities[newPos.second][newPos.first][1] = std::make_shared<AppleEntity>(newPos);
}

std::vector<std::shared_ptr<IEntity>> SnakeGame::getHUD() const
{
    std::vector<std::shared_ptr<IEntity>> hud;

    hud.push_back(std::make_shared<ScoreEntityHUD>(this->getScore()));

    std::size_t secondsElapsed = this->getTime();
    hud.push_back(std::make_shared<TimeEntityHUD>(secondsElapsed));
    return hud;
}
