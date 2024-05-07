/**
 * @file IGameLib.hpp
 * @author COUSTABEAU Maxime (maxime.coustabeau@epitech.eu) / MIGLIANI Benjamin (benjamin.migliani@epitech.eu) / LAMAN-DUFLOT Ilhan (Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 *        Main entry point for the Arcade application. Handles command line arguments, initializes Arcade, and manages user interaction.
 * @version 0.1
 * @date 2024-03-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <string>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

/**
 * @brief Interface for Game Library.
 *
 * @details This class defines a set of virtual methods for handling game logic and data in an arcade system.
 * It provides methods for initializing the game, stopping it, updating game state, and handling player movement.
 * Additionally, it includes getters and setters for accessing and modifying game data such as score, game map, game name, game over status, and number of food items.
 */
class IGameLib {
    public:
        ~IGameLib() = default;

        /**
         * @brief Initializes the game.
         */
        virtual void init() = 0;

        /**
         * @brief Stops the game.
         */
        virtual void stop() = 0;

        /**
         * @brief Updates the game state.
         */
        virtual void update_game() = 0;

        /**
         * @brief Updates the game map.
         */
        virtual void update_map() = 0;

        /**
         * @brief Moves the player in the game.
         *
         * @param nextDirection The next direction the player intends to move.
         * @param prevDirection The previous direction the player was moving in.
         * @return The result of the move operation.
         */
        virtual int move(int nextDirection, int prevDirection) = 0;

        // Getter
        /**
         * @brief Gets the current score of the game.
         *
         * @return The current score.
         */
        virtual int get_score() = 0;

        /**
         * @brief Gets the game map.
         *
         * @return Vector of tuples representing game elements.
         */
        virtual std::vector<std::tuple<char, std::string, int, int>> get_gameMap() = 0;

        /**
         * @brief Gets the name of the game.
         *
         * @return The name of the game.
         */
        virtual std::string get_gameName() = 0;

        /**
         * @brief Checks if the game is over.
         *
         * @return True if the game is over, false otherwise.
         */
        virtual bool get_gameOver() = 0;

        /**
         * @brief Gets the number of food items in the game.
         *
         * @return The number of food items.
         */
        virtual int get_nbFood() = 0;

        // Setter
        /**
         * @brief Sets the score of the game.
         *
         * @param scoreValue The value to set as the score.
         */
        virtual void set_score(int scoreValue) = 0;

        /**
         * @brief Sets the game map entry.
         *
         * @param entry The tuple representing a game element to set in the game map.
         */
        virtual void set_gameMap(const std::tuple<char, std::string, int, int>& entry) = 0;
};
