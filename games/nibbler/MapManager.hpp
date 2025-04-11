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
        // Constructor
        MapManager();
        ~MapManager();

        // Method
        void generateMap(int level);

        // Getter
        std::vector<std::vector<int>> getMapLayout() const;
        std::string getSpriteFromId(int id);
        std::pair<size_t, size_t> getPlayerStartPosition() const;
        bool isWallAt(const std::pair<size_t, size_t>& position) const;
        std::vector<std::pair<int, int>> getValidDirections(const std::pair<size_t, size_t>& position) const;
        int getNbLevels();

    private:
        // Variable
        std::pair<size_t, size_t> _playerStartPosition;
        std::unordered_map<int, std::string> _spriteMap;
        std::vector<std::vector<int>> _mapLayout;

        // Method
        void initSpriteMap();

        // Maps
        void createMapBonus();
        void createMapOne();
        void createMapTwo();
        void createMapThree();
        void createMapFour();
        void createMapFive();
        void createMapSix();
        void createMapSeven();
        void createMapEight();
        void createMapNine();
        void createMapTen();
        void createMapEleven();
        void createMapTwelve();
        void createMapThirteen();
        void createMapFourteen();
        void createMapFifteen();
    };

#endif /* !MAPMANAGER_HPP_ */
