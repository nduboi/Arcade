/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** RedGhost
*/

#include "RedGhost.hpp"
#include "WallEntity.hpp"

RedGhost::RedGhost(std::pair<size_t, size_t> spawnPosition, std::shared_ptr<IEntity> pacman)
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

    this->_speedTime = 0.25f;
    this->_lastMove = std::chrono::steady_clock::now();

    this->_pacman = pacman;
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
    if (elapsedTime.count() < this->_speedTime)
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

    grid[newPos.second][newPos.first][2] = grid[this->_position.second][this->_position.first][2];
    grid[this->_position.second][this->_position.first][2] =  nullptr;
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
        if (std::dynamic_pointer_cast<WallEntity>(grid[it->second][it->first][1]) != nullptr) {
            it = freeCells.erase(it);
            continue;
        }
        ++it;
    }
    if (freeCells.empty())
        return;

    std::pair<size_t, size_t> pacmanPos = this->_pacman->getPosition();
    std::pair<size_t, size_t> closestCell = freeCells[0];
    int minDistance = calculateManhattanDistance(closestCell, pacmanPos);

    for (auto it = freeCells.begin(); it != freeCells.end(); it++) {
        int distance = calculateManhattanDistance(*it, pacmanPos);
        if (distance < minDistance) {
            minDistance = distance;
            closestCell = *it;
        }
    }
    this->moveTocell(gameModule, closestCell);
}

int RedGhost::calculateManhattanDistance(const std::pair<size_t, size_t>& pos1, const std::pair<size_t, size_t>& pos2) {
    int dx = static_cast<int>(pos1.first) - static_cast<int>(pos2.first);
    int dy = static_cast<int>(pos1.second) - static_cast<int>(pos2.second);
    return std::abs(dx) + std::abs(dy);
}

void RedGhost::runAway(std::shared_ptr<IGameModule> gameModule)
{
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
        if (std::dynamic_pointer_cast<WallEntity>(grid[it->second][it->first][1]) != nullptr) {
            it = freeCells.erase(it);
            continue;
        }
        ++it;
    }
    if (freeCells.empty())
        return;

    std::pair<size_t, size_t> pacmanPos = this->_pacman->getPosition();
    std::pair<size_t, size_t> closestCell = freeCells[0];
    int minDistance = calculateManhattanDistance(closestCell, pacmanPos);

    for (auto it = freeCells.begin(); it != freeCells.end(); it++) {
        int distance = calculateManhattanDistance(*it, pacmanPos);
        if (distance > minDistance) {
            minDistance = distance;
            closestCell = *it;
        }
    }
    this->moveTocell(gameModule, closestCell);
}
