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

#endif /* !Exception_HPP_ */
