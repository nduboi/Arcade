/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** GhostEntity
*/

#include "GhostEntity.hpp"
#include "WallEntity.hpp"

std::string GhostEntity::getSpriteName() const
{
    if (this->_state == CHASED)
        return this->_spriteChasedName;
    if (this->_state == TRAVELING)
        return this->_spriteEyeName;
    return this->_spriteName;
}

void GhostEntity::setState(GhostState state)
{
    this->_state = state;
}

GhostEntity::GhostState GhostEntity::getState() const
{
    return this->_state;
}

void GhostEntity::setSpawnPosition(std::pair<size_t, size_t> spawnPosition)
{
    this->_spawnPosition = spawnPosition;
}

std::pair<size_t, size_t> GhostEntity::getSpawnPosition() const
{
    return this->_spawnPosition;
}

void GhostEntity::setSpeedTime(float speedTime)
{
    this->_speedTime = speedTime;
}

float GhostEntity::getSpeedTime() const
{
    return this->_speedTime;
}

void GhostEntity::setWaitingTime(std::size_t waitingTime)
{
    this->_waitingTime = waitingTime;
    this->_waitingPoint = std::chrono::steady_clock::now();
}

void GhostEntity::updateWaitingTime(std::shared_ptr<IGameModule> gameModule)
{
    if (this->_waitingTime == 0)
        return;

    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - this->_waitingPoint;

    if (elapsedTime.count() < this->_waitingTime)
        return;
    this->_waitingTime = 0;
    this->_waitingPoint = currentTime;

    if (this->_state == WAITING) {
        this->_state = CHASING;
        this->moveToClosestFreeCell(gameModule, this->_begPoint);
        this->setSpeedTime(0.25f);
    }
    else if (this->_state == CHASED) {
        this->_state = CHASING;
        this->setSpeedTime(0.25f);
    }
}

void GhostEntity::moveToClosestFreeCell(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos)
{
    grid_t grid = gameModule->getEntities();

    for (int y = newPos.second; y >= 0; y--) {
        for (int x = newPos.first; x >= 0; x--) {
            if ((y == 14 || y == 15) && (x == 11 || x == 12 || x == 13))
                continue;

            if (grid[y][x][1] == nullptr)
                continue;
            if (grid[y][x][2] != nullptr)
                continue;


            if (std::dynamic_pointer_cast<WallEntity>(grid[y][x][1]) != nullptr)
                continue;

            grid[y][x][2] = grid[_position.second][_position.first][2];
            grid[_position.second][_position.first][2] = nullptr;
            this->_position = std::make_pair(x, y);
            gameModule->setEntities(grid);

            return;
        }
    }
}

void GhostEntity::onInteract(std::shared_ptr<IGameModule> gameModule)
{
    if (this->_state == CHASING) {
        gameModule->setGameState(gameState_t::LOSE);
        return;
    }

    if (this->_state == CHASED) {
        gameModule->setScore(gameModule->getScore() + 200);
        this->_state = TRAVELING;
        this->setSpeedTime(0.15f);
    }
}

std::shared_ptr<IEntity> GhostEntity::getPacman()
{
    return this->_pacman;
}
