/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** BigTextEntityHUD
*/

#ifndef BIGTEXTENTITYHUD_HPP_
#define BIGTEXTENTITYHUD_HPP_

#include "AEntity.hpp"

class BigTextEntityHUD : public AEntity {
    public:
        BigTextEntityHUD(std::string text, std::pair<std::size_t, std::size_t> position);
        ~BigTextEntityHUD() = default;

    protected:
    private:
};

#endif /* !BIGTEXTENTITYHUD_HPP_ */
