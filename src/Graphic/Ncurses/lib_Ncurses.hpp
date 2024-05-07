/**
 * @file lib_Ncurses.hpp
 * @author COUSTABEAU Maxime / MIGLIANI Benjamin / LAMAN-DUFLOT Ilhan (maxime.coustabeau@epitech.eu / benjamin.migliani@epitech.eu / Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../IGraphic.hpp"
#include <cmath>
#include <ncurses.h>
#include <menu.h>
#include <string.h>
#include <cstring>
#include <deque>
#include <thread>
#include <chrono>

#ifndef LIB_NCURSES_HPP
#define LIB_NCURSES_HPP

/**
 * @brief Implementation of the NCURSES graphics library for handling arcade graphics.
 *
 * @details This class inherits from IGraphic and provides concrete implementations for NCURSES-based graphics handling.
 * It includes methods for initializing graphics, drawing menus, managing events, updating graphics, handling sounds, and providing getters/setters for various properties.
 */
class LIB_NCURSES : public IGraphic
{
    public:
        // Loader
        LIB_NCURSES(); /**< Constructor for initializing NCURSES library. */
        ~LIB_NCURSES(); /**< Destructor for cleaning up NCURSES resources. */

        // Init
        void init() override; /**< Initializes the NCURSES graphics. */

        // Menu
        const std::string main_menu() override; /**< Generates the main menu. */
        const std::string end_menu(std::string playerName, int score) override; /**< Generates the end game menu. */
        const std::string pause_menu() override; /**< Generates the pause menu. */
        const std::string settings_menu() override; /**< Generates the settings menu. */
        const std::string game_menu(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame) override; /**< Generates the game menu. */

        // Draw
        void draw_game() override; /**< Draws the game. */
        void draw_score() override; /**< Draws the score. */
        void draw_playerName() override; /**< Draws the player's name. */
        void draw_allSprite() override; /**< Draws all sprites. */
        void draw_map(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame) override; /**< Draws the game map. */

        // Event
        void stop() override; /**< Stops the graphics. */
        void pause() override; /**< Pauses the graphics. */
        void clear() override; /**< Clears the graphics. */
        void close() override; /**< Closes the graphics. */

        // Update
        void update() override; /**< Updates the graphics. */

        // Sound
        void sound(std::string pathMusic, int volume) override; /**< Plays a sound. */
        void set_volume(int value) override; /**< Sets the volume level. */

        // Setter
        void set_playerName(std::string name) override; /**< Sets the player's name. */
        void set_selectedItem(int index) override; /**< Sets the selected item index. */
        void set_nameLib(std::string lib) override; /**< Sets the name of the graphics library. */

        // Getter
        const std::string get_playerName() override; /**< Gets the player's name. */
        int get_selectedItem() override; /**< Gets the index of the selected item. */
        const std::string get_nameLib() override; /**< Gets the name of the graphics library. */


    private:
        bool game_paused = false; /**< Flag indicating if the game is paused. */
        std::string _playerName; /**< Player's name. */
        WINDOW *game_win; /**< NCURSES window object for the game. */
        int _selectedItem; /**< Index of the selected menu item. */

        std::string _nameLib; /**< Name of the graphics library. */
};

/**
 * @brief Enumeration for different types of menus.
 */
enum typeMenu
{
    mainMenu, /**< Main menu type. */
    inGame, /**< In-game menu type. */
    pauseMenu, /**< Pause menu type. */
    settingsMenu, /**< Settings menu type. */
    endMenu /**< End game menu type. */
};

#endif // !NCURSES_HPP
