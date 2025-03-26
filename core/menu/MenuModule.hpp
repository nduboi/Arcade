//
// Created by roussierenoa on 3/20/25.
//

#ifndef MENUMODULE_HPP
#define MENUMODULE_HPP

#include <IGameModule.hpp>
#include "IMenu.hpp"


class MenuModule : public IMenu {
private:
	std::unique_ptr<IMenu> _object; /**< Reference to the library loader. */
public:

	std::vector<Boxes> getBoxPoses(std::shared_ptr<IWindow> window) override;

	std::string getUsername() override;

	void setUsername(std::string username) override;

	void displayMenu(std::shared_ptr<IWindow> window, std::vector<Boxes> _boxes, std::vector<std::string> libs, std::vector<std::string> games) override;

	MenuModule(IMenu *);

	~MenuModule() = default;
};
#endif //GAMEMODULE_HPP
