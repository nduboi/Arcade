/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** PinkGhost
*/

#ifndef PINKGHOST_HPP_
#define PINKGHOST_HPP_

#include "GhostEntity.hpp"

class PinkGhost : public GhostEntity {
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
        PinkGhost(std::pair<size_t, size_t> spawnPosition, std::shared_ptr<IEntity> pacman, float multi);
        ~PinkGhost() = default;

        void moveEntity(std::shared_ptr<IGameModule> gameModule) override;
};

#endif /* !PINKGHOST_HPP_ */
