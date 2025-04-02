/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** MinesweeperGame
*/

#ifndef MINESWEEPERGAME_HPP_
#define MINESWEEPERGAME_HPP_

#include "GameTemplate.hpp"
#include <random>
#include <map>

class MinesweeperGame : public GameTemplate {
        public:
                // Constructor
                MinesweeperGame(size_t width = 16, size_t height = 16);
                ~MinesweeperGame() = default;

                // Method
                void initializeGrid();

                std::vector<std::shared_ptr<IEntity>> getHUD() const override;

                void changeDifficulty() override;

        private:
                // Variable
                size_t _width;
                size_t _height;
};

#endif /* !MINESWEEPERGAME_HPP_ */