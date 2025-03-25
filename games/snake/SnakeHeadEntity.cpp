/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeHeadEntity
*/

#include "SnakeHeadEntity.hpp"
#include "VoidEntity.hpp"
#include "IGameModule.hpp"
#include "SnakeGame.hpp"
#include "SnakeBodyEntity.hpp"
#include <iostream>

SnakeHeadEntity::SnakeHeadEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position)
{
    this->_direction = {1, 0};
    this->_spriteName = "assets/snake/head_right.png";
    this->_assetsName = {
        {{1, 0}, "assets/snake/head_right.png"},
        {{-1, 0}, "assets/snake/head_left.png"},
        {{0, 1}, "assets/snake/head_down.png"},
        {{0, -1}, "assets/snake/head_up.png"},
    };
    this->_color = color;
    this->_text = text;
    this->_position = position;
    this->_isMovable = true;
    this->_isControlable = true;
    this->_hasCollisions = true;
    this->_previousPositions.push_back(position);
    this->_lastTime = std::chrono::steady_clock::now();
}

void SnakeHeadEntity::setDirection(std::pair<int, int> direction)
{
    if (direction.first == 0 && direction.second == 0)
        return;
    if (this->_direction.first == direction.first * -1 && this->_direction.second == direction.second * -1)
        return;
    this->_direction = direction;
}

void SnakeHeadEntity::moveEntities(IGameModule &gameModule, std::pair<size_t, size_t> pos1, std::pair<size_t, size_t> pos2)
{
    grid_t grid = gameModule.getEntities();

    grid[pos2.second][pos2.first][1] = grid[pos1.second][pos1.first][1];
    grid[pos1.second][pos1.first][1] = std::make_shared<VoidEntity>(grid[pos1.second][pos1.first][0].get()->getSpriteName(), 0, "", pos1);
    grid[pos2.second][pos2.first][1].get()->setPosition(pos2);
    gameModule.setEntities(grid);
}

bool SnakeHeadEntity::lastTimePassed()
{
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - this->_lastTime;
    if (elapsedTime.count() < 0.15)
        return false;
    this->_lastTime = currentTime;
    return true;
}

std::string SnakeHeadEntity::getSpriteName() const
{
    if (this->_assetsName.find(this->_direction) == this->_assetsName.end())
        return this->_spriteName;
    return this->_assetsName.at(this->_direction);
}

void SnakeHeadEntity::moveBodyParts(IGameModule &gameModule)
{
    grid_t grid = gameModule.getEntities();
    std::vector<std::shared_ptr<AEntity>> bodyParts;

    // Find
    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            auto entity = grid[y][x][1];
            auto bodyPart = std::dynamic_pointer_cast<SnakeBodyEntity>(entity);
            if (bodyPart) {
                bodyParts.push_back(bodyPart);
            }
        }
    }

    // Sort
    std::sort(bodyParts.begin(), bodyParts.end(),
              [](const std::shared_ptr<AEntity>& a, const std::shared_ptr<AEntity>& b) {
                  return std::dynamic_pointer_cast<SnakeBodyEntity>(a)->getIndex() <
                         std::dynamic_pointer_cast<SnakeBodyEntity>(b)->getIndex();
              });

    // Check if we have enough positions stored
    if (this->_previousPositions.size() < bodyParts.size() + 1) {
        return;
    }

    // Move
    for (size_t i = 0; i < bodyParts.size(); i++) {
        auto bodyPart = std::dynamic_pointer_cast<SnakeBodyEntity>(bodyParts[i]);
        auto currentPos = bodyPart->getPosition();
        auto newPos = this->_previousPositions[this->_previousPositions.size() - 2 - i];

        std::pair<size_t, size_t> nextPos;
        std::pair<size_t, size_t> prevPos = {0, 0};

        if (i > 0) {
            nextPos = bodyParts[i-1]->getPosition();
        } else {
            nextPos = this->_position;
        }

        if (i < bodyParts.size() - 1)
            prevPos = bodyParts[i+1]->getPosition();

        this->moveEntities(gameModule, currentPos, newPos);
        grid = gameModule.getEntities();
    }

    // Actualise Directions
    for (size_t i = 0; i < bodyParts.size(); i++) {
        auto bodyPart = std::dynamic_pointer_cast<SnakeBodyEntity>(bodyParts[i]);
        auto currentPos = bodyPart->getPosition();
        auto newPos = this->_previousPositions[this->_previousPositions.size() - 2 - i];

        std::pair<size_t, size_t> nextPos;
        std::pair<size_t, size_t> prevPos = {0, 0};

        if (i > 0) {
            nextPos = bodyParts[i-1]->getPosition();
        } else {
            nextPos = this->_position;
        }

        if (i < bodyParts.size() - 1)
            prevPos = bodyParts[i+1]->getPosition();

        bodyPart->updateDirection(newPos, nextPos, prevPos);
    }
}

bool SnakeHeadEntity::checkCollisionWithBody(std::pair<size_t, size_t> nextPosition, IGameModule &gameModule) const
{
    grid_t grid = gameModule.getEntities();
    auto entity = grid[nextPosition.second][nextPosition.first][1];
    auto bodyPart = std::dynamic_pointer_cast<SnakeBodyEntity>(entity);

    return bodyPart != nullptr;
}

size_t SnakeHeadEntity::getBodySize() const
{
    return this->_previousPositions.size() - 1;
}

void SnakeHeadEntity::addBodyPart(IGameModule &gameModule)
{
    grid_t grid = gameModule.getEntities();
    size_t index = 0;
    std::pair<size_t, size_t> tailPosition;

    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            auto entity = grid[y][x][1];
            auto bodyPart = std::dynamic_pointer_cast<SnakeBodyEntity>(entity);
            if (bodyPart) {
                if (bodyPart->getIndex() >= index) {
                    index = bodyPart->getIndex() + 1;
                    tailPosition = bodyPart->getPosition();
                }
            }
        }
    }

    if (index == 0) {
        int dx = -this->_direction.first;
        int dy = -this->_direction.second;

        if (this->_previousPositions.size() < 1) {
            this->_previousPositions.push_back(this->_position);
        }

        std::pair<size_t, size_t> newPos = {
            this->_position.first + dx,
            this->_position.second + dy
        };

        if (newPos.first < grid[0].size() && newPos.second < grid.size()) {
            auto newBodyPart = std::make_shared<SnakeBodyEntity>(1, "=", newPos, 0);
            newBodyPart->updateDirection(newPos, this->_position, {0, 0});
            grid[newPos.second][newPos.first][1] = newBodyPart;
            gameModule.setEntities(grid);
            this->_previousPositions.insert(this->_previousPositions.begin(), newPos);
        }
    } else {
        std::pair<size_t, size_t> lastBodyPos = tailPosition;
        std::pair<size_t, size_t> beforeLastPos;

        std::vector<std::shared_ptr<SnakeBodyEntity>> bodyParts;
        for (size_t y = 0; y < grid.size(); y++) {
            for (size_t x = 0; x < grid[y].size(); x++) {
                auto entity = grid[y][x][1];
                auto bodyPart = std::dynamic_pointer_cast<SnakeBodyEntity>(entity);
                if (bodyPart) {
                    bodyParts.push_back(bodyPart);
                }
            }
        }

        std::sort(bodyParts.begin(), bodyParts.end(),
            [](const std::shared_ptr<SnakeBodyEntity>& a, const std::shared_ptr<SnakeBodyEntity>& b) {
                return a->getIndex() < b->getIndex();
            });

        if (bodyParts.size() >= 2) {
            lastBodyPos = bodyParts.back()->getPosition();
            beforeLastPos = bodyParts[bodyParts.size() - 2]->getPosition();
        } else if (bodyParts.size() == 1) {
            lastBodyPos = bodyParts[0]->getPosition();
            beforeLastPos = this->_position;
        } else {
            return;
        }

        int dx = lastBodyPos.first - beforeLastPos.first;
        int dy = lastBodyPos.second - beforeLastPos.second;

        std::pair<size_t, size_t> newPos = {
            lastBodyPos.first + dx,
            lastBodyPos.second + dy
        };

        if (newPos.first < grid[0].size() && newPos.second < grid.size() &&
            newPos.first >= 0 && newPos.second >= 0) {
            auto newBodyPart = std::make_shared<SnakeBodyEntity>(1, "=", newPos, index);
            newBodyPart->updateDirection(newPos, lastBodyPos, {0, 0});
            grid[newPos.second][newPos.first][1] = newBodyPart;
            gameModule.setEntities(grid);
            this->_previousPositions.insert(this->_previousPositions.begin(), newPos);

            while (this->_previousPositions.size() > index + 2) {
                this->_previousPositions.pop_back();
            }
        }
    }
}

gameState_t SnakeHeadEntity::moveEntity(IGameModule &gameModule, std::pair<int, int> direction)
{
    this->setDirection(direction);
    if (!this->lastTimePassed())
        return gameState_t::PLAYING;

    grid_t grid = gameModule.getEntities();
    std::pair<size_t, size_t> gridSize = gameModule.getGridSize();
    std::pair<size_t, size_t> nextPosition = {this->_position.first + this->_direction.first, this->_position.second + this->_direction.second};

    if (nextPosition.first >= gridSize.first || nextPosition.second >= gridSize.second
        || nextPosition.first < 0 || nextPosition.second < 0)
        return gameState_t::LOSE;

    if (this->checkCollisionWithBody(nextPosition, gameModule))
        return gameState_t::LOSE;

    this->_previousPositions.push_back(nextPosition);
    while (this->_previousPositions.size() > this->getBodySize() + 2) {
        this->_previousPositions.erase(this->_previousPositions.begin());
    }

    this->moveEntities(gameModule, this->_position, nextPosition);
    this->moveBodyParts(gameModule);

    return gameState_t::PLAYING;
}
