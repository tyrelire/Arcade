/**
 * @file Sfml.hpp
 * @author COUSTABEAU Maxime / MIGLIANI Benjamin / LAMAN-DUFLOT Ilhan (maxime.coustabeau@epitech.eu / benjamin.migliani@epitech.eu / Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "../IGraphic.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>

/**
 * @brief Implementation of the SFML graphics library for handling arcade graphics.
 *
 * @details This class inherits from IGraphic and provides concrete implementations for SFML-based graphics handling.
 * It includes methods for initializing graphics, drawing menus, managing events, updating graphics, handling sounds, and providing getters/setters for various properties.
 */
class LIB_SFML: public IGraphic
{
    public:
        // Loader
        LIB_SFML(); /**< Constructor for initializing SFML library. */
        ~LIB_SFML(); /**< Destructor for cleaning up SFML resources. */

        // Init
        void init() override; /**< Initializes the SFML graphics. */

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
        sf::RenderWindow* window; /**< SFML window object. */
        sf::Event event; /**< SFML event object. */
        sf::Font font; /**< SFML font object. */
        sf::Texture backgroundTexture; /**< SFML texture for background. */
        sf::Sprite backgroundSprite; /**< SFML sprite for background. */
        std::vector<sf::Text> menuItems; /**< Vector of SFML text objects for menu items. */
        std::vector<sf::Text> pauseItems; /**< Vector of SFML text objects for pause menu items. */
        std::vector<sf::Text> settingsItems; /**< Vector of SFML text objects for settings menu items. */
        std::vector<sf::Text> endItems; /**< Vector of SFML text objects for end game menu items. */

        std::string _playerName; /**< Player's name. */

        bool _writen; /**< Flag indicating if text is written. */
        bool _playgame; /**< Flag indicating if the game is being played. */

        sf::Music music; /**< SFML music object. */

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
