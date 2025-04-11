/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** NibblerGame
*/

#ifndef NIBBLERGAME_HPP_
#define NIBBLERGAME_HPP_

#include "GameTemplate.hpp"
#include "NibblerHeadEntity.hpp"
#include "MapManager.hpp"

class NibblerGame : public GameTemplate {
    public:
        // Constructor
        NibblerGame();
        ~NibblerGame() = default;

        // Method
        std::vector<std::shared_ptr<IEntity>> getHUD() const override;
        void changeDifficulty() override;

        bool isWallAt(const std::pair<size_t, size_t>& position) const;
        std::vector<std::pair<int, int>> getValidDirections(const std::pair<size_t, size_t>& position) const;

    private:
        // Variable
        MapManager _mapManager;
        int _currentLevel;
        int _MAP_HEIGHT;
        int _MAP_WIDTH;

        // Method
        void setLayerBackground();
        void setLayerEntities();
        void setNibblerBody();
        void setLayerWalls();

};

#endif /* !NIBBLERGAME_HPP_ */
