/**
 * @file DynamicLib.hpp
 * @brief Header file for dynamic library handling functions.
 *
 * This file provides declarations for functions to load, retrieve symbols from,
 * and close dynamic libraries, as well as retrieve error messages related to
 * dynamic library operations.
 *
 * @author EPITECH PROJECT
 * @date 2025
 */

/*
** EPITECH PROJECT, 2025
** barcade
** File description:
** DynamicLib
*/

#ifndef DYNAMICLIB_HPP_
    #define DYNAMICLIB_HPP_

extern "C" {
    /**
     * @brief Opens a dynamic library.
     *
     * This function loads a dynamic library from the specified path and returns
     * a handle to the loaded library.
     *
     * @param path The file path to the dynamic library.
     * @return A handle to the loaded library, or nullptr if an error occurs.
     */
    void *openDynamicLib(const char *path);

    /**
     * @brief Retrieves a function or symbol from a dynamic library.
     *
     * This function retrieves the address of a function or symbol from a loaded
     * dynamic library using its handle and the symbol's name.
     *
     * @param moduleHandle The handle to the loaded dynamic library.
     * @param name The name of the function or symbol to retrieve.
     * @return A pointer to the function or symbol, or nullptr if an error occurs.
     */
    void *getFunctionDynamicLib(void *moduleHandle, const char *name);

    /**
     * @brief Closes a dynamic library.
     *
     * This function closes a previously loaded dynamic library and releases
     * associated resources.
     *
     * @param moduleHandle The handle to the loaded dynamic library.
     */
    void closeDynamicLib(void *moduleHandle);

    /**
     * @brief Retrieves the last dynamic library error message.
     *
     * This function returns a string describing the last error that occurred
     * during a dynamic library operation.
     *
     * @return A string describing the last error, or nullptr if no error occurred.
     */
    const char *getDlError(void);
}

#endif /* !DYNAMICLIB_HPP_ */
