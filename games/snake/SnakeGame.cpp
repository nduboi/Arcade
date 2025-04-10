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
#include "HighScoreEntityHUD.hpp"
#include "TimeEntityHUD.hpp"
#include "TextEntityHUD.hpp"
#include "BigTextEntityHUD.hpp"

const int MAP_HEIGHT = 17;
const int MAP_WIDTH = 17;
const int MAP_LAYER = 2;

SnakeGame::SnakeGame()
{
    this->_highScore = 0;
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now();
    this->_difficulty = 0;

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
                this->_entities[y][x][0] = std::make_shared<VoidEntity>("assets/snake/grass_bright.png", 1, "#", std::make_pair(x, y));
            else
                this->_entities[y][x][0] = std::make_shared<VoidEntity>("assets/snake/grass_dark.png", 1, "#", std::make_pair(x, y));
            grass = !grass;
        }
    }
}

void SnakeGame::setLayerEntities()
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            this->_entities[y][x][1] = std::make_shared<VoidEntity>(this->_entities[y][x][0]->getSpriteName(), 1, "", std::make_pair(x, y));
        }
    }

    this->_entities[8][8][1] = std::make_shared<SnakeHeadEntity>(4, "h", std::make_pair(8, 8));
    this->setSnakeBody();
    this->setLayerApple();
}

void SnakeGame::setSnakeBody()
{
    this->_entities[8][7][1] = std::make_shared<SnakeBodyEntity>(3, "b", std::make_pair(7, 8), 0);
    this->_entities[8][6][1] = std::make_shared<SnakeBodyEntity>(3, "b", std::make_pair(6, 8), 1);
    this->_entities[8][5][1] = std::make_shared<SnakeBodyEntity>(3, "b", std::make_pair(5, 8), 2);

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

    hud.push_back(std::make_shared<ScoreEntityHUD>(this->getScore(), std::make_pair(10, 15)));
    hud.push_back(std::make_shared<HighScoreEntityHUD>(this->getHighScore(), std::make_pair(10, 55)));

    std::size_t secondsElapsed = this->getTime();
    hud.push_back(std::make_shared<TimeEntityHUD>(secondsElapsed, std::make_pair(350, 35)));

    std::string appleString = std::to_string(this->_difficulty + 1);
    while (appleString.length() < 2)
        appleString = "0" + appleString;
    hud.push_back(std::make_shared<TextEntityHUD>("Apple " + appleString, std::make_pair(675, 35)));

    if (this->getIsStarted() == false)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Press any direction to start", std::make_pair(250, 850)));
    if (this->getGameState() == LOSE)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Game Over", std::make_pair(350, 850)));
    if (this->getGameState() == WIN)
        hud.push_back(std::make_shared<BigTextEntityHUD>("You Win", std::make_pair(350, 850)));
    return hud;
}

void SnakeGame::changeDifficulty()
{
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now();
    this->_difficulty += 1;
    if (_difficulty > 9)
        this->_difficulty = 0;

    this->_entities.resize(MAP_HEIGHT);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        this->_entities[y].resize(MAP_WIDTH);
        for (int x = 0; x < MAP_WIDTH; x++) {
            this->_entities[y][x].resize(MAP_LAYER);
        }
    }
    this->setLayerBackground();
    this->setLayerEntities();

    for (int i = 0; i < _difficulty; i++) {
        this->setLayerApple();
    }
}
