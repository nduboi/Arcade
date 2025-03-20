/**
 * @file LoaderType.hpp
 * @brief Defines the module types used in the Loader namespace.
 *
 * This file contains the definition of the `ModuleType_t` enumeration, which
 * categorizes the types of modules that can be loaded, such as display modules
 * and game modules.
 *
 * @namespace Loader
 * The `Loader` namespace encapsulates all types and definitions related to
 * module loading functionality.
 *
 * @enum Loader::ModuleType_t
 * @brief Enumeration of module types.
 *
 * @var Loader::ModuleType_t::DISPLAY_MODULE
 * Represents a display module type.
 *
 * @var Loader::ModuleType_t::GAME_MODULE
 * Represents a game module type.
 *
 * @var Loader::ModuleType_t::TYPE_COUNT
 * Represents the total count of module types.
 */
/*
** EPITECH PROJECT, 2025
** barcade
** File description:
** LoaderType
*/

#ifndef LOADERTYPE_HPP_
#define LOADERTYPE_HPP_

namespace Loader
{
    typedef enum ModuleType_s {
        DISPLAY_MODULE,
        GAME_MODULE,
        TYPE_COUNT
    } ModuleType_t;
} // namespace Loader


#endif /* !LOADERTYPE_HPP_ */
