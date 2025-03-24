//
// Created by roussierenoa on 3/20/25.
//

#ifndef MENUMODULE_HPP
#define MENUMODULE_HPP

#include "IMenuModule.hpp"


class MenuModule : public IMenuModule {
private:
	std::unique_ptr<IMenuModule> _object; /**< Reference to the library loader. */
public:
	std::size_t getHighScore() const override;

	void setHighScore(std::size_t highScore) override;

	std::size_t getScore() const override;

	void setScore(std::size_t score) override;

	grid_t getEntities() const override;

	std::pair<size_t, size_t> getGridSize() const override;

	MenuModule(IMenuModule *);

	~MenuModule() = default;
};
#endif //GAMEMODULE_HPP
