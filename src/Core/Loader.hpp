/**
 * @file Loader.hpp
 * @author COUSTABEAU Maxime (maxime.coustabeau@epitech.eu) / MIGLIANI Benjamin (benjamin.migliani@epitech.eu) / LAMAN-DUFLOT Ilhan (Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 *        Implementation of the Exception class for handling exceptions in the arcade application.
 * @version 0.1
 * @date 2024-03-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <dirent.h>
#include <vector>
#include <iostream>
#include <dlfcn.h>

/**
 * @brief Generic class for dynamically loading shared libraries and instantiating objects from them.
 *
 * @details This class provides functionality for loading shared libraries dynamically and creating instances of objects from them.
 * It supports loading libraries at runtime, swapping between loaded libraries, and obtaining paths to available libraries.
 *
 * @tparam ClassContainer The class type to be instantiated from the loaded library.
 */
template<typename ClassContainer>
class Loader {
    public:
        /**
         * @brief Default constructor.
         */
        Loader() : _loadedLib(nullptr), _path(pathLib()), _lib(0) {}

        /**
         * @brief Constructor with a specified library file name.
         *
         * @param fn The file name of the library to load.
         */
        Loader(const std::string& fn) : _loadedLib(dlopen(fn.c_str(), RTLD_LAZY)), _path(pathLib()) {
            _lib = currLib(fn);
        }

        /**
         * @brief Destructor for cleaning up resources.
         */
        ~Loader() {
            (_loadedLib != nullptr) ? dlclose(_loadedLib) : 0;
        }

        /**
         * @brief Creates an instance of the specified class from the loaded library.
         *
         * @param param The name of the class to instantiate.
         * @return A pointer to the instantiated object.
         */
        ClassContainer* currInst(const std::string& param) {
            ClassContainer* layer = nullptr;

            if (_loadedLib != nullptr) {
                typedef ClassContainer* (*create_t)();
                create_t create = reinterpret_cast<create_t>(dlsym(_loadedLib, param.c_str()));
                if (create != nullptr) {
                    layer = create();
                } else {
                    std::cerr << "Failed to find " << param << " in library\n";
                }
            } else {
                std::cerr << "Failed to load library\n" << dlerror() << std::endl;
            }
            return layer;
        }

        /**
         * @brief Obtains paths to available libraries in a directory.
         *
         * @return A vector of strings representing library paths.
         */
        std::vector<std::string> pathLib() {
            DIR *Directory;
            struct dirent *ent;
            std::vector<std::string> location;

            if ((Directory = opendir ("./lib")) != NULL) {
                for (struct dirent* ent = readdir(Directory); ent != NULL; ent = readdir(Directory)) {
                    if (ent->d_name[0] == '.') {
                        continue;
                    } else {
                        std::string tmp = "./lib/" + std::string(ent->d_name);
                        location.push_back(tmp);
                    }
                }
                closedir (Directory);
            } else {
                std::cerr << "Failed to open directory" << std::endl;
            }
            return location;
        }

        /**
         * @brief Swaps the currently loaded library with another one.
         *
         * @param fn The file name of the library to load.
         */
        void swapLib(const char* fn) {
            if (_loadedLib != nullptr) {
                dlclose(_loadedLib);
            }

            _loadedLib = dlopen(fn, RTLD_LAZY);
        }

        /**
         * @brief Retrieves the index of a library in the library path vector.
         *
         * @param lib The file name of the library.
         * @return The index of the library in the path vector.
         */
        int currLib(std::string lib) {
            int i = 0;
            while (i < _path.size()) {
                if (_path[i] == lib) {
                    return i;
                }
                i++;
            }
            return 0;
        }

    public:
        void *_loadedLib; /**< Pointer to the loaded library. */

        std::vector<std::string> _path; /**< Vector containing paths to available libraries. */
        int _lib; /**< Index of the current library in the path vector. */

        int loadSDL2; /**< Indicator for SDL2 library loading status. */
        int loadNCURSES; /**< Indicator for NCURSES library loading status. */
        int loadSFML; /**< Indicator for SFML library loading status. */
};
