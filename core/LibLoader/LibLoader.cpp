//
// Created by roussierenoa on 3/17/25.
//

#include <iostream>
#include <stdexcept>
#include "LibLoader.hpp"

namespace Loader {
	void LibLoader::openLib(const std::string &path)
	{
		std::cout << "Opening library: " << path << std::endl;
		if (this->_moduleHandle)
			this->closeLib();
		try {
			this->_moduleHandle = dlopen(path.c_str(), RTLD_LAZY);
			if (!this->_moduleHandle)
				throw std::exception();
		} catch (...) {
			throw DllException("Error during dlopen("+path+", ...): " + std::string(dlerror()));
		}

		//Todo bouger ça \/ retirer du constructeur
		this->_getModuleType = reinterpret_cast<GetModuleTypeFct>(dlsym(this->_moduleHandle, "getType"));
		if (!this->_getModuleType)
			throw DllException("Error cannot getType function");
		this->_moduleType = this->_getModuleType();
		std::cout << "Library loaded successfully: " << path << std::endl;
	}

	void LibLoader::closeLib() {
		if (this->_moduleHandle) {
			std::cout << "Closing library: " << this->_modulePath << std::endl;
			dlclose(this->_moduleHandle);
			this->_moduleHandle = nullptr;
		} else {
			std::cout << "No library to close." << std::endl;
		}
		this->_moduleHandle = nullptr;
	}

	LibLoader::~LibLoader() {
		this->closeLib();
	}
}
