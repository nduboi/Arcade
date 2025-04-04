#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <functional>
#include <memory>
#include <thread>
#include "EventModule.hpp"
#include "WindowModule.hpp"
#include "GameModule.hpp"
#include "Menu.hpp"
#include "Saver.hpp"

/**
 * @class Core
 * @brief Main class responsible for managing the Arcade application.
 *
 * The Core class handles the loading of libraries, managing game and display modules,
 * processing events, and rendering the game or menu.
 */
class Core {
private:
	/**
	 * @enum LogicModule_t
	 * @brief Enum representing the current logic module state.
	 */
	typedef enum LogicModule_e {
		GAME, /**< Game module is active. */
		MENU, /**< Menu module is active. */
		TYPE_COUNT /**< Total number of module types. */
	} LogicModule_t;

	Loader::LibLoader _displayLoader; ///< Loader for display libraries.
	Loader::LibLoader _gameLoader; ///< Loader for game libraries.

	std::vector<std::string> _displayLibPath; ///< Paths to available display libraries.
	std::vector<std::string> _gameLibPath; ///< Paths to available game libraries.

	LogicModule_t _moduleLoaded; ///< Current active module.
	int _gameLibIndex = 0; ///< Index of the currently loaded game library.
	int _displayLibIndex = 0; ///< Index of the currently loaded display library.

	IEvent::event_t _lastEvent; ///< Last event processed.

	Saver _saver; ///< Object responsible for saving and loading scores.

	/**
	 * @brief Get the direction of the current event.
	 * @return A pair representing the direction (x, y).
	 */
	std::pair<int, int> _getEventDirection() const;

	/**
	 * @brief Check if the current event is a click event.
	 * @return True if the event is a click event, false otherwise.
	 */
	bool _isEventClick() const;

	/**
	 * @brief Process a click event on the game grid.
	 * @param x X-coordinate of the click.
	 * @param y Y-coordinate of the click.
	 * @param z Z-coordinate of the click.
	 */
	void _processClickEvent(int x, int y, int z);

	/**
	 * @brief Process a click event in the menu.
	 */
	void _processMenuClick();

	/**
	 * @brief Analyze the current event and take appropriate actions.
	 */
	void _analyze();

	/**
	 * @brief Compute the game logic based on the current state.
	 */
	void _compute();

	/**
	 * @brief Save the current game score.
	 */
	void _saveScore();

	/**
	 * @brief Set the high score for the current game.
	 */
	void _setHighScore();

	/**
	 * @brief Render the current state (game, menu, or HUD).
	 */
	void _display();

	/**
	 * @brief Render the game grid.
	 */
	void _displayGame();

	/**
	 * @brief Render the menu.
	 */
	void _displayMenu();

	/**
	 * @brief Render the HUD (Heads-Up Display).
	 */
	void _displayHUD();

	/**
	 * @brief Refresh the list of available libraries.
	 */
	void _refreshLibList();

	/**
	 * @brief Reload the current game module.
	 */
	void _reloadCurrentGame();

	/**
	 * @brief Load the next game module in the list.
	 */
	void _loadNextGame();

	/**
	 * @brief Load the next display module in the list.
	 */
	void _loadNextGraphic();

public:
	std::shared_ptr<IWindow> displayPtr; ///< Shared pointer to the display IWindow.
	std::shared_ptr<WindowModule> display; ///< Shared pointer to the display WindowModule.
	std::shared_ptr<EventModule> event; ///< Shared pointer to the event module.
	std::shared_ptr<GameModule> game; ///< Shared pointer to the game module.

	Menu _menu; ///< Menu object for managing the menu state.

	/**
	 * @brief Display all available libraries.
	 */
	void displayAllLib();

	/**
	 * @brief Load a display module.
	 * @param displayLib Path to the display library.
	 */
	void loadDisplayModule(const std::string &displayLib);

	/**
	 * @brief Load a game module.
	 * @param gameLib Path to the game library.
	 */
	void loadGameModule(const std::string &gameLib);

	/**
	 * @brief Main loop of the application.
	 */
	void loop();

	/**
	 * @brief Constructor for the Core class.
	 */
	Core();

	/**
	 * @brief Destructor for the Core class.
	 */
	~Core();
};

#endif // PROGRAM_HPP
