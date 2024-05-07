/**
 * @file Nibbler.hpp
 * @author COUSTABEAU Maxime / MIGLIANI Benjamin / LAMAN-DUFLOT Ilhan (maxime.coustabeau@epitech.eu / benjamin.migliani@epitech.eu / Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef NIBBLER_HPP
#define NIBLLER_HPP

#include "../IGameLib.hpp"

/**
 * @brief Implementation of the Nibbler game logic.
 *
 * @details This class inherits from IGameLib and provides concrete implementations for the Nibbler game logic.
 * It includes methods for initializing the game, stopping it, updating game state, handling player movement, and accessing/modifying game data.
 */
class Nibbler : public IGameLib
{
    public:
        Nibbler(); /**< Constructor for initializing the Nibbler game. */
        ~Nibbler(); /**< Destructor for cleaning up Nibbler game resources. */

        /**
         * @brief Initializes the Nibbler game.
         */
        void init() override;

        /**
         * @brief Stops the Nibbler game.
         */
        void stop() override;

        /**
         * @brief Updates the Nibbler game state.
         */
        void update_game() override;

        /**
         * @brief Updates the Nibbler game map.
         */
        void update_map() override;

        /**
         * @brief Moves the Nibbler player.
         *
         * @param nextDirection The next direction the player intends to move.
         * @param prevDirection The previous direction the player was moving in.
         * @return The result of the move operation.
         */
        int move(int nextDirection, int prevDirection) override;

        // Getter
        /**
         * @brief Gets the current score of the Nibbler game.
         *
         * @return The current score.
         */
        int get_score() override;

        /**
         * @brief Gets the game map of the Nibbler game.
         *
         * @return Vector of tuples representing game elements.
         */
        std::vector<std::tuple<char, std::string, int, int>> get_gameMap() override;

        /**
         * @brief Gets the name of the Nibbler game.
         *
         * @return The name of the game.
         */
        std::string get_gameName() override;

        /**
         * @brief Checks if the Nibbler game is over.
         *
         * @return True if the game is over, false otherwise.
         */
        bool get_gameOver() override;

        /**
         * @brief Gets the number of food items in the Nibbler game.
         *
         * @return The number of food items.
         */
        int get_nbFood() override;

        // Setter
        /**
         * @brief Sets the score of the Nibbler game.
         *
         * @param scoreValue The value to set as the score.
         */
        void set_score(int scoreValue) override;

        /**
         * @brief Sets the game map entry of the Nibbler game.
         *
         * @param entry The tuple representing a game element to set in the game map.
         */
        void set_gameMap(const std::tuple<char, std::string, int, int>& entry) override;
    
    private:
            std::vector<std::tuple<char, std::string, int, int>> _gameMap; /**< Game map of the Nibbler game. */
            int _score;  /**< Score of the Nibbler game. */
            int _posXHead; /**< X-coordinate of the Nibbler's head. */
            int _posYHead; /**< Y-coordinate of the Nibbler's head. */
            std::vector<std::tuple<int, int, int, int, int>> _nibbler; /**< Representation of the Nibbler in the game. */

            bool _gameOver; /**< Flag indicating if the Nibbler game is over. */

            int _nbFood; /**< Number of food items in the Nibbler game. */
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

/**
 * @brief Enumeration for different types of Nibbler elements.
 */
enum type
{
    head, /**< Nibbler head. */
    body, /**< Nibbler body segment. */
    tail /**< Nibbler tail. */
};

/**
 * @brief Enumeration for different states of Nibbler elements.
 */
enum state
{
    head_up, /**< Head facing up. */
    head_down, /**< Head facing down. */
    head_left, /**< Head facing left. */
    head_right, /**< Head facing right. */
    body_vertical, /**< Vertical body segment. */
    body_horizontal, /**< Horizontal body segment. */
    body_topleft, /**< Top-left corner body segment. */
    body_topright, /**< Top-right corner body segment. */
    body_bottomleft, /**< Bottom-left corner body segment. */
    body_bottomright, /**< Bottom-right corner body segment. */
    tail_up, /**< Tail facing up. */
    tail_down, /**< Tail facing down. */
    tail_left, /**< Tail facing left. */
    tail_right /**< Tail facing right. */
};

#endif // !NIBBLER_HPP
