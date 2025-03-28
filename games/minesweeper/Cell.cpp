/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Cell
*/

#include "Cell.hpp"
#include "MinesweeperGame.hpp"
#include <algorithm>
#include <iostream>

Cell::Cell(size_t x, size_t y)
{
    this->_isRevealed = false;
    this->_isFlagged = false;
    this->_isMine = false;
    this->_adjacentMines = 0;
    this->_position = {x, y};
    this->_spriteName = "./assets/minesweeper/hidden.png";
    this->_color = 1;
    this->_text = "D";
    this->_firstClick = true;
    this->_gameState = 0;
    this->_clicked = false;
}

void Cell::onClick(std::shared_ptr<IGameModule> gameModule, clickType_t type)
{
    grid_t grid = gameModule->getEntities();
    if (gameModule->getGameState() == WIN || gameModule->getGameState() == LOSE)
        return;
    if (type == LEFT_CLICK) {
        if (this->_firstClick) {
            std::pair<size_t, size_t> mapSize = gameModule->getGridSize();
            for (size_t y = 0; y < mapSize.second; ++y) {
                for (size_t x = 0; x < mapSize.first; ++x) {
                    if (y >= grid.size() || x >= grid[y].size())
                        continue;
                    auto cell = std::dynamic_pointer_cast<Cell>(grid[y][x][0]);
                    cell->_firstClick = false;
                }
            }
            placeMines(gameModule);
            this->_firstClick = false;
        }
        if (!_isFlagged) {
            this->setRevealed(true);
            if (this->_isMine) {
                this->_clicked = true;
                this->_gameState = LOSE;
                std::pair<size_t, size_t> mapSize = gameModule->getGridSize();
                for (size_t y = 0; y < mapSize.second; ++y) {
                    for (size_t x = 0; x < mapSize.first; ++x) {
                        auto cell = std::dynamic_pointer_cast<Cell>(grid[y][x][0]);
                        cell->_gameState = LOSE;
                    }
                }
                this->revealAllMines(gameModule);
                gameModule->setGameState(LOSE);
            } else if (_adjacentMines == 0) {
                this->revealAdjacentCells(this->_position.first, this->_position.second, grid);
            }
            this->checkWinCondition(gameModule);
        }
    } else if (type == RIGHT_CLICK) {
        if (!this->_isRevealed)
            setFlagged(!this->_isFlagged);
    }
}

size_t Cell::createNumberMines(std::pair<size_t, size_t> map)
{
    size_t totalCells = map.first * map.second;
    double percentage = 10.0;

    if (map.first == 9 && map.second == 9)
        return 10;
    if (map.first == 16 && map.second == 16)
        return 40;
    if (map.first == 30 && map.second == 30)
        return 200;
    return static_cast<size_t>(totalCells * 0.15);
}

void Cell::placeMines(std::shared_ptr<IGameModule> gameModule)
{
    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> mapSize = gameModule->getGridSize();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> xDist(0, mapSize.first - 1);
    std::uniform_int_distribution<size_t> yDist(0, mapSize.second - 1);
    size_t mineCount = createNumberMines(mapSize);
    size_t minesPlaced = 0;

    std::vector<std::pair<int, int>> forbiddenPositions;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int fx = static_cast<int>(this->_position.first) + dx;
            int fy = static_cast<int>(this->_position.second) + dy;
            if (fx >= 0 && fx < static_cast<int>(mapSize.first) &&
                fy >= 0 && fy < static_cast<int>(mapSize.second)) {
                forbiddenPositions.push_back({fx, fy});
            }
        }
    }

    while (minesPlaced < mineCount) {
        size_t x = xDist(gen);
        size_t y = yDist(gen);
        auto cell = std::dynamic_pointer_cast<Cell>(grid[y][x][0]);
        if (!cell->isMine() && !cell->isRevealed() &&
            std::find(forbiddenPositions.begin(), forbiddenPositions.end(), std::make_pair(static_cast<int>(x), static_cast<int>(y))) == forbiddenPositions.end()) {
            cell->setMine(true);
            minesPlaced++;
        }
    }
    this->calculateAdjacentMines(gameModule);
    gameModule->setIsStarted(true);
}

gameState_t Cell::checkWinCondition(std::shared_ptr<IGameModule> gameModule)
{
    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> mapSize = gameModule->getGridSize();

    size_t revealedCells = 0;
    size_t mineCount = 0;

    for (size_t y = 0; y < mapSize.second; ++y) {
        for (size_t x = 0; x < mapSize.first; ++x) {
            auto cell = std::dynamic_pointer_cast<Cell>(grid[y][x][0]);
            if (cell->isMine())
                mineCount++;
            if (cell->isRevealed() && !cell->isMine())
                revealedCells++;
        }
    }

    if (revealedCells + mineCount == mapSize.first * mapSize.second) {
        this->_gameState = WIN;
        gameModule->setGameState(WIN);
        for (size_t y = 0; y < mapSize.second; ++y) {
            for (size_t x = 0; x < mapSize.first; ++x) {
                auto cell = std::dynamic_pointer_cast<Cell>(grid[y][x][0]);
                cell->_gameState = WIN;
            }
        }
        this->revealAllMines(gameModule);
        gameModule->setScore(mapSize.first * mapSize.second * 10 - mineCount * 5);
    }

    return gameModule->getGameState();
}

std::string Cell::getSpriteName() const
{
    if (this->_isFlagged) {
        if ((this->_gameState == WIN) && this->_isMine) {
            return "./assets/minesweeper/mine_reveal.png";
        }
        if ((this->_gameState == LOSE) && this->_isMine) {
            return "./assets/minesweeper/mine.png";
        }
        return "./assets/minesweeper/flag.png";
    }
    if (!this->_isRevealed) {
        return "./assets/minesweeper/hidden.png";
    }
    if (this->_isMine) {
        if (this->_gameState == LOSE) {
            if (this->_clicked == true)
                return "./assets/minesweeper/mine_explosed.png";
            return "./assets/minesweeper/mine.png";
        }
        if (this->_gameState == WIN)
            return "./assets/minesweeper/mine_reveal.png";
        return "./assets/minesweeper/mine.png";
    }
    return "./assets/minesweeper/cell_" + std::to_string(this->_adjacentMines) + ".png";
}

void Cell::calculateAdjacentMines(std::shared_ptr<IGameModule> gameModule)
{
    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> mapSize = gameModule->getGridSize();

    for (size_t y = 0; y < mapSize.second; ++y) {
        for (size_t x = 0; x < mapSize.first; ++x) {
            auto cell = std::dynamic_pointer_cast<Cell>(grid[y][x][0]);
            if (!cell->isMine())
                cell->setAdjacentMines(countAdjacentMines(x, y, grid));
        }
    }
}

size_t Cell::countAdjacentMines(size_t x, size_t y, const grid_t& grid) const
{
    size_t count = 0;
    std::pair<size_t, size_t> mapSize = {grid[0].size(), grid.size()};
    static const std::pair<int, int> directions[] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0},           {1, 0},
        {-1, 1},  {0, 1},  {1, 1}
    };

    for (const auto& dir : directions) {
        int nx = static_cast<int>(x) + dir.first;
        int ny = static_cast<int>(y) + dir.second;

        if (nx >= 0 && nx < static_cast<int>(mapSize.first) &&
            ny >= 0 && ny < static_cast<int>(mapSize.second)) {
            auto cell = std::dynamic_pointer_cast<Cell>(grid[ny][nx][0]);
            if (cell->isMine())
                count++;
        }
    }
    return count;
}

void Cell::revealAdjacentCells(size_t x, size_t y, grid_t& grid)
{
    std::pair<size_t, size_t> mapSize = {grid[0].size(), grid.size()};
    static const std::pair<int, int> directions[] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0},           {1, 0},
        {-1, 1},  {0, 1},  {1, 1}
    };

    for (const auto& dir : directions) {
        int nx = static_cast<int>(x) + dir.first;
        int ny = static_cast<int>(y) + dir.second;

        if (nx >= 0 && nx < static_cast<int>(mapSize.first) &&
            ny >= 0 && ny < static_cast<int>(mapSize.second)) {
            auto cell = std::dynamic_pointer_cast<Cell>(grid[ny][nx][0]);

            if (!cell->isRevealed() && !cell->isFlagged()) {
                cell->setRevealed(true);
                if (cell->getAdjacentMines() == 0)
                    this->revealAdjacentCells(nx, ny, grid);
            }
        }
    }
}

std::size_t Cell::getColor() const
{
    if (!this->_isRevealed)
        return 1;
    if (this->_isMine)
        return 2;
    if (this->_adjacentMines == 0)
        return 0;
    if (this->_isFlagged)
        return 4;
    return -1;
}

std::string Cell::getText() const
{
    if (this->_isFlagged)
        return "F";
    if (!this->_isRevealed)
        return " ";
    if (this->_isMine)
        return "#";
    if (this->_adjacentMines > 0)
        return std::to_string(this->_adjacentMines);
    return "D";
}


void Cell::setRevealed(bool revealed)
{
    this->_isRevealed = revealed;

    if (revealed) {
        if (this->_isMine) {
            this->_spriteName = "./assets/minesweeper/mine_reveal.png";
            this->_color = 3;
            this->_text = "@";
        } else if (this->_adjacentMines > 0) {
            this->_spriteName = "./assets/minesweeper/cell_" + std::to_string(this->_adjacentMines) + ".png";
            this->_color = -1;
            this->_text = std::to_string(this->_adjacentMines);
        } else {
            this->_spriteName = "./assets/minesweeper/cell_0.png";
            this->_color = 0;
            this->_text = " ";
        }
    } else {
        this->_spriteName = "./assets/minesweeper/hidden.png";
        this->_color = 1;
        this->_text = "D";
    }
}

void Cell::revealAllMines(std::shared_ptr<IGameModule> gameModule)
{
    grid_t grid = gameModule->getEntities();
    std::pair<size_t, size_t> mapSize = gameModule->getGridSize();

    for (size_t y = 0; y < mapSize.second; ++y) {
        for (size_t x = 0; x < mapSize.first; ++x) {
            auto cell = std::dynamic_pointer_cast<Cell>(grid[y][x][0]);
            if (cell->isMine()) {
                if (cell->isFlagged()) {
                    cell->_spriteName = "./assets/minesweeper/mine_flag.png";
                }
                cell->setRevealed(true);
            }
        }
    }
}

bool Cell::isRevealed() const
{
    return this->_isRevealed;
}

void Cell::setFlagged(bool flagged)
{
    this->_isFlagged = flagged;
    if (flagged) {
        this->_spriteName = "./assets/minesweeper/flag.png";
        this->_text = "F";
    } else if (!_isRevealed) {
        this->_spriteName = "./assets/minesweeper/hidden.png";
        this->_text = "D";
    }
}

bool Cell::isFlagged() const
{
    return this->_isFlagged;
}

void Cell::setMine(bool mine)
{
    this->_isMine = mine;
}

bool Cell::isMine() const
{
    return this->_isMine;
}

void Cell::setAdjacentMines(size_t count)
{
    this->_adjacentMines = count;
}

size_t Cell::getAdjacentMines() const
{
    return this->_adjacentMines;
}
