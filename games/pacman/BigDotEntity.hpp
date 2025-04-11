/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** BigDotEntity
*/

#ifndef BIGDOTENTITY_HPP_
#define BIGDOTENTITY_HPP_

#include "AEntity.hpp"
#include <chrono>

class BigDotEntity : public AEntity {
    public:
        BigDotEntity(std::pair<size_t, size_t> position);
        ~BigDotEntity() = default;

        void onInteract(std::shared_ptr<IGameModule> gameModule) override;
        std::string getSpriteName() const override;

    private:
        std::chrono::time_point<std::chrono::steady_clock> _timePoint;
};

#endif /* !BIGDOTENTITY_HPP_ */
