/**
 * @file IGraphic.hpp
 * @author COUSTABEAU Maxime / MIGLIANI Benjamin / LAMAN-DUFLOT Ilhan (maxime.coustabeau@epitech.eu / benjamin.migliani@epitech.eu / Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef IGRAPHIC_HPP
#define IGRAPHIC_HPP

#include <string>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

/**
 * @brief Interface for Graphic handling.
 *
 * @details This class defines a set of virtual methods for handling graphics in an arcade system.
 * It provides methods for initializing graphics, drawing menus, managing events, updating graphics, and handling sounds.
 */
class IGraphic {
    public:
        virtual ~IGraphic() = default;

        // Init
        /**
         * @brief Initializes the graphics.
         */
        virtual void init() = 0;

        // Menu
        /**
         * @brief Generates the main menu.
         *
         * @return String representing the main menu.
         */
        virtual const std::string main_menu() = 0;

        /**
         * @brief Generates the end game menu.
         *
         * @param playerName Name of the player.
         * @param score Score achieved by the player.
         * @return String representing the end game menu.
         */
        virtual const std::string end_menu(std::string playerName, int score) = 0;

        /**
         * @brief Generates the pause menu.
         *
         * @return String representing the pause menu.
         */
        virtual const std::string pause_menu() = 0;

        /**
         * @brief Generates the settings menu.
         *
         * @return String representing the settings menu.
         */
        virtual const std::string settings_menu() = 0;

        /**
         * @brief Generates the game menu.
         *
         * @param _gameMap Vector of tuples representing game elements.
         * @param nameGame Name of the game.
         * @return String representing the game menu.
         */
        virtual const std::string game_menu(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame) = 0;

        // Draw
        /**
         * @brief Draws the game.
         */
        virtual void draw_game() = 0;

        /**
         * @brief Draws the score.
         */
        virtual void draw_score() = 0;

        /**
         * @brief Draws the player's name.
         */
        virtual void draw_playerName() = 0;

        /**
         * @brief Draws all sprites.
         */
        virtual void draw_allSprite() = 0;

        /**
         * @brief Draws the map of the game.
         *
         * @param _gameMap Vector of tuples representing game elements.
         * @param nameGame Name of the game.
         */
        virtual void draw_map(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame) = 0;

        // Event
        /**
         * @brief Closes the graphics.
         */
        virtual void close() = 0;

        /**
         * @brief Stops the graphics.
         */
        virtual void stop() = 0;

        /**
         * @brief Pauses the graphics.
         */
        virtual void pause() = 0;

        /**
         * @brief Clears the graphics.
         */
        virtual void clear() = 0;

        // Update
        /**
         * @brief Updates the graphics.
         */
        virtual void update() = 0;

        // Sound
        /**
         * @brief Plays a sound.
         *
         * @param pathMusic Path to the sound file.
         * @param volume Volume level of the sound.
         */
        virtual void sound(std::string pathMusic, int volume) = 0;

        /**
         * @brief Sets the volume level.
         *
         * @param value Volume level.
         */
        virtual void set_volume(int value) = 0;

        // Setter
        /**
         * @brief Sets the player's name.
         *
         * @param name Player's name.
         */
        virtual void set_playerName(std::string name) = 0;

        /**
         * @brief Sets the selected item index.
         *
         * @param index Index of the selected item.
         */
        virtual void set_selectedItem(int index) = 0;

        /**
         * @brief Sets the name of the graphics library.
         *
         * @param lib Name of the graphics library.
         */
        virtual void set_nameLib(std::string lib) = 0;

        // Getter
        /**
         * @brief Gets the player's name.
         *
         * @return Player's name.
         */
        virtual const std::string get_playerName() = 0;

        /**
         * @brief Gets the index of the selected item.
         *
         * @return Index of the selected item.
         */
        virtual int get_selectedItem() = 0;

        /**
         * @brief Gets the name of the graphics library.
         *
         * @return Name of the graphics library.
         */
        virtual const std::string get_nameLib() = 0;
};

#endif // !IGRAPHIC_HPP
