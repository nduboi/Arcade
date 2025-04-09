/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** RedGhost
*/

#include "RedGhost.hpp"
#include "WallEntity.hpp"

#include <iostream>
#include <queue>
#include <map>

RedGhost::RedGhost(std::pair<size_t, size_t> spawnPosition, std::shared_ptr<IEntity> pacman, float multi)
{
    this->_spriteName = "assets/pacman/ghosts/blinky.png";
    this->_spriteChasedName = "assets/pacman/ghosts/blue_ghost.png";
    this->_spriteEyeName = "assets/pacman/ghosts/eyes.png";

    this->_spawnPosition = spawnPosition;
    this->_position = spawnPosition;
    this->_begPoint = std::make_pair(12, 9);
    this->_state = GhostEntity::WAITING;

    this->_isMovable = true;
    this->_isControlable = false;
    this->_hasCollisions = true;

    this->_color = 2;
    this->_text = "";

    this->_waitingTime = 10;
    this->_waitingPoint = std::chrono::steady_clock::now();
    this->_wasGettingChased = false;
    this->_chasedTime = std::chrono::steady_clock::now();

    this->_speedTime = 0.25f;
    this->_lastMove = std::chrono::steady_clock::now();

    this->_pacman = pacman;
    this->_multiplier = multi;
}

void RedGhost::checkPacmanCollision(std::shared_ptr<IGameModule> gameModule)
{
    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> pacmanPos = this->_pacman->getPosition();

    if (this->_position == pacmanPos) {
        if (this->_state == GhostEntity::CHASING) {
            gameModule->setGameState(gameState_t::LOSE);
            return;
        }
        if (this->_state == GhostEntity::CHASED) {
            gameModule->setScore(gameModule->getScore() + 200);
            this->_state = GhostEntity::TRAVELING;
            this->setSpeedTime(0.15f);
        }
    }
}

void RedGhost::moveEntity(std::shared_ptr<IGameModule> gameModule)
{
    this->updateWaitingTime(gameModule);

    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - this->_lastMove;
    if (elapsedTime.count() < (this->_speedTime) * this->_multiplier)
        return;
    this->_lastMove = currentTime;

    if (gameModule->getIsStarted() == false || gameModule->getGameState() != gameState_t::PLAYING
        || this->getState() == GhostEntity::WAITING)
        return;

    if (this->getState() == GhostEntity::CHASED)
        this->runAway(gameModule);
    if (this->getState() == GhostEntity::CHASING)
        this->moveToPacman(gameModule);
    if (this->getState() == GhostEntity::TRAVELING)
        this->moveToSpawn(gameModule);
    checkPacmanCollision(gameModule);
}

void RedGhost::moveTocell(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos)
{
    grid_t grid = gameModule->getEntities();

    if (newPos == this->_position)
        return;
    grid[newPos.second][newPos.first][2] = grid[this->_position.second][this->_position.first][2];
    grid[this->_position.second][this->_position.first][2] =  nullptr;
    if (grid[newPos.second][newPos.first][2] == nullptr)
        return;
    grid[newPos.second][newPos.first][2]->setPosition(newPos);
    gameModule->setEntities(grid);
}

void RedGhost::moveToSpawn(std::shared_ptr<IGameModule> gameModule)
{
    if (this->_position.first == this->_begPoint.first &&
        this->_position.second == this->_begPoint.second) {
        std::pair<size_t, size_t> newPos = this->_spawnPosition;
        this->moveTocell(gameModule, newPos);
        this->setState(GhostEntity::WAITING);
        this->setSpeedTime(0.25f);
        return;
    }

    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> size = gameModule->getGridSize();
    std::vector<std::pair<size_t, size_t>> freeCells;

    freeCells.push_back({this->_position.first, this->_position.second - 1});
    freeCells.push_back({this->_position.first, this->_position.second + 1});
    freeCells.push_back({this->_position.first - 1, this->_position.second});
    freeCells.push_back({this->_position.first + 1, this->_position.second});

    for (auto it = freeCells.begin(); it != freeCells.end();) {
        if (it->first >= size.first || it->second >= size.second || it->first < 0 || it->second < 0) {
            it = freeCells.erase(it);
            continue;
        }
        if (grid[it->second][it->first][2] != nullptr) {
            it = freeCells.erase(it);
            continue;
        }
        ++it;
    }

    if (freeCells.empty())
        return;

    std::pair<size_t, size_t> closestCell = freeCells[0];
    int minDistance = calculateManhattanDistance(closestCell, this->_begPoint);

    for (auto it = freeCells.begin(); it != freeCells.end(); it++) {
        int distance = calculateManhattanDistance(*it, this->_begPoint);
        if (distance < minDistance) {
            minDistance = distance;
            closestCell = *it;
        }
    }

    this->moveTocell(gameModule, closestCell);
}

void RedGhost::moveToPacman(std::shared_ptr<IGameModule> gameModule)
{
    std::pair<size_t, size_t> pacmanPos = this->_pacman->getPosition();
    std::pair<size_t, size_t> nextMove = findBestPathToTarget(gameModule, pacmanPos, true);

    if (nextMove.first != SIZE_MAX && nextMove.second != SIZE_MAX)
        this->moveTocell(gameModule, nextMove);
}

void RedGhost::runAway(std::shared_ptr<IGameModule> gameModule)
{
    std::pair<size_t, size_t> pacmanPos = this->_pacman->getPosition();
    std::pair<size_t, size_t> nextMove = findBestPathToTarget(gameModule, pacmanPos, false);

    if (nextMove.first != SIZE_MAX && nextMove.second != SIZE_MAX)
        this->moveTocell(gameModule, nextMove);
}

std::pair<size_t, size_t> RedGhost::findBestPathToTarget(std::shared_ptr<IGameModule> gameModule,
                                                         const std::pair<size_t, size_t>& target, bool moveTowards)
{
    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> size = gameModule->getGridSize();

    std::queue<std::pair<size_t, size_t>> queue;
    std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> parent;
    std::map<std::pair<size_t, size_t>, int> distances;
    const int MAX_DEPTH = 8;

    queue.push(this->_position);
    parent[this->_position] = {SIZE_MAX, SIZE_MAX};
    distances[this->_position] = 0;

    const std::vector<std::pair<int, int>> directions = {
        {0, -1},  // Up
        {0, 1},   // Down
        {-1, 0},  // Left
        {1, 0}    // Right
    };

    std::pair<size_t, size_t> bestCell = {SIZE_MAX, SIZE_MAX};
    int bestScore = moveTowards ? INT_MAX : -1;

    while (!queue.empty()) {
        std::pair<size_t, size_t> current = queue.front();
        queue.pop();
        if (distances[current] >= MAX_DEPTH)
            continue;
        int distanceToTarget = calculateManhattanDistance(current, target);

        if (!moveTowards) {
            if (distanceToTarget > bestScore) {
                bestScore = distanceToTarget;
                bestCell = current;
            }
        } else {
            if (distanceToTarget < bestScore) {
                bestScore = distanceToTarget;
                bestCell = current;
            }
        }

        for (const auto& dir : directions) {
            int newXInt = static_cast<int>(current.first) + dir.first;
            int newYInt = static_cast<int>(current.second) + dir.second;

            if (newXInt < 0 || newXInt >= static_cast<int>(size.first) ||
                newYInt < 0 || newYInt >= static_cast<int>(size.second))
                continue;

            size_t newX = static_cast<size_t>(newXInt);
            size_t newY = static_cast<size_t>(newYInt);
            std::pair<size_t, size_t> newPos = {newX, newY};

            if (distances.find(newPos) != distances.end())
                continue;
            if (grid[newY][newX][2] != nullptr)
                continue;
            if (std::dynamic_pointer_cast<WallEntity>(grid[newY][newX][1]) != nullptr)
                continue;

            queue.push(newPos);
            parent[newPos] = current;
            distances[newPos] = distances[current] + 1;
        }
    }

    if (bestCell.first == SIZE_MAX) {
        std::vector<std::pair<size_t, size_t>> adjacentCells;

        for (const auto& dir : directions) {
            int newXInt = static_cast<int>(this->_position.first) + dir.first;
            int newYInt = static_cast<int>(this->_position.second) + dir.second;

            if (newXInt < 0 || newXInt >= static_cast<int>(size.first) ||
                newYInt < 0 || newYInt >= static_cast<int>(size.second))
                continue;

            size_t newX = static_cast<size_t>(newXInt);
            size_t newY = static_cast<size_t>(newYInt);

            if (grid[newY][newX][2] != nullptr ||
                std::dynamic_pointer_cast<WallEntity>(grid[newY][newX][1]) != nullptr)
                continue;

            adjacentCells.push_back({newX, newY});
        }

        if (!adjacentCells.empty())
            return adjacentCells[0];
        return {SIZE_MAX, SIZE_MAX};
    }

    std::pair<size_t, size_t> current = bestCell;
    while (parent[current] != this->_position && parent[current].first != SIZE_MAX) {
        current = parent[current];
    }
    return current;
}

int RedGhost::calculateManhattanDistance(const std::pair<size_t, size_t>& pos1, const std::pair<size_t, size_t>& pos2) {
    int dx = static_cast<int>(pos1.first) - static_cast<int>(pos2.first);
    int dy = static_cast<int>(pos1.second) - static_cast<int>(pos2.second);
    return std::abs(dx) + std::abs(dy);
}
