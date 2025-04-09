/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** RedGhost
*/

#ifndef CYANGHOST_HPP_
#define CYANGHOST_HPP_

#include "GhostEntity.hpp"

class CyanGhost : public GhostEntity {
    private:
        void moveToSpawn(std::shared_ptr<IGameModule> gameModule);
        void moveToPacman(std::shared_ptr<IGameModule> gameModule);
        void runAway(std::shared_ptr<IGameModule> gameModule);

        void moveTocell(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos);

        void checkPacmanCollision(std::shared_ptr<IGameModule> gameModule);

        int calculateManhattanDistance(const std::pair<size_t, size_t>& pos1, const std::pair<size_t, size_t>& pos2);

        std::pair<size_t, size_t> findBestPathToTarget(std::shared_ptr<IGameModule> gameModule,
                                                      const std::pair<size_t, size_t>& target,
                                                      bool moveTowards);

    public:
        CyanGhost(std::pair<size_t, size_t> spawnPosition, std::shared_ptr<IEntity> pacman, float multi);
        ~CyanGhost() = default;

        void moveEntity(std::shared_ptr<IGameModule> gameModule) override;
};

#endif /* !CYANGHOST_HPP_ */
