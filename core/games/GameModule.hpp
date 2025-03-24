//
// Created by roussierenoa on 3/20/25.
//

#ifndef GAMEMODULE_HPP
#define GAMEMODULE_HPP

#include "IGameModule.hpp"


class GameModule : public IGameModule {
private:
	std::unique_ptr<IGameModule> _object; /**< Reference to the library loader. */
public:
	std::size_t getHighScore() const override;

	void setHighScore(std::size_t highScore) override;

	std::size_t getScore() const override;

	void setScore(std::size_t score) override;

	grid_t getEntities() const override;

	std::pair<size_t, size_t> getGridSize() const override;

	GameModule(IGameModule *);

	~GameModule() = default;
};
#endif //GAMEMODULE_HPP
