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
		this->_getModuleType = reinterpret_cast<GetModuleTypeFct>(getFunctionDynamicLib(this->_moduleHandle, "getModuleType"));
		if (!this->_getModuleType)
			throw DllException("Error cannot getModuleType function");
		this->_moduleType = this->_getModuleType();
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
