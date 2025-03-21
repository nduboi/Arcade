//
// Created by roussierenoa on 3/20/25.
//

#ifndef MENU_HPP
#define MENU_HPP
#include "IMenuModule.hpp"

class Menu : public IMenuModule {
private:
	std::size_t _score;
	std::size_t _highScore;

public:
	grid_t getEntities() const override;

	std::pair<size_t, size_t> getGridSize() const override;

	std::size_t getHighScore() const override;

	std::size_t getScore() const override;

	void setHighScore(std::size_t highScore) override;

	void setScore(std::size_t score) override;

	Menu();

	~Menu() = default;
};



#endif //MENU_HPP
