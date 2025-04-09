/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** GhostEntity
*/

#include "GhostEntity.hpp"

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

void GhostEntity::updateWaitingTime()
{
    if (this->_waitingTime == 0)
        return;

    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - this->_waitingPoint;

    if (elapsedTime.count() < this->_waitingTime)
        return;
    this->_waitingTime = 0;
    this->_waitingPoint = currentTime;

    if (this->_state == WAITING)
        this->_state = CHASING;
    else if (this->_state == CHASED) {
        this->_state = CHASING;
        this->setSpeedTime(0.15f);
    }
}
