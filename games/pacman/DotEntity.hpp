/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** DotEntity
*/

#ifndef DOTENTITY_HPP_
#define DOTENTITY_HPP_

#include "AEntity.hpp"

class DotEntity : public AEntity {
    public:
        DotEntity(std::pair<size_t, size_t> position);
        ~DotEntity() = default;

        void onInteract(std::shared_ptr<IGameModule> gameModule) override;
};

#endif /* !DOTENTITY_HPP_ */
