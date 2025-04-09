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
    if (this->_wasGettingChased)
        return this->_spriteChasedName;
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

void GhostEntity::setMultiplier(float multiplier)
{
    this->_multiplier = multiplier;
}

float GhostEntity::getMultiplier() const
{
    return this->_multiplier;
}

void GhostEntity::setWaitingTime(std::size_t waitingTime)
{
    this->_waitingTime = waitingTime;
    this->_waitingPoint = std::chrono::steady_clock::now();
}

void GhostEntity::updateWaitingTime(std::shared_ptr<IGameModule> gameModule)
{
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedSinceChased = currentTime - this->_chasedTime;


    if (this->_state == CHASED && !this->getWasGettingChased()) {
        this->_state = CHASING;
        this->setSpeedTime(0.25f);
    }
    if (this->getWasGettingChased() && (elapsedSinceChased.count() > 10))
        this->_wasGettingChased = false;

    if (this->_waitingTime == 0)
        return;

    std::chrono::duration<double> elapsedTime = currentTime - this->_waitingPoint;

    if (elapsedTime.count() < this->_waitingTime)
        return;
    this->_waitingTime = 0;
    this->_waitingPoint = currentTime;

    if (this->_state == WAITING) {
        if (!this->moveToClosestFreeCell(gameModule, this->_begPoint)) {
            this->setWaitingTime(1);
            return;
        };
        this->_state = CHASING;
        this->setSpeedTime(0.25f);
        if (this->_wasGettingChased) {
            this->_state = CHASED;
            this->setSpeedTime(0.5f);
            this->setWaitingTime(10 - elapsedSinceChased.count());
            if (this->_waitingTime < 0 || this->_waitingTime > 20)
                this->_waitingTime = 0;
        }
    }
    else if (this->_state == CHASED) {
        this->_state = CHASING;
        this->setSpeedTime(0.25f);
    }
}

bool GhostEntity::moveToClosestFreeCell(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos)
{
    grid_t grid = gameModule->getEntities();

    if (grid[newPos.second][newPos.first][2] != nullptr)
        return false;
    if (std::dynamic_pointer_cast<WallEntity>(grid[newPos.second][newPos.first][1]))
        return false;

    grid[newPos.second][newPos.first][2] = grid[_position.second][_position.first][2];
    grid[_position.second][_position.first][2] = nullptr;
    this->_position = std::make_pair(newPos.first, newPos.second);
    gameModule->setEntities(grid);

    return true;
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

std::size_t GhostEntity::getWaitingTime() const
{
    return this->_waitingTime;
}

void GhostEntity::setWasGettingChased(bool wasGettingChased)
{
    this->_wasGettingChased = wasGettingChased;
    this->_chasedTime = std::chrono::steady_clock::now();
}

bool GhostEntity::getWasGettingChased() const
{
    return this->_wasGettingChased;
}
