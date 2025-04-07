/**
 * @file Exception.hpp
 * @brief Exception class for handling DLL-related errors in the barcade project.
 *
 * This file contains the definition of the DllException class, WindowException class.
 *
 * @date 3/18/25
 */

/*
** EPITECH PROJECT, 2025
** barcade
** File description:
** Exception
*/

#ifndef Exception_HPP_
#define Exception_HPP_
#include <exception>
#include <string>

/**
 * @class DllException
 * @brief Exception class for handling DLL-related errors.
 *
 * The DllException class is used to handle errors related to loading and
 * managing DLLs.
 */
class DllException : public std::exception {
    private:
        std::string _msg; ///< Error message.

    public:
        /**
         * @brief Returns the error message.
         * @return The error message.
         */
        const char *what() const noexcept override { return this->_msg.c_str(); }
        /**
         * @brief Constructor for DllException.
         * @param msg The error message.
         */
        DllException(const std::string &msg) : _msg(msg) {}
        /**
         * @brief Destructor for DllException.
         */
        ~DllException() = default;
};

/**
 * @class WindowException
 * @brief Exception class for handling DLL-related errors.
 *
 * The WindowException class is used to handle errors related to display module
 *
 */
class WindowException : public std::exception {
private:
    std::string _msg; ///< Error message.

public:
    /**
     * @brief Returns the error message.
     * @return The error message.
     */
    const char *what() const noexcept override { return this->_msg.c_str(); }
    /**
     * @brief Constructor for WindowException.
     * @param msg The error message.
     */
    WindowException(const std::string &msg) : _msg(msg) {}
    /**
     * @brief Destructor for WindowException.
     */
    ~WindowException() = default;
};

/**
 * @class CoreException
 * @brief Exception class for handling DLL-related errors.
 *
 * The CoreException class is used to handle errors related to display module
 *
 */
class CoreException : public std::exception {
private:
    std::string _msg; ///< Error message.

public:
    /**
     * @brief Returns the error message.
     * @return The error message.
     */
    const char *what() const noexcept override { return this->_msg.c_str(); }
    /**
     * @brief Constructor for CoreException.
     * @param msg The error message.
     */
    CoreException(const std::string &msg) : _msg(msg) {}
    /**
     * @brief Destructor for CoreException.
     */
    ~CoreException() = default;
};

/**
 * @class HelpException
 * @brief Exception class for handling DLL-related errors.
 *
 * The HelpException class is used to handle errors related to display module
 *
 */
class HelpException : public std::exception {
public:
    /**
     * @brief Constructor for HelpException.
     */
    HelpException() = default;
    /**
     * @brief Destructor for HelpException.
     */
    ~HelpException() = default;
};

/**
 * @class GameModuleException
 * @brief Exception class for handling DLL-related errors.
 *
 * The GameModuleException class is used to handle errors related to display module
 *
 */
class GameModuleException : public std::exception {
private:
    std::string _msg; ///< Error message.

public:
    /**
     * @brief Returns the error message.
     * @return The error message.
     */
    const char *what() const noexcept override { return this->_msg.c_str(); }
    /**
     * @brief Constructor for GameModuleException.
     * @param msg The error message.
     */
    GameModuleException(const std::string &msg) : _msg(msg) {}
    /**
     * @brief Destructor for GameModuleException.
     */
    ~GameModuleException() = default;
};

/**
 * @class MenuModuleException
 * @brief Exception class for handling DLL-related errors.
 *
 * The MenuModuleException class is used to handle errors related to display module
 *
 */
class MenuModuleException : public std::exception {
private:
    std::string _msg; ///< Error message.

public:
    /**
     * @brief Returns the error message.
     * @return The error message.
     */
    const char *what() const noexcept override { return this->_msg.c_str(); }
    /**
     * @brief Constructor for MenuModuleException.
     * @param msg The error message.
     */
    MenuModuleException(const std::string &msg) : _msg(msg) {}
    /**
     * @brief Destructor for MenuModuleException.
     */
    ~MenuModuleException() = default;
};

/**
 * @class EventModuleException
 * @brief Exception class for handling DLL-related errors.
 *
 * The EventModuleException class is used to handle errors related to display module
 *
 */
class EventModuleException : public std::exception {
private:
    std::string _msg; ///< Error message.

public:
    /**
     * @brief Returns the error message.
     * @return The error message.
     */
    const char *what() const noexcept override { return this->_msg.c_str(); }
    /**
     * @brief Constructor for EventModuleException.
     * @param msg The error message.
     */
    EventModuleException(const std::string &msg) : _msg(msg) {}
    /**
     * @brief Destructor for EventModuleException.
     */
    ~EventModuleException() = default;
};

/**
 * @class EntityModuleException
 * @brief Exception class for handling DLL-related errors.
 *
 * The EntityModuleException class is used to handle errors related to display module
 *
 */
class EntityModuleException : public std::exception {
private:
    std::string _msg; ///< Error message.

public:
    /**
     * @brief Returns the error message.
     * @return The error message.
     */
    const char *what() const noexcept override { return this->_msg.c_str(); }
    /**
     * @brief Constructor for EntityModuleException.
     * @param msg The error message.
     */
    EntityModuleException(const std::string &msg) : _msg(msg) {}
    /**
     * @brief Destructor for EntityModuleException.
     */
    ~EntityModuleException() = default;
};

/**
 * @class ProgramCoreException
 * @brief Exception class for handling DLL-related errors.
 *
 * The ProgramCoreException class is used to handle errors related to the program 
 * core
 */
class ProgramCoreException : public std::exception {
    private:
        std::string _msg; ///< Error message.

    public:
        /**
         * @brief Returns the error message.
         * @return The error message.
         */
        const char *what() const noexcept override { return this->_msg.c_str(); }
        /**
         * @brief Constructor for ProgramCoreException.
         * @param msg The error message.
         */
        ProgramCoreException(const std::string &msg) : _msg(msg) {}
        /**
         * @brief Destructor for ProgramCoreException.
         */
        ~ProgramCoreException() = default;
};

/**
 * @class NcursesException
 * @brief Exception class for handling DLL-related errors.
 *
 * The NcursesException class is used to handle errors related to the program
 * core
 */
class NcursesException : public std::exception {
private:
    std::string _msg; ///< Error message.

public:
    /**
     * @brief Returns the error message.
     * @return The error message.
     */
    const char *what() const noexcept override { return this->_msg.c_str(); }
    /**
     * @brief Constructor for NcursesException.
     * @param msg The error message.
     */
    NcursesException(const std::string &msg) : _msg(msg) {}
    /**
     * @brief Destructor for NcursesException.
     */
    ~NcursesException() = default;
};

/**
 * @class SDLException
 * @brief Exception class for handling DLL-related errors.
 *
 * The SDLException class is used to handle errors related to the program
 * core
 */
class SDLException : public std::exception {
private:
    std::string _msg; ///< Error message.

public:
    /**
     * @brief Returns the error message.
     * @return The error message.
     */
    const char *what() const noexcept override { return this->_msg.c_str(); }
    /**
     * @brief Constructor for SDLException.
     * @param msg The error message.
     */
    SDLException(const std::string &msg) : _msg(msg) {}
    /**
     * @brief Destructor for SDLException.
     */
    ~SDLException() = default;
};

#endif /* !Exception_HPP_ */
