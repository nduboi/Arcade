/**
 * @file LibLoader.hpp
 * @brief Header file for the LibLoader class, responsible for dynamically loading modules.
 * 
 * This file defines the LibLoader class, which provides functionality to load and manage
 * dynamic libraries (modules) at runtime. It includes methods to retrieve module information
 * such as type, path, and name, as well as to create display module objects.
 * 
 * @author Roussiere Noa
 * @date 2023
 */

#ifndef LIBLOADER_HPP
#define LIBLOADER_HPP

#include <memory>
#include "IWindow.hpp"
#include "IEvent.hpp"
#include "LoaderType.hpp"
#include "Exception.hpp"
#include "DynamicLib.hpp"

namespace Loader
{
	/**
	 * @class LibLoader
	 * @brief A class for dynamically loading and managing modules.
	 * 
	 * The LibLoader class is responsible for loading dynamic libraries (modules) at runtime.
	 * It provides methods to retrieve module type, path, and name, and to create instances
	 * of display modules.
	 */
	class LibLoader {
	protected:
		void *_moduleHandle = nullptr; /**< Handle to the loaded module. */
		std::string _modulePath; /**< Path to the module file. */
		Loader::ModuleType_t _moduleType = Loader::ModuleType_t::TYPE_COUNT; /**< Type of the module. */

		typedef Loader::ModuleType_t (*GetModuleTypeFct)(); /**< Function pointer to retrieve module type. */
		GetModuleTypeFct _getModuleType = nullptr; /**< Pointer to the function that retrieves module type. */

	public:

		/**
		 * @brief Get the type of the loaded module.
		 * @return The type of the module as a Loader::ModuleType_t.
		 */
		Loader::ModuleType_t getModuleType() const {return this->_moduleType;};

		/**
		 * @brief Get the path of the loaded module.
		 * @return The path of the module as a C-style string.
		 */
		const char *getModulePath() const {return this->_modulePath.c_str();};

		/**
		 * @brief Initializes and retrieves an instance of a class from a dynamically loaded library.
		 * 
		 * This template function attempts to locate and invoke the "getClass" function from a dynamically
		 * loaded library. The "getClass" function is expected to return a pointer to an instance of the
		 * specified class type `T`. If the function cannot be found or invoked, an exception is thrown.
		 * 
		 * @tparam T The type of the class to be instantiated.
		 * @return T* A pointer to an instance of the specified class type `T`.
		 * @throws DllException If the "getClass" function cannot be retrieved or invoked.
		 */
		IWindow *initEntryPointDisplay() const;
		IEvent *initEntryPointEvent(IWindow &win) const;

		/**
		 * @brief Closes the currently loaded library.
		 * 
		 * This function is responsible for properly unloading and releasing
		 * any resources associated with the dynamically loaded library.
		 * It ensures that the library is no longer in use and prevents
		 * resource leaks.
		 */
		void closeLib();
		/**
		 * @brief Opens a shared library from the specified file path.
		 * 
		 * This function attempts to load a shared library located at the given
		 * file path. It is typically used to dynamically load external libraries
		 * at runtime.
		 * 
		 * @param path The file path to the shared library to be loaded.
		 *             It should be a valid path to a shared library file.
		 * 
		 * @throws std::runtime_error If the library cannot be opened or loaded.
		 */
		void openLib(const std::string &path);

		/**
		 * @brief Constructor for the LibLoader class.
		 * 
		 * Initializes the LibLoader object
		 * 
		 */
		LibLoader() = default;

		/**
		 * @brief Destructor for the LibLoader class.
		 * 
		 * Cleans up resources and unloads the module if it is loaded.
		 */
		~LibLoader();
	};
}
#endif //LIBLOADER_HPP
