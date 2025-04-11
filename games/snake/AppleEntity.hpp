/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AppleEntity
*/

#ifndef APPLEENTITY_HPP_
#define APPLEENTITY_HPP_

#include "AEntity.hpp"
#include <chrono>

class AppleEntity : public AEntity {
    private:
        int getNbVoidEntities(const grid_t &grid) const;
        bool isValidPosition(const std::pair<size_t, size_t> &pos, const grid_t &grid) const;
        std::chrono::time_point<std::chrono::steady_clock> _timePoint;

    public:
        AppleEntity(std::pair<size_t, size_t> position);
        ~AppleEntity() = default;

        void onInteract(std::shared_ptr<IGameModule> gameModule) override;
        std::string getSpriteName() const override;
};

#endif /* !APPLEENTITY_HPP_ */
