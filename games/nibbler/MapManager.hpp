/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** MapManager
*/

#ifndef MAPMANAGER_HPP_
#define MAPMANAGER_HPP_

#include <vector>
#include <string>
#include <map>
#include "IGameModule.hpp"
#include <unordered_map>

class MapManager {
    public:
        MapManager();

        std::vector<std::vector<int>> getMapLayout() const;
        std::string getSpriteFromId(int id);
        std::pair<size_t, size_t> getPlayerStartPosition() const;
        bool isWallAt(const std::pair<size_t, size_t>& position) const;
        std::vector<std::pair<int, int>> getValidDirections(const std::pair<size_t, size_t>& position) const;
        void generateMap(int level);
    
    private:
        void createMap();
    
        std::unordered_map<int, std::string> _spriteMap;
    void initSpriteMap();
        std::vector<std::vector<int>> _mapLayout;
        std::pair<size_t, size_t> _playerStartPosition;
    };

#endif /* !MAPMANAGER_HPP_ */
