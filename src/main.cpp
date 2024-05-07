/**
 * @file main.cpp
 * @author COUSTABEAU Maxime (maxime.coustabeau@epitech.eu) / MIGLIANI Benjamin (benjamin.migliani@epitech.eu) / LAMAN-DUFLOT Ilhan (Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 *        Main entry point for the Arcade application. Initializes Arcade, and manages user interaction.
 * @version 0.1
 * @date 2024-03-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <stdexcept>
#include <dlfcn.h>

#include "./Core/ICore.hpp"

/**
 * @brief Displays Arcade's help message.
 *
 * @details This function prints usage information for the program.
 */
void printHelp()
{
    std::cout << "Usage: ./arcade [lib.so]" << std::endl;
    std::cout << "\tHelp : -Help -help -H -h" << std::endl;
}

/**
 * @brief Main function for Arcade.
 *
 * @details This function handles command line arguments, initializes Arcade, and manages user interaction.
 * The program supports a help message ("-h" or "-H" or -help" or "-Help") and a debug mode ("-Debug or -debug or -D or -d").
 *
 * @param ac Number of command line arguments.
 * @param av Array of pointers to strings representing command line arguments.
 * @return int Exit status (0 for success, 84 for errors).
 */
int main(int ac, char **av)
{
    try {
        if (ac == 2) {
            Loader <IGraphic> loader;
            Loader <IGameLib> loaderG;
            loader.loadNCURSES = 0;
            loader.loadSDL2 = 0;
            loader.loadSFML = 0;

            loader.swapLib(av[1]);

            Core *core = new Core();

            core->run(&loader, &loaderG);

            return 0;
        } else {
            throw std::invalid_argument("Error: invalid arguments value");
        }
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}