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

const int MAP_HEIGHT = 17;
const int MAP_WIDTH = 17;
const int MAP_LAYER = 2;

SnakeGame::SnakeGame()
{
    this->_highScore = 0;
    this->_score = 0;

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
            this->_entities[y][x][1] = std::make_shared<VoidEntity>(this->_entities[y][x][0].get()->getSpriteName(), 0, "", std::make_pair(x, y));
        }
    }

    // Create snake head at position (8,8)
    this->_entities[8][8][1] = std::make_shared<SnakeHeadEntity>(1, "O", std::make_pair(8, 8));

    auto head = std::dynamic_pointer_cast<SnakeHeadEntity>(this->_entities[8][8][1]);
    if (head) {
        head->addBodyPart(*this);

        head->moveEntity(*this, {1, 0});
        head->moveEntity(*this, {1, 0});

        head->addBodyPart(*this);
        head->addBodyPart(*this);
    }
}
