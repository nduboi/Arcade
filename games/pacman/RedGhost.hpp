/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** RedGhost
*/

#ifndef REDGHOST_HPP_
#define REDGHOST_HPP_

#include "GhostEntity.hpp"

class RedGhost : public GhostEntity {
    private:
        void moveToSpawn(std::shared_ptr<IGameModule> gameModule);
        void moveToPacman(std::shared_ptr<IGameModule> gameModule);
        void runAway(std::shared_ptr<IGameModule> gameModule);

        void moveTocell(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos);

        int calculateManhattanDistance(const std::pair<size_t, size_t>& pos1, const std::pair<size_t, size_t>& pos2);

    public:
        RedGhost(std::pair<size_t, size_t> spawnPosition, std::shared_ptr<IEntity> pacman);
        ~RedGhost() = default;

        void moveEntity(std::shared_ptr<IGameModule> gameModule) override;
};

#endif /* !REDGHOST_HPP_ */
