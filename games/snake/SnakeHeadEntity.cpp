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
#include "AppleEntity.hpp"
#include <iostream>
#include <bits/algorithmfwd.h>

const double SNAKE_DELTATIME = 0.10;

SnakeHeadEntity::SnakeHeadEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position)
{
    this->_inputDirection = {1, 0};
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
    this->_pendingBodyPartAddition = false;
    this->_lastTailPosition = {0, 0};
    this->_closeToApple = false;
}

void SnakeHeadEntity::setDirection(std::pair<int, int> direction, std::shared_ptr<IGameModule> gameModule)
{
    if (direction.first == 0 && direction.second == 0)
        return;
    gameModule->setIsStarted(true);
    if (this->_direction.first == direction.first * -1 && this->_direction.second == direction.second * -1)
        return;
    this->_inputDirection = direction;
}

void SnakeHeadEntity::moveEntities(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> pos1, std::pair<size_t, size_t> pos2)
{
    grid_t grid = gameModule->getEntities();

    grid[pos2.second][pos2.first][1] = grid[pos1.second][pos1.first][1];
    grid[pos1.second][pos1.first][1] = std::make_shared<VoidEntity>(grid[pos1.second][pos1.first][0]->getSpriteName(), 1, "", pos1);
    grid[pos2.second][pos2.first][1]->setPosition(pos2);
    gameModule->setEntities(grid);
}

float SnakeHeadEntity::getSpeedMultiplier(std::shared_ptr<IGameModule> gameModule) const
{
    size_t elapsedTime = gameModule->getTime();

    if (elapsedTime < 15)
        return 1.2f;
    if (elapsedTime < 30)
        return 1.1f;
    if (elapsedTime < 45)
        return 1.0f;
    if (elapsedTime < 60)
        return 0.9f;
    return 0.8f;
}

bool SnakeHeadEntity::lastTimePassed(std::shared_ptr<IGameModule> gameModule)
{
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - this->_lastTime;
    if (elapsedTime.count() < (SNAKE_DELTATIME * this->getSpeedMultiplier(gameModule)))
        return false;
    this->_lastTime = currentTime;
    return true;
}

bool SnakeHeadEntity::isCloseToApple(std::shared_ptr<IGameModule> gameModule) const
{
    grid_t grid = gameModule->getEntities();

    for (int y = _position.second - 2; y <= _position.second + 2; y++) {
        if (y < 0 || y >= grid.size())
            continue;

        for (int x = _position.first - 2; x <= _position.first + 2; x++) {
            if (x < 0 || x >= grid[y].size())
                continue;

            auto entity = grid[y][x][1];
            auto apple = std::dynamic_pointer_cast<AppleEntity>(entity);
            if (apple) {
                return true;
            }
        }
    }
    return false;
}

std::string SnakeHeadEntity::getSpriteName() const
{
    if (this->_assetsName.find(this->_direction) == this->_assetsName.end())
        return this->_spriteName;

    std::string apple = "";
    if (this->_closeToApple)
        apple = "_apple";

    return this->_assetsName.at(this->_direction).substr(0, this->_assetsName.at(this->_direction).find_last_of('.')) + apple + ".png";
}

std::vector<std::shared_ptr<SnakeBodyEntity>> SnakeHeadEntity::findAndSortBodyParts(const grid_t &grid) const
{
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

    return bodyParts;
}

void SnakeHeadEntity::moveBodyParts(std::shared_ptr<IGameModule> gameModule)
{
    grid_t grid = gameModule->getEntities();
    auto bodyParts = findAndSortBodyParts(grid);

    if (this->_previousPositions.size() < bodyParts.size() + 1) {
        return;
    }

    if (!bodyParts.empty()) {
        this->_lastTailPosition = bodyParts.back()->getPosition();
    }

    moveBodyPartsToNewPositions(gameModule, bodyParts);
}

void SnakeHeadEntity::moveBodyPartsToNewPositions(std::shared_ptr<IGameModule> gameModule,
    const std::vector<std::shared_ptr<SnakeBodyEntity>> &bodyParts)
{
    for (size_t i = 0; i < bodyParts.size(); i++) {
        auto bodyPart = bodyParts[i];
        auto currentPos = bodyPart->getPosition();
        auto newPos = this->_previousPositions[this->_previousPositions.size() - 2 - i];

        this->moveEntities(gameModule, currentPos, newPos);
    }
}

void SnakeHeadEntity::updateBodyPartDirections(std::shared_ptr<IGameModule> gameModule,
    const std::vector<std::shared_ptr<SnakeBodyEntity>> &bodyParts)
{
    grid_t grid = gameModule->getEntities();

    for (size_t i = 0; i < bodyParts.size(); i++) {
        auto bodyPart = std::dynamic_pointer_cast<SnakeBodyEntity>(bodyParts[i]);
        auto newPos = this->_previousPositions[this->_previousPositions.size() - 2 - i];

        std::pair<size_t, size_t> nextPos;
        std::pair<size_t, size_t> prevPos = {100, 100};

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

bool SnakeHeadEntity::checkCollisionWithBody(std::pair<size_t, size_t> nextPosition, std::shared_ptr<IGameModule> gameModule) const
{
    grid_t grid = gameModule->getEntities();
    auto entity = grid[nextPosition.second][nextPosition.first][1];
    auto bodyPart = std::dynamic_pointer_cast<SnakeBodyEntity>(entity);

    return bodyPart != nullptr;
}

gameState_t SnakeHeadEntity::appleCollision(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> nextPosition)
{
    grid_t grid = gameModule->getEntities();
    auto entity = grid[nextPosition.second][nextPosition.first][1];
    auto apple = std::dynamic_pointer_cast<AppleEntity>(entity);

    if (apple) {
        apple->onInteract(gameModule);
        this->addBodyPart(gameModule);
        return gameState_t::PLAYING;
    }

    return gameState_t::PLAYING;
}

size_t SnakeHeadEntity::getBodySize() const
{
    return this->_previousPositions.size() - 1;
}

void SnakeHeadEntity::addFirstBodyPart(std::shared_ptr<IGameModule> gameModule)
{
    grid_t grid = gameModule->getEntities();
    int dx = -this->_direction.first;
    int dy = -this->_direction.second;

    if (this->_previousPositions.size() < 1)
        this->_previousPositions.push_back(this->_position);

    std::pair<size_t, size_t> newPos = {
        this->_position.first + dx,
        this->_position.second + dy
    };

    if (this->isValidPosition(newPos, grid)) {
        auto newBodyPart = std::make_shared<SnakeBodyEntity>(3, "", newPos, 0);
        newBodyPart->updateDirection(newPos, this->_position, {100, 100});
        grid[newPos.second][newPos.first][1] = newBodyPart;
        gameModule->setEntities(grid);
        this->_previousPositions.insert(this->_previousPositions.begin(), newPos);
    }
}

void SnakeHeadEntity::addBodyPartToTail(std::shared_ptr<IGameModule> gameModule, size_t index,
    const std::pair<size_t, size_t> &lastBodyPos, const std::pair<size_t, size_t> &beforeLastPos)
{
    grid_t grid = gameModule->getEntities();
    int dx = lastBodyPos.first - beforeLastPos.first;
    int dy = lastBodyPos.second - beforeLastPos.second;

    std::pair<size_t, size_t> newPos = {
        lastBodyPos.first + dx,
        lastBodyPos.second + dy
    };

    if (this->isValidPosition(newPos, grid)) {
        auto newBodyPart = std::make_shared<SnakeBodyEntity>(3, "", newPos, index);
        newBodyPart->updateDirection(newPos, lastBodyPos, {0, 0});
        grid[newPos.second][newPos.first][1] = newBodyPart;
        gameModule->setEntities(grid);
        this->_previousPositions.insert(this->_previousPositions.begin(), newPos);

        while (this->_previousPositions.size() > index + 2) {
            this->_previousPositions.pop_back();
        }
    }
}

bool SnakeHeadEntity::isValidPosition(const std::pair<size_t, size_t> &pos, const grid_t &grid) const
{
    return pos.first < grid[0].size() && pos.second < grid.size() &&
           pos.first >= 0 && pos.second >= 0;
}

void SnakeHeadEntity::addBodyPart(std::shared_ptr<IGameModule> gameModule)
{
    this->_pendingBodyPartAddition = true;
}

void SnakeHeadEntity::addPendingBodyPart(std::shared_ptr<IGameModule> gameModule)
{
    if (!this->_pendingBodyPartAddition)
        return;

    grid_t grid = gameModule->getEntities();
    auto bodyParts = findAndSortBodyParts(grid);
    size_t index = bodyParts.empty() ? 0 : bodyParts.back()->getIndex() + 1;

    if (bodyParts.empty()) {
        int dx = -this->_direction.first;
        int dy = -this->_direction.second;
        std::pair<size_t, size_t> newPos = {
            this->_position.first + dx,
            this->_position.second + dy
        };

        if (this->isValidPosition(newPos, grid)) {
            auto newBodyPart = std::make_shared<SnakeBodyEntity>(3, "", newPos, 0);
            newBodyPart->updateDirection(newPos, this->_position, {100, 100});
            grid[newPos.second][newPos.first][1] = newBodyPart;
            gameModule->setEntities(grid);
            this->_previousPositions.insert(this->_previousPositions.begin(), newPos);
        }
    } else {
        if (this->isValidPosition(this->_lastTailPosition, grid)) {
            auto newBodyPart = std::make_shared<SnakeBodyEntity>(3, "", this->_lastTailPosition, index);

            std::pair<size_t, size_t> beforeTailPos;
            if (bodyParts.size() > 1)
                beforeTailPos = bodyParts[bodyParts.size() - 2]->getPosition();
            else
                beforeTailPos = this->_position;
            newBodyPart->updateDirection(this->_lastTailPosition, beforeTailPos, {100, 100});
            grid[this->_lastTailPosition.second][this->_lastTailPosition.first][1] = newBodyPart;
            gameModule->setEntities(grid);
            this->_previousPositions.insert(this->_previousPositions.begin(), this->_lastTailPosition);
        }
    }

    this->_pendingBodyPartAddition = false;
}

void SnakeHeadEntity::initializePreviousPositions(const std::vector<std::pair<size_t, size_t>>& positions)
{
    this->_previousPositions.clear();
    for (const auto& pos : positions) {
        this->_previousPositions.push_back(pos);
    }
}

void SnakeHeadEntity::ensurePreviousPositionsInitialized(std::shared_ptr<IGameModule> gameModule)
{
    if (this->_previousPositions.size() > 1)
        return;

    grid_t grid = gameModule->getEntities();
    auto bodyParts = findAndSortBodyParts(grid);

    if (!bodyParts.empty()) {
        this->_previousPositions.clear();
        for (size_t i = bodyParts.size(); i > 0; i--) {
            this->_previousPositions.push_back(bodyParts[i-1]->getPosition());
        }
        this->_previousPositions.push_back(this->_position);
    }
}

void SnakeHeadEntity::moveEntity(std::shared_ptr<IGameModule> gameModule, std::pair<int, int> direction)
{
    this->setDirection(direction, gameModule);
    this->ensurePreviousPositionsInitialized(gameModule);

    if (gameModule->getGameState() != gameState_t::PLAYING)
        return;
    if (!this->lastTimePassed(gameModule) || !gameModule->getIsStarted())
        return;
    this->_direction = this->_inputDirection;

    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> gridSize = gameModule->getGridSize();
    std::pair<size_t, size_t> nextPosition = {this->_position.first + this->_direction.first, this->_position.second + this->_direction.second};

    if (nextPosition.first >= gridSize.first || nextPosition.second >= gridSize.second
        || nextPosition.first < 0 || nextPosition.second < 0) {
        gameModule->setGameState(gameState_t::LOSE);
        return;
    }

    if (this->checkCollisionWithBody(nextPosition, gameModule)) {
        gameModule->setGameState(gameState_t::LOSE);
        return;
    }

    gameState_t state = this->appleCollision(gameModule, nextPosition);
    if (state != gameState_t::PLAYING)
        return;

    this->_previousPositions.push_back(nextPosition);
    while (this->_previousPositions.size() > this->getBodySize() + 2) {
        this->_previousPositions.erase(this->_previousPositions.begin());
    }

    this->moveEntities(gameModule, this->_position, nextPosition);
    this->_closeToApple = this->isCloseToApple(gameModule);
    this->moveBodyParts(gameModule);
    this->addPendingBodyPart(gameModule);
    this->updateBodyPartDirections(gameModule, findAndSortBodyParts(gameModule->getEntities()));
}
