/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Saver
*/

#include "Saver.hpp"
#include <fstream>
#include <json.hpp>

Saver::Saver(std::string savefile)
{
    this->_savefile = savefile;
}

void Saver::saveScore(int score, std::string username, std::string game)
{
    nlohmann::json saveData;
    std::ifstream inFile(_savefile);

    if (inFile.is_open()) {
        try {
            inFile >> saveData;
        } catch (const std::exception& e) {
            saveData = nlohmann::json::object();
        }
        inFile.close();
    }

    if (!saveData.contains(username)) {
        saveData[username] = nlohmann::json::object();
    }
    saveData[username][game] = score;

    std::ofstream outFile(_savefile);
    if (outFile.is_open()) {
        outFile << std::setw(4) << saveData << std::endl;
        outFile.close();
    }
}

int Saver::getHighScore(std::string username, std::string game)
{
    nlohmann::json saveData;
    std::ifstream inFile(_savefile);

    if (inFile.is_open()) {
        try {
            inFile >> saveData;
            if (saveData.contains(username) &&
                saveData[username].contains(game)) {
                return saveData[username][game].get<int>();
            }
        } catch (const std::exception& e) {
            return 0;
        }
        inFile.close();
    }
    return 0;
}

std::pair<std::string, int> Saver::getHighScore(std::string game)
{
    nlohmann::json saveData;
    std::ifstream inFile(_savefile);

    if (inFile.is_open()) {
        try {
            inFile >> saveData;
            int highScore = 0;
            std::string highScoreUser = "";
            for (auto& user : saveData.items()) {
                if (user.value().contains(game)) {
                    int score = user.value()[game].get<int>();
                    if (score > highScore) {
                        highScore = score;
                        highScoreUser = user.key();
                    }
                }
            }
            return std::make_pair(highScoreUser, highScore);
        } catch (const std::exception& e) {
            return std::make_pair("", 0);
        }
        inFile.close();
    }
    return std::make_pair("", 0);
}
