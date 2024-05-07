# Epitech Project, second Year -> Arcade

## About Arcade :

Arcade is a project developed in C++ that includes shared libraries 
from different libraries. The aim is to play games on different graphics libraries.

## TEAM MEMBERS:

- Maxime Coustabeay : <sub> maxime.coustabeau@epitech.eu </sub>
* Benjamin Migliani : <sub> benjamin.migliani@epitech.eu </sub>
+ Ilhan Laman-Duflot : <sub> ilhan.laman-duflot@epitech.eu </sub>

## USAGE

 Make sure you've installed the graphics libs `sdl2` `sfml` and `ncurses`  

- Compile : `make`
- Launch : `./arcade ./lib/arcade_[graphic_lib].so`
- Clean : `make fclean` 

## Command :

### Menu Navigation :

 - Swap Librairy -> `g`
 - Restart Game -> `r`
 - Back Menu -> `m`
 - Swap Game -> `j`
 - Pause Menu -> `echap`
   
###  Game Commands :
-  Up -> `z`
-  Left -> `q`
-  Down -> `s`
-  Right -> `d`
 
 ## ADD a GAME :

  To add a game, create an `file.hpp` and `file.cpp` file
  your file will be a class that inherits from IGamelib.hpp
  all `IGamelib.hpp` functions must be added as overrides
  you will need to implement the following functions

    `void init();`
    
  Initializes the game.

    `void stop()`
    
  Stops the Snake game.

    `void update_game()`
    
  Updates the Snake game state.

    `void update_map();`
    
  Updates the Snake game map.

    `int move(int nextDirection, int prevDirection);`
    
  Moves the Snake player.
     `nextDirection` The next direction the player intends to move.
     `revDirection` The previous direction the player was moving in.
     `return` The result of the move operation.

    `int get_score();`
    
   Gets the current score of the Snake game.
     `return` The current score.

    `std::vector<std::tuple<char, std::string, int, int>> get_gameMap();``
    
   Gets the game map of the Snake game.
     `return` Vector of tuples representing game elements.

    `std::string get_gameName();`
    
   Gets the name of the Snake game.
      `return` The name of the game.

    `bool get_gameOver():`
    
   Checks if the Snake game is over.
     `return` True if the game is over, false otherwise.

     `int get_nbFood();`
     
   Gets the number of food items in the Snake game.
     `return` The number of food items.

     `void set_score(int scoreValue);`
     
   Sets the score of the Snake game.
    scoreValue The value to set as the score.

     `void set_gameMap(const std::tuple<char, std::string, int, int>& entry);`
   Sets the game map entry of the Snake game.
    entry The tuple representing a game element to set in the game map.

## ADD Library :

   Adding a library is the same as adding a game create an hpp and a cpp
   that will inherit from the IGraphicLib.hpp class all
   your following functions must be implemented in the cpp and overridden in the hpp

    `void init() override;`
  Initializes the SDL2 graphics.

        `const std::string main_menu();`
  Generates the main menu.

        `const std::string end_menu(std::string playerName, int score);`
  Generates the end game menu.

        `const std::string pause_menu();`
  Generates the pause menu.

        `const std::string settings_menu();`
  Generates the settings menu.

        `const std::string game_menu(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame);`
  Generates the game menu.

        `void draw_game();`
  Draws the game.

        void draw_score();
  Draws the score.

        void draw_playerName();
  Draws the player's name.

        void draw_allSprite();
  Draws all sprites.

        `void draw_map(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame);`
  Draws the game map.

        `void stop();`
  Stops the graphics.

        `void pause();`
  Pauses the graphics.

        `void clear();`
  Clears the graphics.

        `void close();`
  Closes the graphics.

        `void update();`
  Updates the graphics.

        `void sound(std::string pathMusic, int volume);`
   Plays a sound.

        `void set_volume(int value);`
   Sets the volume level.

        `void set_playerName(std::string name);`
   Sets the player's name.

        `void set_selectedItem(int index);`
   Sets the selected item index.

        `void set_nameLib(std::string lib);`
   Sets the name of the graphics library.

        `const std::string get_playerName();`
   Gets the player's name.

        `int get_selectedItem();`
   Gets the index of the selected item.

        `const std::string get_nameLib();`
   Gets the name of the graphics library.
