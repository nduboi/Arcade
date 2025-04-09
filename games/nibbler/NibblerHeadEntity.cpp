/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** NibblerHeadEntity
*/

#include "NibblerHeadEntity.hpp"
#include "VoidEntity.hpp"
#include "IGameModule.hpp"
#include "NibblerGame.hpp"
#include "NibblerTailEntity.hpp"
#include "FoodEntity.hpp"
#include "WallEntity.hpp"
#include <iostream>
#include <bits/algorithmfwd.h>

const double NIBBLER_DELTATIME = 0.08;
const double NIBBLER_PAUSE_TIME = 0.3;

NibblerHeadEntity::NibblerHeadEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position)
{
    this->_inputDirection = {1, 0};
    this->_direction = {1, 0};
    this->_spriteName = "assets/nibbler/Nibbler_head_right.png";
    this->_assetsName = {
        {{1, 0}, "assets/nibbler/Nibbler_head_right.png"},
        {{-1, 0}, "assets/nibbler/Nibbler_head_left.png"},
        {{0, 1}, "assets/nibbler/Nibbler_head_bottom.png"},
        {{0, -1}, "assets/nibbler/Nibbler_head_top.png"},
    };
    this->_color = color;
    this->_text = text;
    this->_position = position;
    this->_isMovable = true;
    this->_isControlable = true;
    this->_hasCollisions = true;
    this->_previousPositions.push_back(position);
    this->_lastTime = std::chrono::steady_clock::now();
    this->_pauseUntil = std::chrono::steady_clock::now();
    this->_pendingBodyPartAddition = false;
    this->_lastTailPosition = {0, 0};
    this->_isPaused = false;
}

void NibblerHeadEntity::setDirection(std::pair<int, int> direction, std::shared_ptr<IGameModule> gameModule)
{
    if (direction.first == 0 && direction.second == 0)
        return;
    gameModule->setIsStarted(true);

    if (this->_direction.first != 0 && direction.first != 0 && 
        this->_direction.first + direction.first == 0)
        return;
    if (this->_direction.second != 0 && direction.second != 0 && 
        this->_direction.second + direction.second == 0)
        return;

    this->_inputDirection = direction;
}

void NibblerHeadEntity::moveEntities(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> pos1, std::pair<size_t, size_t> pos2)
{
    grid_t grid = gameModule->getEntities();

    grid[pos2.second][pos2.first][1] = grid[pos1.second][pos1.first][1];
    grid[pos1.second][pos1.first][1] = std::make_shared<VoidEntity>(grid[pos1.second][pos1.first][0]->getSpriteName(), 1, "", pos1);
    grid[pos2.second][pos2.first][1]->setPosition(pos2);
    gameModule->setEntities(grid);
}

bool NibblerHeadEntity::lastTimePassed()
{
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();

    if (this->_isPaused) {
        if (currentTime < this->_pauseUntil)
            return false;
        this->_isPaused = false;
    }

    std::chrono::duration<double> elapsedTime = currentTime - this->_lastTime;
    if (elapsedTime.count() < NIBBLER_DELTATIME)
        return false;
    this->_lastTime = currentTime;
    return true;
}

bool NibblerHeadEntity::isAtIntersection(std::shared_ptr<IGameModule> gameModule)
{
    auto nibblerGame = std::dynamic_pointer_cast<NibblerGame>(gameModule);
    if (!nibblerGame)
        return false;

    auto validDirections = nibblerGame->getValidDirections(this->_position);
    return validDirections.size() > 2;
}

std::string NibblerHeadEntity::getSpriteName() const
{
    if (this->_assetsName.find(this->_direction) == this->_assetsName.end())
        return this->_spriteName;
    return this->_assetsName.at(this->_direction);
}

std::vector<std::shared_ptr<NibblerTailEntity>> NibblerHeadEntity::findAndSortBodyParts(const grid_t &grid) const
{
    std::vector<std::shared_ptr<NibblerTailEntity>> bodyParts;

    for (size_t y = 0; y < grid.size(); y++) {
        for (size_t x = 0; x < grid[y].size(); x++) {
            auto entity = grid[y][x][1];
            auto bodyPart = std::dynamic_pointer_cast<NibblerTailEntity>(entity);
            if (bodyPart) {
                bodyParts.push_back(bodyPart);
            }
        }
    }

    std::sort(bodyParts.begin(), bodyParts.end(),
              [](const std::shared_ptr<NibblerTailEntity>& a, const std::shared_ptr<NibblerTailEntity>& b) {
                  return a->getIndex() < b->getIndex();
              });

    return bodyParts;
}

void NibblerHeadEntity::moveBodyParts(std::shared_ptr<IGameModule> gameModule)
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

void NibblerHeadEntity::moveBodyPartsToNewPositions(std::shared_ptr<IGameModule> gameModule,
    const std::vector<std::shared_ptr<NibblerTailEntity>> &bodyParts)
{
    for (size_t i = 0; i < bodyParts.size(); i++) {
        auto bodyPart = bodyParts[i];
        auto currentPos = bodyPart->getPosition();
        auto newPos = this->_previousPositions[this->_previousPositions.size() - 2 - i];

        this->moveEntities(gameModule, currentPos, newPos);
    }
}

void NibblerHeadEntity::updateBodyPartDirections(std::shared_ptr<IGameModule> gameModule,
    const std::vector<std::shared_ptr<NibblerTailEntity>> &bodyParts)
{
    grid_t grid = gameModule->getEntities();

    for (size_t i = 0; i < bodyParts.size(); i++) {
        auto bodyPart = std::dynamic_pointer_cast<NibblerTailEntity>(bodyParts[i]);
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

bool NibblerHeadEntity::checkCollisionWithBody(std::pair<size_t, size_t> nextPosition, std::shared_ptr<IGameModule> gameModule) const
{
    grid_t grid = gameModule->getEntities();
    auto entity = grid[nextPosition.second][nextPosition.first][1];
    auto bodyPart = std::dynamic_pointer_cast<NibblerTailEntity>(entity);

    return bodyPart != nullptr;
}

bool NibblerHeadEntity::checkCollisionWithWall(std::pair<size_t, size_t> nextPosition, std::shared_ptr<IGameModule> gameModule) const
{
    grid_t grid = gameModule->getEntities();
    auto entity = grid[nextPosition.second][nextPosition.first][1];
    auto wall = std::dynamic_pointer_cast<WallEntity>(entity);

    return wall != nullptr;
}

gameState_t NibblerHeadEntity::foodCollision(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> nextPosition)
{
    grid_t grid = gameModule->getEntities();
    auto entity = grid[nextPosition.second][nextPosition.first][1];
    auto food = std::dynamic_pointer_cast<FoodEntity>(entity);

    if (food) {
        food->onInteract(gameModule);
        this->addBodyPart(gameModule);
        return gameState_t::PLAYING;
    }

    return gameState_t::PLAYING;
}

size_t NibblerHeadEntity::getBodySize() const
{
    return this->_previousPositions.size() - 1;
}

void NibblerHeadEntity::addFirstBodyPart(std::shared_ptr<IGameModule> gameModule)
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
        auto newBodyPart = std::make_shared<NibblerTailEntity>(3, "", newPos, 0);
        newBodyPart->updateDirection(newPos, this->_position, {100, 100});
        grid[newPos.second][newPos.first][1] = newBodyPart;
        gameModule->setEntities(grid);
        this->_previousPositions.insert(this->_previousPositions.begin(), newPos);
    }
}

void NibblerHeadEntity::addBodyPartToTail(std::shared_ptr<IGameModule> gameModule, size_t index,
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
        auto newBodyPart = std::make_shared<NibblerTailEntity>(3, "", newPos, index);
        newBodyPart->updateDirection(newPos, lastBodyPos, {0, 0});
        grid[newPos.second][newPos.first][1] = newBodyPart;
        gameModule->setEntities(grid);
        this->_previousPositions.insert(this->_previousPositions.begin(), newPos);

        while (this->_previousPositions.size() > index + 2) {
            this->_previousPositions.pop_back();
        }
    }
}

bool NibblerHeadEntity::isValidPosition(const std::pair<size_t, size_t> &pos, const grid_t &grid) const
{
    if (pos.first >= grid[0].size() || pos.second >= grid.size() ||
        pos.first < 0 || pos.second < 0)
        return false;

    auto entity = grid[pos.second][pos.first][1];
    auto bodyPart = std::dynamic_pointer_cast<NibblerTailEntity>(entity);

    if (bodyPart)
        return false;

    return true;
}

void NibblerHeadEntity::addBodyPart(std::shared_ptr<IGameModule> gameModule)
{
    this->_pendingBodyPartAddition = true;
}

void NibblerHeadEntity::addPendingBodyPart(std::shared_ptr<IGameModule> gameModule)
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
            auto newBodyPart = std::make_shared<NibblerTailEntity>(3, "", newPos, 0);
            newBodyPart->updateDirection(newPos, this->_position, {100, 100});
            grid[newPos.second][newPos.first][1] = newBodyPart;
            gameModule->setEntities(grid);
            this->_previousPositions.insert(this->_previousPositions.begin(), newPos);
        }
    } else {
        if (this->isValidPosition(this->_lastTailPosition, grid)) {
            auto newBodyPart = std::make_shared<NibblerTailEntity>(3, "", this->_lastTailPosition, index);

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

void NibblerHeadEntity::initializePreviousPositions(const std::vector<std::pair<size_t, size_t>>& positions)
{
    this->_previousPositions.clear();
    for (const auto& pos : positions) {
        this->_previousPositions.push_back(pos);
    }
}

void NibblerHeadEntity::ensurePreviousPositionsInitialized(std::shared_ptr<IGameModule> gameModule)
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

void NibblerHeadEntity::moveEntity(std::shared_ptr<IGameModule> gameModule, std::pair<int, int> direction)
{
    this->setDirection(direction, gameModule);
    this->ensurePreviousPositionsInitialized(gameModule);

    if (gameModule->getGameState() != gameState_t::PLAYING)
        return;
    if (!this->lastTimePassed() || !gameModule->getIsStarted())
        return;

    if (isAtIntersection(gameModule) && !this->_isPaused) {
        if (this->_inputDirection != this->_direction) {
            this->_isPaused = true;
            this->_pauseUntil = std::chrono::steady_clock::now() +
                               std::chrono::milliseconds(static_cast<int>(NIBBLER_PAUSE_TIME * 1000));
            return;
        }
    }

    this->_direction = this->_inputDirection;

    std::pair<size_t, size_t> nextPosition = {
        this->_position.first + this->_direction.first,
        this->_position.second + this->_direction.second
    };

    if (this->checkCollisionWithWall(nextPosition, gameModule)) {
        gameModule->setGameState(gameState_t::LOSE);
        return;
    }

    std::pair<size_t, size_t> gridSize = gameModule->getGridSize();
    if (nextPosition.first >= gridSize.first || nextPosition.second >= gridSize.second
        || nextPosition.first < 0 || nextPosition.second < 0) {
        gameModule->setGameState(gameState_t::LOSE);
        return;
    }

    if (this->checkCollisionWithBody(nextPosition, gameModule)) {
        gameModule->setGameState(gameState_t::LOSE);
        return;
    }

    gameState_t state = this->foodCollision(gameModule, nextPosition);
    if (state != gameState_t::PLAYING)
        return;

    this->_previousPositions.push_back(nextPosition);
    while (this->_previousPositions.size() > this->getBodySize() + 2) {
        this->_previousPositions.erase(this->_previousPositions.begin());
    }

    this->moveEntities(gameModule, this->_position, nextPosition);
    this->moveBodyParts(gameModule);
    this->addPendingBodyPart(gameModule);
    this->updateBodyPartDirections(gameModule, findAndSortBodyParts(gameModule->getEntities()));
}
