/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** RedGhost
*/

#include "RedGhost.hpp"

RedGhost::RedGhost(std::pair<size_t, size_t> spawnPosition)
{
    this->_spriteName = "assets/pacman/ghosts/blinky.png";
    this->_spriteChasedName = "assets/pacman/ghosts/blue_ghost.png";
    this->_spriteEyeName = "assets/pacman/ghosts/eyes.png";

    this->_spawnPosition = spawnPosition;
    this->_position = spawnPosition;
    this->_state = GhostEntity::WAITING;

    this->_isMovable = true;
    this->_isControlable = false;
    this->_hasCollisions = true;

    this->_color = 2;
    this->_text = "";

    this->_waitingTime = 10;
    this->_waitingPoint = std::chrono::steady_clock::now();

    this->_speedTime = 0.15f;
    this->_lastMove = std::chrono::steady_clock::now();
}

void RedGhost::moveEntity(std::shared_ptr<IGameModule> gameModule)
{
    this->updateWaitingTime();
}
