/**
 * @file ICore.hpp
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

#include <string>
#include "../Game/IGameLib.hpp"
#include "../Graphic/IGraphic.hpp"
#include "Loader.hpp"

/**
 * @brief Core class responsible for managing the main game loop and coordinating interactions between graphics and game logic.
 *
 * @details This class orchestrates the main game loop, handles user input, and manages interactions between the graphics interface and game logic.
 * It provides methods for running the game, updating menus, switching between graphics libraries and game implementations, and setting/getting various game parameters.
 */
class Core {
    public:
        /**
         * @brief Constructor for initializing the Core.
         */
        Core();

        /**
         * @brief Destructor for cleaning up resources used by the Core.
         */
        ~Core();

        /**
         * @brief Runs the main game loop.
         * 
         * @param dl Pointer to the loader for graphics libraries.
         * @param dlG Pointer to the loader for game libraries.
         */
        void run(Loader <IGraphic> *dl, Loader <IGameLib> *dlG);

        /**
         * @brief Updates the menu based on the given event.
         * 
         * @param event The event triggering the menu update.
         * @param dl Pointer to the loader for graphics libraries.
         * @param dlG Pointer to the loader for game libraries.
         */
        void update_menu(const std::string event, Loader <IGraphic> *dl, Loader <IGameLib> *dlG);

        /**
         * @brief Switches the graphics library being used.
         * 
         * @param dl Pointer to the loader for graphics libraries.
         * @param lib The name of the library to switch to.
         */
        void switchLib(Loader <IGraphic> *dl, const char *lib);

        /**
         * @brief Switches the game library being used.
         * 
         * @param dl Pointer to the loader for game libraries.
         * @param game The name of the game library to switch to.
         */
        void switchGame(Loader <IGameLib> *dl, const char *game);

        // Setter
        void set_isRunning(bool run); /**< Sets the running state of the game. */
        void set_whichMenu(int menu); /**< Sets the current menu state. */
        void set_whichOldMenu(int menu); /**< Sets the previous menu state. */
        void set_volume(int value); /**< Sets the volume level. */
        void set_playerName(std::string name); /**< Sets the player's name. */
        void set_pathMusic(std::string name); /**< Sets the path to the music file. */
        void set_score(int value); /**< Sets the player's score. */

        // Getter
        bool get_isRunning(); /**< Gets the running state of the game. */
        int get_whichMenu(); /**< Gets the current menu state. */
        int get_whichOldMenu(); /**< Gets the previous menu state. */
        int get_volume(); /**< Gets the volume level. */
        const std::string get_playerName(); /**< Gets the player's name. */
        const std::string get_pathMusic(); /**< Gets the path to the music file. */
        int get_score(); /**< Gets the player's score. */

        // Setters
        void setDisplay(IGraphic *display) { _display = display; }; /**< Sets the graphics interface. */
        void setGame(IGameLib *game) { _game = game; }; /**< Sets the game logic. */

        // Getters
        IGraphic *getDisplay() const { return _display; }; /**< Gets the graphics interface. */
        IGameLib *getGame() const { return _game;}; /**< Gets the game logic. */

    protected:
        IGraphic *_display; /**< Pointer to the graphics interface. */
        IGameLib *_game; /**< Pointer to the game logic. */

    private:
        bool _isRunning; /**< Flag indicating if the game is running. */

        int _whichMenu; /**< Current menu state. */
        int _whichOldMenu; /**< Previous menu state. */

        int _volume; /**< Volume level. */

        std::string _playerName; /**< Player's name. */
        int _score; /**< Player's score. */

        std::string _pathMusic; /**< Path to the music file. */

        bool _enter; /**< Flag indicating if the Enter key is pressed. */

        int _nextDirection; /**< Next direction for player movement. */
        int _previousDirection; /**< Previous direction of player movement. */
        int _autoDirection; /**< Automatic direction for game movement. */
        int _autoDirectionTmp; /**< Temporary automatic direction for game movement. */

        bool _gameOver; /**< Flag indicating if the game is over. */
};

/**
 * @brief Enumeration for different types of menus.
 */
enum typeMenu
{
    mainMenu, /**< Main menu. */
    inGame, /**< In-game menu. */
    pauseMenu, /**< Pause menu. */
    settingsMenu, /**< Settings menu. */
    endMenu /**< End menu. */
};

/**
 * @brief Enumeration for different directions.
 */
enum direction
{
    top, /**< Up direction. */
    down, /**< Down direction. */
    left, /**< Left direction. */
    right, /**< Right direction. */
    none /**< No direction. */
};
