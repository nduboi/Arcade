/**
 * @file EventModule.hpp
 * @brief Declaration of the EventModule class.
 *
 * This file contains the definition of the EventModule class, which implements
 * the IEventModule interface. It is responsible for managing the display module
 * functionality and interacts with a library loader.
 *
 * @author EPITECH PROJECT
 * @date 2025
 */

#ifndef EventModule_HPP
#define EventModule_HPP

#include <memory>
#include "IEvent.hpp"
#include "LibLoader.hpp"
/**
 * @class EventModule
 * @brief A class that implements the IEventModule interface.
 *
 * The EventModule class is responsible for initializing and stopping
 * the display module. It interacts with a library loader to manage
 * dynamic libraries.
 */
class EventModule : public IEvent{
private:
	std::unique_ptr<IEvent> _object; /**< Reference to the library loader. */

public:

	void init() override;

	int pollEvents() override;

	void cleanup() override;
	/**
	 * @brief Constructor for the EventModule class.
	 * 
	 * @param EventModule A pointer to an object implementing the IEvent interface.
	 *                      This parameter is used to initialize the EventModule instance.
	 */
	EventModule(IEvent *);
	/**
	 * @brief Destructor for the EventModule class.
	 */
	~EventModule() override;

};

#endif // LIBMODULE_HPP
