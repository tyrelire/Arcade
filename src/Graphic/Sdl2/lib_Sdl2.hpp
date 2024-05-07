/**
 * @file LIB_SDL2.hpp
 * @author COUSTABEAU Maxime / MIGLIANI Benjamin / LAMAN-DUFLOT Ilhan (maxime.coustabeau@epitech.eu / benjamin.migliani@epitech.eu / Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../IGraphic.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#ifndef LIB_SDL2_HPP
#define LIB_SDL2_HPP

/**
 * @brief Implementation of the SDL2 graphics library for handling arcade graphics.
 *
 * @details This class inherits from IGraphic and provides concrete implementations for SDL2-based graphics handling.
 * It includes methods for initializing graphics, drawing menus, managing events, updating graphics, handling sounds, and providing getters/setters for various properties.
 */
class LIB_SDL2 : public IGraphic
{
    public:
        // Loader
        LIB_SDL2(); /**< Constructor for initializing SDL2 library. */
        ~LIB_SDL2(); /**< Destructor for cleaning up SDL2 resources. */

        // Init
        void init() override; /**< Initializes the SDL2 graphics. */

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
        SDL_Window* window; /**< SDL window object. */
        SDL_Renderer* renderer; /**< SDL renderer object. */
        TTF_Font* font; /**< SDL font object. */
        SDL_Texture* backgroundTexture; /**< SDL texture for background. */
        Mix_Music *music; /**< SDL music object. */

        struct MenuItem {
            SDL_Texture* texture; /**< Texture for menu item. */
            SDL_Texture* hoverTexture; /**< Texture for hovered menu item. */
            SDL_Rect rect; /**< Rectangular area for menu item. */
        };

        std::vector<MenuItem> menuItems; /**< Vector of menu items. */
        std::vector<MenuItem> pauseItems; /**< Vector of pause menu items. */
        std::vector<MenuItem> endItems; /**< Vector of end game menu items. */
        std::vector<MenuItem> settingsItems; /**< Vector of settings menu items. */

        std::string _playerName; /**< Player's name. */

        bool _writen; /**< Flag indicating if text is written. */

        int _selectedItem; /**< Index of the selected menu item. */

        std::string _nameLib; /**< Name of the graphics library. */

        int _imgLoaded; /**< Number of images loaded. */
};

/**
 * @brief Enumeration for different types of menus.
 */
enum typeMenu
{
    mainMenu, /**< Main menu type. */
    inGame, /**< In-game menu type. */
    pauseMenu, /**< Pause menu type. */
    endMenu, /**< End game menu type. */
    settingsMenu /**< Settings menu type. */
};

#endif // !LIB_SDL2_HPP
