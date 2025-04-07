/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Saver
*/

#ifndef SAVER_HPP_
#define SAVER_HPP_

#include <iostream>
#include <iomanip>

class Saver {
    private:
        std::string _savefile;

    public:
        Saver(std::string savefile);
        ~Saver() = default;

        void saveScore(int score, std::string username, std::string game);
        int getHighScore(std::string username, std::string game);
        int getHighScore(std::string username);
};

#endif /* !SAVER_HPP_ */
