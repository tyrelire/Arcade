/**
 * @file ICore.cpp
 * @author COUSTABEAU Maxime (maxime.coustabeau@epitech.eu) / MIGLIANI Benjamin (benjamin.migliani@epitech.eu) / LAMAN-DUFLOT Ilhan (Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 *        Main entry point for the Arcade application. Initializes Arcade, and manages user interaction.
 * @version 0.1
 * @date 2024-03-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "ICore.hpp"
#include <dlfcn.h>
#include <iostream>

Core::Core()
{
    set_isRunning(true);
    set_whichMenu(typeMenu::mainMenu);
    set_whichOldMenu(typeMenu::mainMenu);
    set_playerName("playerName");
    _volume = 30;
    _score = 0;
    _enter = true;
    _nextDirection = direction::left;
    _previousDirection = direction::left;
    _autoDirection = direction::none;
    _autoDirectionTmp = direction::none;
    _gameOver = false;
}

Core::~Core()
{
    delete _display;
    delete _game;
}

void Core::run(Loader <IGraphic> *dl, Loader <IGameLib> *dlG)
{
    // Set Display
    setDisplay(dl->currInst("start_lib"));
    _display->set_playerName(_playerName);
    _display->init();
    _display->set_volume(_volume);

    std::string event;
    while (_isRunning == true) {
        if (_whichMenu == typeMenu::inGame) {
            event = _display->game_menu(_game->get_gameMap(), _game->get_gameName());
        }
        if (_whichMenu == typeMenu::endMenu) {
            event = _display->end_menu(_playerName, _game->get_score());
        }
        if (_whichMenu == typeMenu::pauseMenu) {
            event = _display->pause_menu();
        }
        if (_whichMenu == typeMenu::mainMenu) {
            event = _display->main_menu();
        }
        if (_whichMenu == typeMenu::settingsMenu) {
            event = _display->settings_menu();
        }
        update_menu(event, dl, dlG);
        if (!event.empty()) {
            // std::cout << "Event : " << event << std::endl;
        }
        if (_whichMenu == typeMenu::inGame) {
            _gameOver = _game->get_gameOver();
        }
        if (_gameOver == true && _whichMenu == typeMenu::inGame) {
            set_whichMenu(typeMenu::endMenu);
            _display->set_selectedItem(0);
        }
        if (_whichMenu == typeMenu::inGame && _game->get_nbFood() != 3) {
            _game->update_game();
        }
    }
    // std::cout << "Bye bye !" << std::endl;
    _display->close();
}

void Core::update_menu(const std::string event, Loader <IGraphic> *dl, Loader <IGameLib> *dlG)
{
    if (event == "exit") {
        set_isRunning(false);
        return;
    }

    if (event == "setPlayerName") {
        set_playerName(_display->get_playerName());
    }

    if (event == "snake") {
        set_whichMenu(typeMenu::inGame);
        _display->set_selectedItem(0);
        switchGame(dlG, "lib/arcade_snake.so");
        _nextDirection = direction::left;
        _previousDirection = direction::left;
    }
    if (event == "nibbler") {
        set_whichMenu(typeMenu::inGame);
        _display->set_selectedItem(0);
        switchGame(dlG, "lib/arcade_nibbler.so");
    }
    if (event == "pacman") {
        set_whichMenu(typeMenu::inGame);
        _display->set_selectedItem(0);
    }

    if (event == "pause") {
        set_whichMenu(typeMenu::pauseMenu);
        _display->set_selectedItem(0);
    }
    if (event == "resume") {
        set_whichMenu(typeMenu::inGame);
        _display->set_selectedItem(0);
    }
    if (event == "backMain") {
        set_whichMenu(typeMenu::mainMenu);
        _display->set_selectedItem(0);
    }

    if (event == "settingsMain") {
        set_whichMenu(typeMenu::settingsMenu);
        set_whichOldMenu(typeMenu::mainMenu);
        _display->set_selectedItem(0);
    }
    if (event == "settingsPause") {
        set_whichMenu(typeMenu::settingsMenu);
        set_whichOldMenu(typeMenu::pauseMenu);
        _display->set_selectedItem(0);
    }
    if (event == "settingsEnd") {
        set_whichMenu(typeMenu::settingsMenu);
        set_whichOldMenu(typeMenu::endMenu);
        _display->set_selectedItem(0);
    }
    if (event == "backSettings") {
        set_whichMenu(_whichOldMenu);
        _display->set_selectedItem(0);
    }

    if (event == "back") {
        set_whichMenu(typeMenu::inGame);
        _display->set_selectedItem(0);
    }
    if (event == "volume up") {
        set_volume(10);
        _display->set_volume(_volume);
    }
    if (event == "volume down") {
        set_volume(-10);
        _display->set_volume(_volume);
    }

    if (event == "restart") {
        _gameOver = false;
        if (_game->get_gameName() == "Nibbler") {
            set_whichMenu(typeMenu::inGame);
            _display->set_selectedItem(0);
            switchGame(dlG, "lib/arcade_nibbler.so");
            _nextDirection = direction::left;
            _previousDirection = direction::left;
            _autoDirection = direction::none;
            _autoDirectionTmp = direction::none;
        } else if (_game->get_gameName() == "Snake") {
            set_whichMenu(typeMenu::inGame);
            _display->set_selectedItem(0);
            switchGame(dlG, "lib/arcade_snake.so");
            _nextDirection = direction::left;
            _previousDirection = direction::left;
            _autoDirection = direction::none;
            _autoDirectionTmp = direction::none;
        }
    }

    if (event == "end") {
        set_whichMenu(typeMenu::endMenu);
        _display->set_selectedItem(0);
    }

    if (event == "nextLib") {
        if (_display->get_nameLib() == "Ncurses") {
            switchLib(dl, "lib/arcade_sfml.so");
        } else if (_display->get_nameLib() == "Sfml") {
            switchLib(dl, "lib/arcade_sdl2.so");
        } else if (_display->get_nameLib() == "Sdl2") {
            switchLib(dl, "lib/arcade_ncurses.so");
        }
    }

    if (event == "nextGame") {
        if (_game->get_gameName() == "Nibbler") {
            set_whichMenu(typeMenu::inGame);
            _display->set_selectedItem(0);
            switchGame(dlG, "lib/arcade_snake.so");
            _autoDirection = direction::none;
            _autoDirectionTmp = direction::none;
        } else if (_game->get_gameName() == "Snake") {
            set_whichMenu(typeMenu::inGame);
            _display->set_selectedItem(0);
            switchGame(dlG, "lib/arcade_nibbler.so");
            _autoDirection = direction::none;
            _autoDirectionTmp = direction::none;
        }
    }

    if (event == "top") {
        if (_nextDirection != direction::down) {
            _previousDirection = _nextDirection;
            _nextDirection = direction::top;
            _autoDirectionTmp = _game->move(_nextDirection, _previousDirection);
            if (_autoDirectionTmp != direction::none) {
                _autoDirection = _autoDirectionTmp;
            }
        }
    }
    if (event == "down") {
        if (_nextDirection != direction::top) {
            _previousDirection = _nextDirection;
            _nextDirection = direction::down;
            _autoDirectionTmp = _game->move(_nextDirection, _previousDirection);
            if (_autoDirectionTmp != direction::none) {
                _autoDirection = _autoDirectionTmp;
            }
        }
    }
    if (event == "left") {
        if (_nextDirection != direction::right) {
            _previousDirection = _nextDirection;
            _nextDirection = direction::left;
            _autoDirectionTmp = _game->move(_nextDirection, _previousDirection);
            if (_autoDirectionTmp != direction::none) {
                _autoDirection = _autoDirectionTmp;
            }
        }
    }
    if (event == "right") {
        if (_nextDirection != direction::left) {
            _previousDirection = _nextDirection;
            _nextDirection = direction::right;
            _autoDirectionTmp = _game->move(_nextDirection, _previousDirection);
            if (_autoDirectionTmp != direction::none) {
                _autoDirection = _autoDirectionTmp;
            }
        }
    }

    if (event == "auto") {
        if (_autoDirection != direction::none) {
            _previousDirection = _nextDirection;
            _nextDirection = _autoDirection;
            _autoDirectionTmp = _game->move(_nextDirection, _previousDirection);
            if (_autoDirectionTmp != direction::none) {
                _autoDirection = _autoDirectionTmp;
            }
        }
    }
}

void Core::switchLib(Loader <IGraphic> *dl, const char *lib)
{
    //_display->close();
    delete _display;
    dl->swapLib(lib);
    setDisplay(dl->currInst("start_lib"));
    _display->set_playerName(_playerName);
    _display->init();
    _display->set_volume(_volume);
}

void Core::switchGame(Loader <IGameLib> *dl, const char *game)
{
    if (_game != nullptr && _enter == false) {
        // std::cout << "Game : Delete" << std::endl;
        delete _game;
    }
    if (_display->get_nameLib() == "Ncurses") {
        _display->close();
    }
    _enter = false;
    dl->swapLib(game);
    setGame(dl->currInst("start_game"));
    _game->init();
    // std::cout << "Game : " << game << std::endl;
}

/* START Region Setter */

void Core::set_isRunning(bool run)
{
    _isRunning = run;
}

void Core::set_whichMenu(int menu)
{
    _whichMenu = menu;
}

void Core::set_whichOldMenu(int menu)
{
    _whichOldMenu = menu;
}

void Core::set_volume(int value)
{
    if (_volume + value < 0)
        return;
    if (_volume + value > 100)
        return;
    _volume = _volume + value;
}

void Core::set_playerName(std::string name)
{
    _playerName = name;
}

void Core::set_pathMusic(std::string nameMusic)
{
    _pathMusic = nameMusic;
}

void Core::set_score(int value)
{
    _score = _score + value;
}

/* END Region Setter*/

/* START Region Getter */

bool Core::get_isRunning()
{
    return _isRunning;
}

int Core::get_whichMenu()
{
    return _whichMenu;
}

int Core::get_whichOldMenu()
{
    return _whichOldMenu;
}

int Core::get_volume()
{
    return _volume;
}

const std::string Core::get_playerName()
{
    return _playerName;
}

const std::string Core::get_pathMusic()
{
    return _pathMusic;
}

int Core::get_score()
{
    return _score;
}

/* END Region Getter*/