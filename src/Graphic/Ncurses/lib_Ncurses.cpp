/**
 * @file lib_Ncurses.cpp
 * @author COUSTABEAU Maxime / MIGLIANI Benjamin / LAMAN-DUFLOT Ilhan (maxime.coustabeau@epitech.eu / benjamin.migliani@epitech.eu / Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "lib_Ncurses.hpp"


#define WIDTH 30
#define HEIGHT 10

/* START Region Loader */

LIB_NCURSES::LIB_NCURSES()
{
    //init();
}

LIB_NCURSES::~LIB_NCURSES()
{
    close();
}

extern "C" IGraphic *start_lib()
{
    //printf("[arcade_ncurses] Entry point !\n");
    return new LIB_NCURSES();
}

/* # END Region Loader */

/* # START Region Init */

void LIB_NCURSES::init()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    set_selectedItem(0);

    set_nameLib("Ncurses");
}

/* END Region Init */

/* START Region Menu */

const std::string LIB_NCURSES::main_menu()
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    const char *choices[] = {
        "Snake",
        "Nibbler",
        "PacMan",
        "Settings",
        "Exit",
    };

    int c;

    while(1) {
        clear();

        int ascii_starty = 10;
        int ascii_startx = (cols - 68) / 2;

        mvprintw(ascii_starty, ascii_startx, "······································································");
        mvprintw(ascii_starty + 1, ascii_startx, ":                                                                    :");
        mvprintw(ascii_starty + 2, ascii_startx, ":                                                                    :");
        mvprintw(ascii_starty + 3, ascii_startx, ":   ________  ________  ________  ________  ________  _______        :");
        mvprintw(ascii_starty + 4, ascii_startx, ":  |\\   __  \\|\\   __  \\|\\   ____\\|\\   __  \\|\\   ___ \\|\\  ___ \\       :");
        mvprintw(ascii_starty + 5, ascii_startx, ":  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\_|\\ \\ \\   __/|      :");
        mvprintw(ascii_starty + 6, ascii_startx, ":   \\ \\   __  \\ \\   _  _\\ \\  \\    \\ \\   __  \\ \\  \\ \\\\ \\ \\  \\_|/__    :");
        mvprintw(ascii_starty + 7, ascii_startx, ":    \\ \\  \\ \\  \\ \\  \\\\  \\\\ \\  \\____\\ \\  \\ \\  \\ \\  \\_\\\\ \\ \\  \\_|\\ \\   :");
        mvprintw(ascii_starty + 8, ascii_startx, ":     \\ \\__\\ \\__\\ \\__\\\\ _\\\\ \\_______\\ \\__\\ \\__\\ \\_______\\ \\_______\\  :");
        mvprintw(ascii_starty + 9, ascii_startx, ":      \\|__|\\|__|\\|__|\\|__|\\|_______|\\|__|\\|__|\\|_______|\\|_______|  :");
        mvprintw(ascii_starty + 10, ascii_startx, ":                                                                    :");
        mvprintw(ascii_starty + 11, ascii_startx, ":                                                                    :");
        mvprintw(ascii_starty + 12, ascii_startx, "······································································");

        refresh();

        for(int i = 0; i <= 5; ++i) {
            mvprintw(rows/2 + i, cols/2 - 11, "|");
            mvprintw(rows/2 + i, cols/2 + 10, "|");
        }
        mvprintw(rows/2 - 1, cols/2 - 11, "+--------------------+");
        mvprintw(rows/2 + 6, cols/2 - 11, "+--------------------+");

        for(int i = 0; i < 6; ++i) {
            if (i == _selectedItem) {
                attron(A_REVERSE);
            }
            if (i == 0) {
                mvprintw(rows/2 + i - 1, cols/2 - _playerName.length()/2, "%s", _playerName.c_str());
            } else {
                mvprintw(rows/2 + i, cols/2 - strlen(choices[i-1])/2, "%s", choices[i-1]);
            }
            attroff(A_REVERSE);
        }

        refresh();

        c = getch();
        switch(c) {
            case KEY_UP:
                if (_selectedItem > 0) {
                    --_selectedItem;
                }
                break;
            case KEY_DOWN:
                if (_selectedItem < 5) {
                    ++_selectedItem;
                }
                break;
            case 'g':
                return "nextLib";
            case '\n':
                if (_selectedItem == 0) {
                    echo();
                    int ch;
                    _playerName.clear();
                    move(rows/2 - 1, cols/2 - 10);
                    clrtoeol();
                    mvprintw(rows/2 - 1, cols/2 - 11, "+--------------------+");
                    while ((ch = getch()) != '\n') {
                        if (ch == KEY_BACKSPACE) {
                            if (!_playerName.empty()) {
                                _playerName.pop_back();
                            }
                        } else if (_playerName.length() < 10) {
                            _playerName += ch;
                        }
                        move(rows/2 - 1, cols/2 - 10);
                        clrtoeol();
                        mvprintw(rows/2 - 1, cols/2 - 11, "+--------------------+");
                        mvprintw(rows/2 - 1, cols/2 - _playerName.length()/2, "%s", _playerName.c_str());
                        refresh();
                    }
                    noecho();
                    if (_playerName.empty()) {
                        _playerName = "PlayerName";
                    }
                    return "setPlayerName";
                } else if (_selectedItem == 5) {
                    endwin();
                    return "exit";
                } else if (_selectedItem == 1) {
                    endwin();
                    game_paused = false;
                    return "snake";
                } else if (_selectedItem == 2) {
                    endwin();
                    game_paused = false;
                    return "nibbler";
                } if (_selectedItem == 4) {
                    endwin();
                    return "settingsMain";
                }
                break;
        }
    }
    return "";
}


const std::string LIB_NCURSES::pause_menu()
{
    int ch;
    const char *choices[] = {"Resume", "Settings", "Back to Main Menu"};

    WINDOW *pause_win = newwin(10, 30, (LINES - 10) / 2, (COLS - 30) / 2);

    box(pause_win, 0, 0);

    keypad(pause_win, TRUE);

    while (1) {
        for(int i = 0; i < 3; ++i) {
            if (i == _selectedItem) {
                wattron(pause_win, A_REVERSE);
            }
            int len = strlen(choices[i]);
            int x = (30 - len) / 2;
            mvwprintw(pause_win, i + 2, x, "%s", choices[i]);
            wattroff(pause_win, A_REVERSE);
        }

        wrefresh(pause_win);

        ch = wgetch(pause_win);

        switch(ch) {
            case KEY_UP:
                _selectedItem = (_selectedItem - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                _selectedItem = (_selectedItem + 1) % 3;
                break;
            case 'g':
                return "nextLib";
            case '\n':
                if (_selectedItem == 0) {
                    game_paused = false;
                    delwin(pause_win);
                    return "resume";
                }
                if (_selectedItem == 1) {
                    return "settingsPause";
                }
                if (_selectedItem == 2) {
                    delwin(pause_win);
                    endwin();
                    return "backMain";
                }
                break;
        }
    }
}

const std::string LIB_NCURSES::end_menu(std::string playerName, int score)
{
    int ch;
    const char *choices[] = {"Restart", "Back to Main Menu", "Settings"};

    WINDOW *end_win = newwin(10, 30, (LINES - 10) / 2, (COLS - 30) / 2);

    box(end_win, 0, 0);

    char player_text[50];
    sprintf(player_text, "%s", playerName.c_str());
    int len = strlen(player_text);
    int x = (30 - len) / 2;
    mvwprintw(end_win, 1, x, "%s", player_text);

    char score_text[50];
    sprintf(score_text, "Score %d", score);
    len = strlen(score_text);
    x = (30 - len) / 2;
    mvwprintw(end_win, 2, x, "%s", score_text);

    keypad(end_win, TRUE);

    while (1) {
        for(int i = 0; i < 3; ++i) {
            if (i == _selectedItem) {
                wattron(end_win, A_REVERSE);
            }
            len = strlen(choices[i]);
            x = (30 - len) / 2;
            mvwprintw(end_win, i + 3, x, "%s", choices[i]);
            wattroff(end_win, A_REVERSE);
        }

        wrefresh(end_win);

        ch = wgetch(end_win);

        switch(ch) {
            case KEY_UP:
                _selectedItem = (_selectedItem - 1 + 2) % 3;
                break;
            case KEY_DOWN:
                _selectedItem = (_selectedItem + 1) % 3;
                break;
            case 'g':
                return "nextLib";
            case '\n':
                if (_selectedItem == 0) {
                    delwin(end_win);
                    endwin();
                    game_paused = false;
                    return "restart";
                }
                if (_selectedItem == 1) {
                    delwin(end_win);
                    endwin();
                    return "backMain";
                }
                if (_selectedItem == 2) {
                    delwin(end_win);
                    endwin();
                    return "settingsEnd";
                }
                break;
        }
    }
}

const std::string LIB_NCURSES::settings_menu()
{
    int ch;
    const char *choices[] = {"Back", "Volume up", "Volume Down"};
    int volume = 50;
    initscr();

    WINDOW *settings_win = newwin(10, 30, (LINES - 10) / 2, (COLS - 30) / 2);

    box(settings_win, 0, 0);

    keypad(settings_win, TRUE);

    while (1) {
        for(int i = 0; i < 3; ++i) {
            if (i == _selectedItem) {
                wattron(settings_win, A_REVERSE);
            }
            int len = strlen(choices[i]);
            int x = (30 - len) / 2;
            mvwprintw(settings_win, i + 2, x, "%s", choices[i]);
            wattroff(settings_win, A_REVERSE);
        }

        wrefresh(settings_win);

        ch = wgetch(settings_win);

        switch(ch) {
            case KEY_UP:
                _selectedItem = (_selectedItem - 1 + 4) % 4;
                break;
            case KEY_DOWN:
                _selectedItem = (_selectedItem + 1) % 4;
                break;
            case 'g':
                return "nextLib";
            case '\n':
                if (_selectedItem == 0) {
                    return "backSettings";
                }
                if (_selectedItem == 1) {
                    return "volume up";
                }
                if (_selectedItem == 2) {
                    return "volume down";
                }
                break;
        }
    }
}

const std::string LIB_NCURSES::game_menu(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame)
{
    int ch;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    game_win = newwin(rows - 4, cols - 4, 2, 2);
    box(game_win, 0, 0);

    draw_map(_gameMap, nameGame);

    wrefresh(game_win);

    while (1) {
        if (game_paused) {
            game_paused = false;
            return "pause";
        }

        ch = wgetch(game_win);
        if (ch == 27) {
            nodelay(stdscr, TRUE);
            ch = wgetch(stdscr);
            nodelay(stdscr, FALSE);
            if (ch == ERR) {
                game_paused = true;;
            }
        } if (ch == 'g') {
            return "nextLib";
        } if (ch == 'j') {
            return "nextGame";
        } if (ch == 'r') {
            return "restart";
        } if (ch == 'm') {
            return "backMain";
        } if (ch == 'z') {
            return "top";
        } if (ch == 's') {
            return "down";
        } if (ch == 'q') {
            return "left";
        } if (ch == 'd') {
            return "right";
        }
    }

    // Action declencher au bout de 1 secondes si aucun event
    // return "auto";

    delwin(game_win);
}

/* END Region Menu */

/* START Region Draw */

void LIB_NCURSES::draw_game()
{
    
}

void LIB_NCURSES::draw_map(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame)
{
    werase(game_win);

    int max_x, max_y;
    getmaxyx(game_win, max_y, max_x);

    int map_width = sqrt(_gameMap.size());
    int map_height = sqrt(_gameMap.size());

    int start_x = (max_x - map_width) / 2;
    int start_y = (max_y - map_height) / 2;

    for (const auto& entry : _gameMap) {
        char c = std::get<0>(entry);
        int x = std::get<2>(entry);
        int y = std::get<3>(entry);

        if (c == 'W') {
            mvwaddch(game_win, start_y + y, start_x + x, 'W');
        } else if (c == 'M') {
            mvwaddch(game_win, start_y + y, start_x + x, 'M');
        } else if (c == 'E') {
            mvwaddch(game_win, start_y + y, start_x + x, 'E');
        } else if (c == '3') {
            mvwaddch(game_win, start_y + y, start_x + x, '3');
        } else if (c == '|') {
            mvwaddch(game_win, start_y + y, start_x + x, '|');
        } else if (c == '-') {
            mvwaddch(game_win, start_y + y, start_x + x, '-');
        } else if (c == '^') {
            mvwaddch(game_win, start_y + y, start_x + x, '^');
        } else if (c == 'v') {
            mvwaddch(game_win, start_y + y, start_x + x, 'v');
        } else if (c == '<') {
            mvwaddch(game_win, start_y + y, start_x + x, '<');
        } else if (c == '>') {
            mvwaddch(game_win, start_y + y, start_x + x, '>');
        } else if (c == '1') {
            mvwaddch(game_win, start_y + y, start_x + x, '1');
        } else if (c == '9') {
            mvwaddch(game_win, start_y + y, start_x + x, '9');
        } else if (c == '6') {
            mvwaddch(game_win, start_y + y, start_x + x, '6');
        } else if (c == 'T') {
            mvwaddch(game_win, start_y + y, start_x + x, 'T');
        } else if (c != ' ') {
            mvwaddch(game_win, start_y + y, start_x + x, '#');
        }
    }

    box(game_win, 0, 0);
    wrefresh(game_win);
}

void LIB_NCURSES::draw_score()
{

}

void LIB_NCURSES::draw_playerName()
{

}

void LIB_NCURSES::draw_allSprite()
{

}

/* END Region Draw */

/* START Region Event */

void LIB_NCURSES::close()
{
    endwin();
}

void LIB_NCURSES::pause()
{

}

void LIB_NCURSES::stop()
{
    endwin();
}

void LIB_NCURSES::clear()
{
    ::clear();
}

/* # END Region Event */

/* START Region Update*/

void LIB_NCURSES::update()
{
    refresh();
}

/* END Region Update */

/* # START Region Sound */

void LIB_NCURSES::sound(std::string pathMusic, int volume)
{

}

void LIB_NCURSES::set_volume(int value)
{
    
}

/* # END Region Sound */

/* # START Region Setter */

void LIB_NCURSES::set_playerName(std::string name)
{
    _playerName = name;
}

void LIB_NCURSES::set_selectedItem(int index)
{
    _selectedItem = index;
}

void LIB_NCURSES::set_nameLib(std::string lib)
{
    _nameLib = lib;
}

/* # END Region Setter */

/* # START Region Getter */

const std::string LIB_NCURSES::get_playerName()
{
    return _playerName;
}

int LIB_NCURSES::get_selectedItem()
{
    return _selectedItem;
}

const std::string LIB_NCURSES::get_nameLib()
{
    return _nameLib;
}

/* # END Region Getter */

