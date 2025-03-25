/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** MinesweeperGame
*/

#include "MinesweeperGame.hpp"
#include "Cell.hpp"
#include <algorithm>
#include <ctime>

MinesweeperGame::MinesweeperGame(size_t width, size_t height, size_t mineCount)
{
    this->_highScore = 0;
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = 0;
    _width = width;
    _height = height;
    _mineCount = mineCount;
    _revealedCells = 0;
    _flaggedCells = 0;
    _gameState = PLAYING;
    _firstClick = true;
    initializeGrid();
}

void MinesweeperGame::initializeGrid()
{
    _entities.resize(_height);
    for (size_t y = 0; y < _height; ++y) {
        _entities[y].resize(_width);
        for (size_t x = 0; x < _width; ++x) {
            _entities[y][x].resize(1);
            _entities[y][x][0] = std::make_shared<Cell>(x, y);
        }
    }
}

void MinesweeperGame::placeMines()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> xDist(0, _width - 1);
    std::uniform_int_distribution<size_t> yDist(0, _height - 1);
    size_t minesPlaced = 0;

    while (minesPlaced < _mineCount) {
        size_t x = xDist(gen);
        size_t y = yDist(gen);
        auto cell = std::dynamic_pointer_cast<Cell>(_entities[0][y][x]);
        if (!cell->isMine()) {
            cell->setMine(true);
            minesPlaced++;
        }
    }
    calculateAdjacentMines();
}

void MinesweeperGame::calculateAdjacentMines()
{
    for (size_t y = 0; y < _height; ++y) {
        for (size_t x = 0; x < _width; ++x) {
            if (!isMine(x, y)) {
                auto cell = std::dynamic_pointer_cast<Cell>(_entities[0][y][x]);
                cell->setAdjacentMines(countAdjacentMines(x, y));
            }
        }
    }
}

gameState_t MinesweeperGame::revealCell(size_t x, size_t y)
{
    if (!isValidPosition(x, y)) {
        return _gameState;
    }

    auto cell = std::dynamic_pointer_cast<Cell>(_entities[0][y][x]);
    if (_firstClick) {
        _firstClick = false;
        cell->setRevealed(true);
        placeMines();
        cell->setRevealed(false);
    }
    if (cell->isRevealed() || cell->isFlagged()) {
        return _gameState;
    }
    cell->setRevealed(true);
    _revealedCells++;
    if (cell->isMine()) {
        _gameState = LOSE;
        for (size_t cy = 0; cy < _height; ++cy) {
            for (size_t cx = 0; cx < _width; ++cx) {
                auto c = std::dynamic_pointer_cast<Cell>(_entities[0][cy][cx]);
                if (c->isMine()) {
                    c->setRevealed(true);
                }
            }
        }
        return _gameState;
    }
    if (cell->getAdjacentMines() == 0) {
        revealAdjacentCells(x, y);
    }
    return checkWinCondition();
}

gameState_t MinesweeperGame::flagCell(size_t x, size_t y)
{
    if (!isValidPosition(x, y) || _gameState != PLAYING) {
        return _gameState;
    }

    auto cell = std::dynamic_pointer_cast<Cell>(_entities[0][y][x]);
    if (cell->isRevealed()) {
        return _gameState;
    }
    if (cell->isFlagged()) {
        cell->setFlagged(false);
        _flaggedCells--;
    } else {
        cell->setFlagged(true);
        _flaggedCells++;
    }
    return _gameState;
}

gameState_t MinesweeperGame::checkWinCondition()
{
    if (_revealedCells + _mineCount == _width * _height) {
        _gameState = WIN;
        setScore(_width * _height * 10 - _mineCount * 5);
        if (getScore() > getHighScore()) {
            setHighScore(getScore());
        }
    }
    return _gameState;
}

void MinesweeperGame::revealAdjacentCells(size_t x, size_t y)
{

    static const std::pair<int, int> directions[] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0},           {1, 0},
        {-1, 1},  {0, 1},  {1, 1}
    };

    for (const auto& dir : directions) {
        int nx = static_cast<int>(x) + dir.first;
        int ny = static_cast<int>(y) + dir.second;
        if (nx >= 0 && nx < static_cast<int>(_width) && ny >= 0 && ny < static_cast<int>(_height)) {
            auto cell = std::dynamic_pointer_cast<Cell>(_entities[0][ny][nx]);
            if (!cell->isRevealed() && !cell->isFlagged()) {
                cell->setRevealed(true);
                _revealedCells++;
                if (cell->getAdjacentMines() == 0) {
                    revealAdjacentCells(nx, ny);
                }
            }
        }
    }
}

bool MinesweeperGame::isValidPosition(size_t x, size_t y) const
{
    return x < _width && y < _height;
}

bool MinesweeperGame::isMine(size_t x, size_t y) const
{
    if (!isValidPosition(x, y)) {
        return false;
    }

    auto cell = std::dynamic_pointer_cast<Cell>(_entities[0][y][x]);
    return cell->isMine();
}

size_t MinesweeperGame::countAdjacentMines(size_t x, size_t y) const
{
    size_t count = 0;

    static const std::pair<int, int> directions[] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0},           {1, 0},
        {-1, 1},  {0, 1},  {1, 1}
    };

    for (const auto& dir : directions) {
        int nx = static_cast<int>(x) + dir.first;
        int ny = static_cast<int>(y) + dir.second;
        if (nx >= 0 && nx < static_cast<int>(_width) && ny >= 0 && ny < static_cast<int>(_height)) {
            if (isMine(nx, ny)) {
                count++;
            }
        }
    }
    return count;
}
