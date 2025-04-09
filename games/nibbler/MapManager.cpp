/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** MapManager
*/

#include "MapManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

MapManager::MapManager()
{
    generateMap(1);
    initSpriteMap();
}

void MapManager::initSpriteMap()
{
    _spriteMap = {
        {0, "assets/nibbler/Floor.png"},
        {1, "assets/nibbler/Wall_horizontal.png"},
        {2, "assets/nibbler/Wall_vertical.png"},
        {3, "assets/nibbler/Wall_corner_top_left.png"},
        {4, "assets/nibbler/Wall_corner_top_right.png"},
        {5, "assets/nibbler/Wall_corner_bottom_left.png"},
        {6, "assets/nibbler/Wall_corner_bottom_right.png"},
        {7, "assets/nibbler/Wall_corner_bottom.png"},
        {8, "assets/nibbler/Wall_corner_top.png"},
        {9, "assets/nibbler/Wall_corner_left.png"},
        {10, "assets/nibbler/Wall_corner_right.png"},
        {11, "assets/nibbler/Wall_middle_bottom.png"},
        {12, "assets/nibbler/Wall_middle_left.png"},
        {13, "assets/nibbler/Wall_middle_right.png"},
        {14, "assets/nibbler/Wall_middle_top.png"},
        {15, "assets/nibbler/Nibbler_head_right.png"},
        {16, "assets/nibbler/Nibbler_head_left.png"},
        {17, "assets/nibbler/Nibbler_head_bottom.png"},
        {18, "assets/nibbler/Nibbler_head_top.png"},
        {19, "assets/nibbler/Nibbler_tail_horizontal.png"},
        {20, "assets/nibbler/Nibbler_tail_vertical.png"},
        {21, "assets/nibbler/Food.png"}
    };
}

void MapManager::generateMap(int level)
{
    createMap();
}

void MapManager::createMap()
{
    const int height = 21;
    const int width = 21;

    _mapLayout.resize(height, std::vector<int>(width, 0));

    // exterior wall
    _mapLayout[0][0] = 3;
    _mapLayout[0][height - 1] = 4;
    _mapLayout[width - 1][0] = 5;
    _mapLayout[width - 1][height - 1] = 6;
    for (int x = 1; x < height - 1; x++) {
        _mapLayout[0][x] = 1;
        _mapLayout[width - 1][x] = 1;
    }
    for (int y = 1; y < width - 1; y++) {
        _mapLayout[y][0] = 2;
        _mapLayout[y][height - 1] = 2;
    }

    // interior wall
    _mapLayout[2][2] = 9;
    _mapLayout[2][3] = 1;
    _mapLayout[2][4] = 14;
    _mapLayout[2][5] = 10;
    _mapLayout[3][4] = 7;

    _mapLayout[2][7] = 9;
    _mapLayout[2][8] = 14;
    _mapLayout[2][9] = 1;
    _mapLayout[2][10] = 10;
    _mapLayout[3][8] = 7;

    _mapLayout[2][12] = 3;
    _mapLayout[2][13] = 1;
    _mapLayout[2][14] = 10;
    _mapLayout[3][12] = 2;
    _mapLayout[4][12] = 2;
    _mapLayout[5][12] = 2;
    _mapLayout[6][12] = 2;
    _mapLayout[7][12] = 2;
    _mapLayout[8][12] = 6;
    _mapLayout[8][11] = 1;
    _mapLayout[8][10] = 9;

    _mapLayout[4][2] = 8;
    _mapLayout[5][2] = 2;
    _mapLayout[6][2] = 5;
    _mapLayout[6][3] = 1;
    _mapLayout[6][4] = 10;

    _playerStartPosition = {9, 9};
}

std::vector<std::vector<int>> MapManager::getMapLayout() const
{
    return _mapLayout;
}

std::string MapManager::getSpriteFromId(int id)
{
    auto it = _spriteMap.find(id);
    if (it != _spriteMap.end())
        return it->second;
    return "";
}


std::pair<size_t, size_t> MapManager::getPlayerStartPosition() const
{
    return _playerStartPosition;
}

bool MapManager::isWallAt(const std::pair<size_t, size_t>& position) const
{
    if (position.first >= _mapLayout[0].size() || position.second >= _mapLayout.size())
        return true;

    int tileId = _mapLayout[position.second][position.first];
    // Tu peux ajuster ici ce qui est considéré comme un mur
    return (tileId >= 1 && tileId <= 12);
}

std::vector<std::pair<int, int>> MapManager::getValidDirections(const std::pair<size_t, size_t>& position) const
{
    std::vector<std::pair<int, int>> validDirections;
    std::pair<int, int> directions[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (const auto& dir : directions) {
        std::pair<size_t, size_t> newPos = {
            position.first + dir.first,
            position.second + dir.second
        };

        if (!isWallAt(newPos)) {
            validDirections.push_back(dir);
        }
    }

    return validDirections;
}
