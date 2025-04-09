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
    public:
        RedGhost(std::pair<size_t, size_t> spawnPosition);
        ~RedGhost() = default;

        void moveEntity(std::shared_ptr<IGameModule> gameModule) override;
};

#endif /* !REDGHOST_HPP_ */
