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
		this->_modulePath = path;
		this->closeLib();
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
	}

	IWindow * LibLoader::initEntryPointDisplay() const {
		IWindow *(*create)() = reinterpret_cast<IWindow *(*)()>(getFunctionDynamicLib(this->_moduleHandle, "createInstance"));
		if (!create)
			throw DllException("Error cannot createInstance function");
		return (*create)();
	}

	IEvent * LibLoader::initEntryPointEvent(IWindow &win) const {
		IEvent *(*create)(IWindow &) = reinterpret_cast<IEvent *(*)(IWindow &)>(getFunctionDynamicLib(this->_moduleHandle, "createEvent"));
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
		if (this->_moduleHandle)
			closeDynamicLib(this->_moduleHandle);
		this->_moduleHandle = nullptr;
	}

	LibLoader::~LibLoader() {
		if (this->_moduleHandle)
			closeDynamicLib(this->_moduleHandle);
		this->_moduleHandle = nullptr;
	}
}
