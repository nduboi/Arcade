/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** FoodEntity
*/

#ifndef FOODENTITY_HPP_
#define FOODENTITY_HPP_

#include "AEntity.hpp"

class FoodEntity : public AEntity {
    public:
        // Constructor
        FoodEntity(std::pair<size_t, size_t> position);
        ~FoodEntity();

        // Method
        void onInteract(std::shared_ptr<IGameModule> gameModule) override;

    private:
        //Method
        int getNbFoodEntities(const grid_t &grid) const;
};

#endif /* !FOODENTITY_HPP_ */
