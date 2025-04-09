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

MapManager::~MapManager()
{

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

    _mapLayout = {
        { 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4},
        { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        { 2, 0, 9, 1,14,10, 0, 9,14, 1,10, 0, 3, 1,10, 0, 3, 1,10, 0, 2},
        { 2, 0, 0, 0, 7, 0, 0, 0, 7, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2},
        { 2, 0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 2, 0, 8, 0, 2, 0, 8, 0, 2},
        { 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 2, 0, 7, 0, 2, 0, 2},
        { 2, 0, 5, 1,10, 0, 2, 0, 9, 1, 6, 0, 2, 0, 2, 0, 0, 0, 2, 0, 2},
        { 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 7, 0, 9, 1, 6, 0, 2},
        {12, 1, 1, 1, 1, 1,11, 1,10, 0, 9, 1, 6, 0, 0, 0, 0, 0, 0, 0, 2},
        { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 1, 1, 1, 1,13},
        { 2, 0, 3, 1, 1,10, 0, 9,14,10, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        { 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0,12,10, 0, 9,14, 1, 1,10, 0, 2},
        { 2, 0, 2, 0, 8, 0, 8, 0, 7, 0, 9,13, 0, 0, 0, 2, 0, 0, 0, 0, 2},
        { 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 2, 0, 8, 0, 2, 0, 9,10, 0, 2},
        { 2, 0, 7, 0, 2, 0, 5,10, 0, 8, 0, 7, 0, 2, 0, 7, 0, 0, 0, 0, 2},
        { 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 4, 0, 2},
        { 2, 0, 9, 1,11, 1,10, 0, 9,11, 1,10, 0, 2, 0, 8, 0, 5, 6, 0, 2},
        { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2},
        { 2, 0, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 0, 5, 1, 1,10, 0, 2},
        { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6},
    };

    _playerStartPosition = {9, 19};
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
    return (tileId >= 1 && tileId <= 14);
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
