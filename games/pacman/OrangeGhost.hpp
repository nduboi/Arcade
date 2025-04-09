/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** OrangeGhost
*/

#ifndef ORANGEGHOST_HPP_
#define ORANGEGHOST_HPP_

#include "GhostEntity.hpp"

class OrangeGhost : public GhostEntity {
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
        OrangeGhost(std::pair<size_t, size_t> spawnPosition, std::shared_ptr<IEntity> pacman, float multi);
        ~OrangeGhost() = default;

        void moveEntity(std::shared_ptr<IGameModule> gameModule) override;
};

#endif /* !ORANGEGHOST_HPP_ */
