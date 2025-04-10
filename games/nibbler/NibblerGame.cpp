/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** NibblerGame
*/

#include "NibblerGame.hpp"
#include "VoidEntity.hpp"
#include "NibblerHeadEntity.hpp"
#include "NibblerTailEntity.hpp"
#include "FoodEntity.hpp"
#include "WallEntity.hpp"

#include "ScoreEntityHUD.hpp"
#include "HighScoreEntityHUD.hpp"
#include "TimeEntityHUD.hpp"
#include "TextEntityHUD.hpp"
#include "BigTextEntityHUD.hpp"
#include <bits/algorithmfwd.h>

const int MAP_LAYER = 2;

NibblerGame::NibblerGame() : _currentLevel(1)
{
    this->_highScore = 0;
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now();

    _mapManager.generateMap(_currentLevel);
    this->_MAP_HEIGHT = _mapManager.getMapLayout().size();
    this->_MAP_WIDTH = _mapManager.getMapLayout()[0].size();

    this->_entities.resize(_MAP_HEIGHT);
    for (int y = 0; y < _MAP_HEIGHT; y++) {
        this->_entities[y].resize(_MAP_WIDTH);
        for (int x = 0; x < _MAP_WIDTH; x++) {
            this->_entities[y][x].resize(MAP_LAYER);
        }
    }
    this->setLayerBackground();
    this->setLayerWalls();
    this->setLayerEntities();
}

void NibblerGame::setLayerBackground()
{
    for (int y = 0; y < _MAP_HEIGHT; y++) {
        for (int x = 0; x < _MAP_WIDTH; x++) {
            this->_entities[y][x][0] = std::make_shared<VoidEntity>("assets/nibbler/Floor.png", 1, "", std::make_pair(x, y));
        }
    }
}

void NibblerGame::setLayerWalls()
{
    auto mapLayout = _mapManager.getMapLayout();

    for (int y = 0; y < _MAP_HEIGHT && y < mapLayout.size(); y++) {
        for (int x = 0; x < _MAP_WIDTH && x < mapLayout[y].size(); x++) {
            if ((mapLayout[y][x] >= 1 && mapLayout[y][x] <= 14) || mapLayout[y][x] == 22) {
                std::string wallSprite = _mapManager.getSpriteFromId(mapLayout[y][x]);
                this->_entities[y][x][1] = std::make_shared<WallEntity>(wallSprite, std::make_pair(x, y));
            }
        }
    }
}

void NibblerGame::setLayerEntities()
{
    for (int y = 0; y < _MAP_HEIGHT; y++) {
        for (int x = 0; x < _MAP_WIDTH; x++) {
            if (!this->_entities[y][x][1] || !std::dynamic_pointer_cast<WallEntity>(this->_entities[y][x][1]))
                this->_entities[y][x][1] = std::make_shared<VoidEntity>(this->_entities[y][x][0]->getSpriteName(), 1, "", std::make_pair(x, y));
        }
    }

    auto startPos = _mapManager.getPlayerStartPosition();
    this->_entities[startPos.second][startPos.first][1] = std::make_shared<NibblerHeadEntity>(4, "h", startPos, _mapManager);
    this->setNibblerBody();
    this->setLayerFood();
}

void NibblerGame::setNibblerBody()
{
    auto startPos = _mapManager.getPlayerStartPosition();
    auto validDirections = _mapManager.getValidDirections(startPos);

    if (validDirections.empty())
        return;

    std::pair<int, int> bodyDirection = {-validDirections[0].first, -validDirections[0].second};

    std::vector<std::pair<size_t, size_t>> bodyPositions;
    std::pair<size_t, size_t> currentPos = startPos;

    for (int i = 0; i < 3; i++) {
        std::pair<size_t, size_t> nextPos = {
            currentPos.first + bodyDirection.first,
            currentPos.second + bodyDirection.second
        };

        if (nextPos.first >= _MAP_WIDTH || nextPos.second >= _MAP_HEIGHT ||
            nextPos.first < 0 || nextPos.second < 0 ||
            _mapManager.isWallAt(nextPos))
            break;

        bodyPositions.push_back(nextPos);
        currentPos = nextPos;
    }

    for (size_t i = 0; i < bodyPositions.size(); i++) {
        auto pos = bodyPositions[i];
        this->_entities[pos.second][pos.first][1] = std::make_shared<NibblerTailEntity>(3, "b", pos, i);
    }

    auto head = std::dynamic_pointer_cast<NibblerHeadEntity>(this->_entities[startPos.second][startPos.first][1]);
    if (head) {
        std::vector<std::pair<size_t, size_t>> allPositions = bodyPositions;
        allPositions.insert(allPositions.begin(), startPos);
        std::reverse(allPositions.begin(), allPositions.end());
        head->initializePreviousPositions(allPositions);
    }
}

std::pair<size_t, size_t> NibblerGame::findFoodPosition() const
{
    std::vector<std::pair<size_t, size_t>> emptyPositions;

    for (int y = 0; y < _MAP_HEIGHT; y++) {
        for (int x = 0; x < _MAP_WIDTH; x++) {
            if (std::dynamic_pointer_cast<VoidEntity>(this->_entities[y][x][1])) {
                emptyPositions.push_back(std::make_pair(x, y));
            }
        }
    }

    if (emptyPositions.empty())
        return std::make_pair(0, 0);

    int randIndex = rand() % emptyPositions.size();
    return emptyPositions[randIndex];
}

void NibblerGame::setLayerFood()
{
    auto foodPos = findFoodPosition();
    this->_entities[foodPos.second][foodPos.first][1] = std::make_shared<FoodEntity>(foodPos);
}

bool NibblerGame::isWallAt(const std::pair<size_t, size_t>& position) const
{
    return _mapManager.isWallAt(position);
}

std::vector<std::pair<int, int>> NibblerGame::getValidDirections(const std::pair<size_t, size_t>& position) const
{
    return _mapManager.getValidDirections(position);
}

std::vector<std::shared_ptr<IEntity>> NibblerGame::getHUD() const
{
    std::vector<std::shared_ptr<IEntity>> hud;

    hud.push_back(std::make_shared<ScoreEntityHUD>(this->getScore(), std::make_pair(10, 15)));
    hud.push_back(std::make_shared<HighScoreEntityHUD>(this->getHighScore(), std::make_pair(10, 55)));

    std::size_t secondsElapsed = this->getTime();
    hud.push_back(std::make_shared<TimeEntityHUD>(secondsElapsed, std::make_pair(350, 35)));

    std::string levelString = std::to_string(this->_currentLevel);
    while (levelString.length() < 2)
        levelString = "0" + levelString;
    hud.push_back(std::make_shared<TextEntityHUD>("Level " + levelString, std::make_pair(675, 35)));

    if (this->getIsStarted() == false)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Press any direction to start", std::make_pair(250, 850)));
    if (this->getGameState() == LOSE)
        hud.push_back(std::make_shared<BigTextEntityHUD>("Game Over", std::make_pair(350, 850)));
    if (this->getGameState() == WIN)
        hud.push_back(std::make_shared<BigTextEntityHUD>("You Win", std::make_pair(350, 850)));

    return hud;
}

void NibblerGame::changeDifficulty()
{
    this->_score = 0;
    this->_isStarted = false;
    this->_gameState = PLAYING;
    this->_time = std::chrono::steady_clock::now();
    this->_currentLevel += 1;
    if (_currentLevel > 2)
        this->_currentLevel = 1;

    _mapManager.generateMap(_currentLevel);
    this->_MAP_HEIGHT = _mapManager.getMapLayout().size();
    this->_MAP_WIDTH = _mapManager.getMapLayout()[0].size();

    this->_entities.clear();
    this->_entities.resize(_MAP_HEIGHT);
    for (int y = 0; y < _MAP_HEIGHT; y++) {
        this->_entities[y].resize(_MAP_WIDTH);
        for (int x = 0; x < _MAP_WIDTH; x++) {
            this->_entities[y][x].resize(MAP_LAYER);
        }
    }
    this->setLayerBackground();
    this->setLayerWalls();
    this->setLayerEntities();
}
