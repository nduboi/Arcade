/**
 * @file Saver.hpp
 * @brief Declaration of the Saver class.
 *
 * This file contains the definition of the Saver class, which is responsible
 * for saving and retrieving high scores for the Arcade project.
 */

#ifndef SAVER_HPP_
#define SAVER_HPP_

#include <iostream>
#include <iomanip>

/**
 * @class Saver
 * @brief Class for saving and retrieving high scores.
 *
 * The Saver class provides methods to save scores to a file and retrieve
 * high scores for specific users and games.
 */
class Saver {
    private:
        std::string _savefile; ///< Path to the save file.

    public:
        /**
         * @brief Constructor for the Saver class.
         * @param savefile Path to the save file.
         */
        Saver(std::string savefile);

        /**
         * @brief Save a score for a specific user and game.
         * @param score The score to save.
         * @param username The username associated with the score.
         * @param game The game associated with the score.
         */
        void saveScore(int score, std::string username, std::string game);

        /**
         * @brief Retrieve the high score for a specific user and game.
         * @param username The username to retrieve the high score for.
         * @param game The game to retrieve the high score for.
         * @return The high score.
         */
        int getHighScore(std::string username, std::string game);
};

#endif /* !SAVER_HPP_ */
