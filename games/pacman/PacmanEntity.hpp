/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** PacmanEntity
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <map>
#include <chrono>
#include <vector>

#include "AEntity.hpp"

class PacmanEntity : public AEntity {
    private:
        std::chrono::time_point<std::chrono::steady_clock> _lastTime;
        std::pair<int, int> _inputDirection;
        std::pair<int, int> _direction;
        std::map<std::pair<size_t, size_t>, std::string> _assetsName;
        float _speedTime;
        std::chrono::time_point<std::chrono::steady_clock> _lastAnimation;
        int _animationIndex = 0;

        void setDirection(std::pair<int, int> direction, std::shared_ptr<IGameModule> gameModule);
        bool lastTimePassed();

        void moveEntities(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> pos1, std::pair<size_t, size_t> pos2);

        void actualiseAnimation();

        bool checkWallCollision(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos);

        bool isWall(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos);

    public:
        PacmanEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position);
        ~PacmanEntity() = default;

        void moveEntity(std::shared_ptr<IGameModule> gameModule, std::pair<int, int> direction) override;
        std::string getSpriteName() const override;
};

#endif /* !PACMAN_HPP_ */
