/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** BigDotEntity
*/

#ifndef BIGDOTENTITY_HPP_
#define BIGDOTENTITY_HPP_

#include "AEntity.hpp"

class BigDotEntity : public AEntity {
    public:
        BigDotEntity(std::pair<size_t, size_t> position);
        ~BigDotEntity() = default;

        void onInteract(std::shared_ptr<IGameModule> gameModule) override;
};

#endif /* !BIGDOTENTITY_HPP_ */
