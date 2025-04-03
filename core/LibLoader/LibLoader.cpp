//
// Created by roussierenoa on 3/17/25.
//

#include "LibLoader.hpp"
#include "DynamicLib.hpp"
#include <iostream>
#include <stdexcept>

namespace Loader {
	void LibLoader::openLib(const std::string &path)
	{
		std::cout << "Opening library: " << path << std::endl;
		this->closeLib(); // Assurez-vous que la bibliothèque précédente est fermée

		try {
			this->_moduleHandle = openDynamicLib(path.c_str());
			if (!this->_moduleHandle)
				throw std::exception();
		} catch (...) {
			throw DllException("Error during dlopen("+path+", ...): " + std::string(getDlError()));
		}

		this->_getModuleType = reinterpret_cast<GetModuleTypeFct>(getFunctionDynamicLib(this->_moduleHandle, "getType"));
		if (!this->_getModuleType)
			throw DllException("Error cannot getType function");
		this->_moduleType = this->_getModuleType();
		std::cout << "Library loaded successfully: " << path << std::endl;
	}

	IWindow * LibLoader::initEntryPointDisplay() const {
		IWindow *(*create)() = reinterpret_cast<IWindow *(*)()>(getFunctionDynamicLib(this->_moduleHandle, "createInstance"));
		if (!create)
			throw DllException("Error cannot createInstance function");
		return (*create)();
	}

	IEvent * LibLoader::initEntryPointEvent(std::shared_ptr<IWindow> win) const {
		IEvent *(*create)(std::shared_ptr<IWindow>  &) = reinterpret_cast<IEvent *(*)(std::shared_ptr<IWindow>  &)>(getFunctionDynamicLib(this->_moduleHandle, "createEvent"));
		if (!create)
			throw DllException("Error cannot createEvent function");
		return (*create)(win);
	}

	IGameModule * LibLoader::initEntryPointGame() const {
		IGameModule *(*create)() = reinterpret_cast<IGameModule *(*)()>(getFunctionDynamicLib(this->_moduleHandle, "createGame"));
		if (!create)
			throw DllException("Error cannot createGame function");
		return (*create)();
	}

	IMenu * LibLoader::initEntryPointMenu() const {
		IMenu *(*create)() = reinterpret_cast<IMenu *(*)()>(getFunctionDynamicLib(this->_moduleHandle, "createMenu"));
		if (!create)
			throw DllException("Error cannot createMenu function");
		return (*create)();
	}

	void LibLoader::closeLib() {
		if (this->_moduleHandle) {
			std::cout << "Closing library: " << this->_modulePath << std::endl;
			closeDynamicLib(this->_moduleHandle);
			this->_moduleHandle = nullptr;
		} else {
			std::cout << "No library to close." << std::endl;
		}
	}

	LibLoader::~LibLoader() {
		this->closeLib();
	}
}
