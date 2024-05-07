/**
 * @file Nibbler.cpp
 * @author COUSTABEAU Maxime / MIGLIANI Benjamin / LAMAN-DUFLOT Ilhan (maxime.coustabeau@epitech.eu / benjamin.migliani@epitech.eu / Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Nibbler.hpp"

/* START Region Loader */

Nibbler::Nibbler()
{

}

Nibbler::~Nibbler()
{

}

extern "C" IGameLib *start_game()
{
    printf("[arcade_nibbler] Entry point for Nibbler game!\n");
    return new Nibbler();
}

/* END Region Loader */

/* START Region Init */

void Nibbler::init()
{
    // std::cout << "start init" << std::endl;

    _gameOver = false;
    _score = 0;
    int index = 0;

    _nbFood = 0;

    std::ifstream file("src/asset/game/nibbler/map.txt");
    if (!file) {
        std::cerr << "Unable to open file map.txt";
        exit(84);
    }

    if (file.is_open()) {
        std::string line;
        std::vector<std::string> map;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '\n') continue;
            map.push_back(line);
        }
        file.close();

        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                char c = map[i][j];
                std::string imageFile;
                if (c == '#') {
                    imageFile = "src/asset/game/nibbler/wall2.png";
                } else if (c == ' ') {
                    imageFile = "src/asset/game/nibbler/floor.png";
                } else if (c == 'o') {
                    imageFile = "src/asset/game/nibbler/floor.png";
                } else if (c == 'L') {
                    imageFile = "src/asset/game/nibbler/corner1.png";
                } else if (c == 'R') {
                    imageFile = "src/asset/game/nibbler/corner2.png";
                } else if (c == 'D') {
                    imageFile = "src/asset/game/nibbler/corner3.png";
                } else if (c == 'G') {
                    imageFile = "src/asset/game/nibbler/corner4.png";
                } else if (c == 'H') {
                    imageFile = "src/asset/game/nibbler/wall1.png";
                } else if (c == 'W') {
                    imageFile = "src/asset/game/nibbler/head_down.png";
                    _posYHead = j; _posXHead = i;
                } else if (c == 'M') {
                    imageFile = "src/asset/game/nibbler/head_up.png";
                    _posYHead = j; _posXHead = i;
                } else if (c == 'E') {
                    imageFile = "src/asset/game/nibbler/head_right.png";
                    _posYHead = j; _posXHead = i;
                } else if (c == '3') {
                    imageFile = "src/asset/game/nibbler/head_left.png";
                    _nibbler.push_back(std::make_tuple(j, i, state::head_left, direction::left, type::head));
                    _posYHead = j; _posXHead = i;
                } else if (c == '|') {
                    imageFile = "src/asset/game/nibbler/body_vertical.png";
                } else if (c == '-') {
                    imageFile = "src/asset/game/nibbler/body_horizontal.png";
                    _nibbler.push_back(std::make_tuple(j, i, state::body_horizontal, direction::left, type::body));
                } else if (c == '^') {
                    imageFile = "src/asset/game/nibbler/tail_up.png";
                } else if (c == 'v') {
                    imageFile = "src/asset/game/nibbler/tail_down.png";
                } else if (c == '<') {
                    imageFile = "src/asset/game/nibbler/tail_left.png";
                } else if (c == '>') {
                    imageFile = "src/asset/game/nibbler/tail_right.png";
                    _nibbler.push_back(std::make_tuple(j, i, state::tail_right, direction::left, type::tail));
                } else if (c == '1') {
                    imageFile = "src/asset/game/nibbler/body_bottomleft.png";
                } else if (c == 'T') {
                    imageFile = "src/asset/game/nibbler/body_bottomright.png";
                } else if (c == '6') {
                    imageFile = "src/asset/game/nibbler/body_topright.png";
                } else if (c == '9') {
                    imageFile = "src/asset/game/nibbler/body_topleft.png";
                } else {
                    continue;
                }
                _gameMap.push_back(std::make_tuple(c, imageFile, j, i));
            }
        }
    }

    // place food
    while (_nbFood < 3) {
        int x = rand() % _gameMap.size();
        int y = rand() % _gameMap.size();
        for (int i = 0; i < _gameMap.size(); ++i) {
            if (std::get<2>(_gameMap[i]) == y && std::get<3>(_gameMap[i]) == x && std::get<0>(_gameMap[i]) == ' ') {
                _gameMap[i] = std::make_tuple('f', "src/asset/game/snake/apple.png", y, x);
                _nbFood++;
                break;
            }
        }
    }
}

void Nibbler::stop()
{

}

void Nibbler::update_game()
{
    while (_nbFood < 3) {
        int x = rand() % _gameMap.size();
        int y = rand() % _gameMap.size();
        for (int i = 0; i < _gameMap.size(); ++i) {
            if (std::get<2>(_gameMap[i]) == y && std::get<3>(_gameMap[i]) == x && std::get<0>(_gameMap[i]) == ' ') {
                _gameMap[i] = std::make_tuple('f', "src/asset/game/snake/apple.png", y, x);
                _nbFood++;
                _score+=10;
                break;
            }
        }
    }
}

void Nibbler::update_map()
{
    
}

int Nibbler::move(int nextDirection, int prevDirection)
{
    int prevY = 0;
    int prevX = 0;
    int prevTmpY = 0;
    int prevTmpX = 0;
    int prevDirec = 0;
    int prevType = 0;
    int prevTmpDirec = 0;
    int prevTmpType = 0;
    for (int i = 0; i < _nibbler.size(); ++i) {
        if (std::get<4>(_nibbler[i]) == type::head) {
            if (nextDirection == direction::top && prevDirection != direction::down) {
                prevY = std::get<0>(_nibbler[i]);
                prevX = std::get<1>(_nibbler[i]);
                prevDirec = std::get<3>(_nibbler[i]);
                prevType = std::get<4>(_nibbler[i]);
                for (int j = 0; j < _gameMap.size(); ++j) {
                    if (prevY - 0 == std::get<2>(_gameMap[j]) && prevX - 1 == std::get<3>(_gameMap[j])) {
                        if (std::get<0>(_gameMap[j]) == ' ') {
                            // std::cout << "Can move" << std::endl;
                        } else if (std::get<0>(_gameMap[j]) == '#' || std::get<0>(_gameMap[j]) == 'H' || std::get<0>(_gameMap[j]) == 'L' || std::get<0>(_gameMap[j]) == 'R' || std::get<0>(_gameMap[j]) == 'D' || std::get<0>(_gameMap[j]) == 'G' || std::get<0>(_gameMap[j]) == 'o') {
                            // std::cout << "Can't move" << std::endl;
                            return direction::none;
                        }  else if (std::get<0>(_gameMap[j]) == 'f') {
                            std::get<4>(_nibbler[_nibbler.size() - 1]) = type::body;
                            _nibbler.push_back(std::make_tuple(prevY, prevX, state::tail_left, std::get<3>(_nibbler[_nibbler.size() - 2]), type::tail));
                            // std::cout << "eat" << std::endl;
                            std::get<0>(_gameMap[j]) = ' ';
                            std::get<1>(_gameMap[j]) = "src/asset/game/nibbler/floor.png";
                            _nbFood--;
                        } else {
                            // std::cout << "Game Over" << std::endl;
                            _gameOver = true; return none;
                        }
                        break;
                    }
                }
                std::get<0>(_nibbler[i]) -= 0;
                std::get<1>(_nibbler[i]) -= 1;
                std::get<2>(_nibbler[i]) = state::head_up;
                std::get<3>(_nibbler[i]) = direction::top;
                std::get<4>(_nibbler[i]) = type::head;
            } else if (nextDirection == direction::down && prevDirection != direction::top) {
                prevY = std::get<0>(_nibbler[i]);
                prevX = std::get<1>(_nibbler[i]);
                prevDirec = std::get<3>(_nibbler[i]);
                prevType = std::get<4>(_nibbler[i]);
                for (int j = 0; j < _gameMap.size(); ++j) {
                    if (prevY + 0 == std::get<2>(_gameMap[j]) && prevX + 1 == std::get<3>(_gameMap[j])) {
                        if (std::get<0>(_gameMap[j]) == ' ') {
                            // std::cout << "Can move" << std::endl;
                        } else if (std::get<0>(_gameMap[j]) == '#' || std::get<0>(_gameMap[j]) == 'H' || std::get<0>(_gameMap[j]) == 'L' || std::get<0>(_gameMap[j]) == 'R' || std::get<0>(_gameMap[j]) == 'D' || std::get<0>(_gameMap[j]) == 'G' || std::get<0>(_gameMap[j]) == 'o') {
                            // std::cout << "Can't move" << std::endl;
                            return direction::none;
                        }  else if (std::get<0>(_gameMap[j]) == 'f') {
                            std::get<4>(_nibbler[_nibbler.size() - 1]) = type::body;
                            _nibbler.push_back(std::make_tuple(prevY, prevX, state::tail_left, std::get<3>(_nibbler[_nibbler.size() - 2]), type::tail));
                            // std::cout << "eat" << std::endl;
                            std::get<0>(_gameMap[j]) = ' ';
                            std::get<1>(_gameMap[j]) = "src/asset/game/nibbler/floor.png";
                            _nbFood--;
                        } else {
                            // std::cout << "Game Over" << std::endl;
                            _gameOver = true; return none;
                        }
                        break;
                    }
                }
                std::get<0>(_nibbler[i]) += 0;
                std::get<1>(_nibbler[i]) += 1;
                std::get<2>(_nibbler[i]) = state::head_down;
                std::get<3>(_nibbler[i]) = direction::down;
                std::get<4>(_nibbler[i]) = type::head;
            } else if (nextDirection == direction::left && prevDirection != direction::right) {
                prevY = std::get<0>(_nibbler[i]);
                prevX = std::get<1>(_nibbler[i]);
                prevDirec = std::get<3>(_nibbler[i]);
                prevType = std::get<4>(_nibbler[i]);
                for (int j = 0; j < _gameMap.size(); ++j) {
                    if (prevY - 1 == std::get<2>(_gameMap[j]) && prevX - 0 == std::get<3>(_gameMap[j])) {
                        if (std::get<0>(_gameMap[j]) == ' ') {
                            // std::cout << "Can move" << std::endl;
                        } else if (std::get<0>(_gameMap[j]) == '#' || std::get<0>(_gameMap[j]) == 'H' || std::get<0>(_gameMap[j]) == 'L' || std::get<0>(_gameMap[j]) == 'R' || std::get<0>(_gameMap[j]) == 'D' || std::get<0>(_gameMap[j]) == 'G' || std::get<0>(_gameMap[j]) == 'o') {
                            // std::cout << "Can't move" << std::endl;
                            return direction::none;
                        } else if (std::get<0>(_gameMap[j]) == 'f') {
                            std::get<4>(_nibbler[_nibbler.size() - 1]) = type::body;
                            _nibbler.push_back(std::make_tuple(prevY, prevX, state::tail_left, std::get<3>(_nibbler[_nibbler.size() - 2]), type::tail));
                            // std::cout << "eat" << std::endl;
                            std::get<0>(_gameMap[j]) = ' ';
                            std::get<1>(_gameMap[j]) = "src/asset/game/nibbler/floor.png";
                            _nbFood--;
                        } else {
                            // std::cout << "Game Over" << std::endl;
                            _gameOver = true; return none;
                        }
                        break;
                    }
                }
                std::get<0>(_nibbler[i]) -= 1;
                std::get<1>(_nibbler[i]) -= 0;
                std::get<2>(_nibbler[i]) = state::head_left;
                std::get<3>(_nibbler[i]) = direction::left;
                std::get<4>(_nibbler[i]) = type::head;
            } else if (nextDirection == direction::right && prevDirection != direction::left) {
                prevY = std::get<0>(_nibbler[i]);
                prevX = std::get<1>(_nibbler[i]);
                prevDirec = std::get<3>(_nibbler[i]);
                prevType = std::get<4>(_nibbler[i]);
                for (int j = 0; j < _gameMap.size(); ++j) {
                    if (prevY + 1 == std::get<2>(_gameMap[j]) && prevX + 0 == std::get<3>(_gameMap[j])) {
                        if (std::get<0>(_gameMap[j]) == ' ') {
                            // std::cout << "Can move" << std::endl;
                        } else if (std::get<0>(_gameMap[j]) == '#' || std::get<0>(_gameMap[j]) == 'H' || std::get<0>(_gameMap[j]) == 'L' || std::get<0>(_gameMap[j]) == 'R' || std::get<0>(_gameMap[j]) == 'D' || std::get<0>(_gameMap[j]) == 'G' || std::get<0>(_gameMap[j]) == 'o') {
                            // std::cout << "Can't move" << std::endl;
                            return direction::none;
                        }  else if (std::get<0>(_gameMap[j]) == 'f') {
                            std::get<4>(_nibbler[_nibbler.size() - 1]) = type::body;
                            _nibbler.push_back(std::make_tuple(prevY, prevX, state::tail_left, std::get<3>(_nibbler[_nibbler.size() - 2]), type::tail));
                            // std::cout << "eat" << std::endl;
                            std::get<0>(_gameMap[j]) = ' ';
                            std::get<1>(_gameMap[j]) = "src/asset/game/nibbler/floor.png";
                            _nbFood--;
                        } else {
                            // std::cout << "Game Over" << std::endl;
                            _gameOver = true; return none;
                        }
                        break;
                    }
                }
                std::get<0>(_nibbler[i]) += 1;
                std::get<1>(_nibbler[i]) += 0;
                std::get<2>(_nibbler[i]) = state::head_right;
                std::get<3>(_nibbler[i]) = direction::right;
                std::get<4>(_nibbler[i]) = type::head;
            }
        } else if (std::get<4>(_nibbler[i]) == type::body) {
            prevTmpY = prevY;
            prevTmpX = prevX;
            prevTmpDirec = prevDirec;
            prevTmpType = prevType;
            prevY = std::get<0>(_nibbler[i]);
            prevX = std::get<1>(_nibbler[i]);
            prevDirec = std::get<3>(_nibbler[i]);
            prevType = std::get<4>(_nibbler[i]);
            if (std::get<3>(_nibbler[i - 1]) == top && prevTmpDirec == direction::left) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_topright;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == down && prevTmpDirec == direction::left) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_bottomright;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == direction::down && prevTmpDirec == direction::right) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_bottomleft;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == direction::top && prevTmpDirec == direction::right) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_topleft;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == direction::left && prevTmpDirec == direction::down) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_topleft;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == direction::right && prevTmpDirec == direction::down) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_topright;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == direction::right && prevTmpDirec == direction::top) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_bottomright;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == direction::left && prevTmpDirec == direction::top) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_bottomleft;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (prevTmpDirec == direction::top) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_vertical;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (prevTmpDirec == direction::down) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_vertical;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (prevTmpDirec == direction::left) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_horizontal;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (prevTmpDirec == direction::right) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::body_horizontal;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            }
        } else if (std::get<4>(_nibbler[i]) == type::tail) {
            prevTmpY = prevY;
            prevTmpX = prevX;
            prevTmpDirec = prevDirec;
            prevTmpType = prevType;
            prevY = std::get<0>(_nibbler[i]);
            prevX = std::get<1>(_nibbler[i]);
            prevDirec = std::get<3>(_nibbler[i]);
            prevType = std::get<4>(_nibbler[i]);
            if (std::get<3>(_nibbler[i - 1]) == direction::top) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::tail_up;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == direction::down) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::tail_down;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == direction::left) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::tail_right;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            } else if (std::get<3>(_nibbler[i - 1]) == direction::right) {
                std::get<0>(_nibbler[i]) = prevTmpY;
                std::get<1>(_nibbler[i]) = prevTmpX;
                std::get<2>(_nibbler[i]) = state::tail_left;
                std::get<3>(_nibbler[i]) = prevTmpDirec;
            }
        }
    }

    // std::cout << std::endl;
    for (int i = 0; i < _nibbler.size(); ++i) {
        // std::cout << std::get<0>(_nibbler[i]) << " " << std::get<1>(_nibbler[i]) << " " << std::get<2>(_nibbler[i]) << std::endl;
    }

    for (int i = 0; i < _gameMap.size(); ++i) {
        // clear head
        _posYHead = std::get<2>(_gameMap[i]);
        _posXHead = std::get<3>(_gameMap[i]);
        if (std::get<0>(_gameMap[i]) == 'W' || std::get<0>(_gameMap[i]) == 'M' || std::get<0>(_gameMap[i]) == 'E' || std::get<0>(_gameMap[i]) == '3') {
            _gameMap[i] = std::make_tuple(' ', "src/asset/game/nibbler/floor.png", _posYHead, _posXHead);
        }
        // clear tail
        if (std::get<0>(_gameMap[i]) == '<' || std::get<0>(_gameMap[i]) == '>' || std::get<0>(_gameMap[i]) == 'v' || std::get<0>(_gameMap[i]) == '^') {
            _gameMap[i] = std::make_tuple(' ', "src/asset/game/nibbler/floor.png", _posYHead, _posXHead);
        }
        // clear body
        if (std::get<0>(_gameMap[i]) == '1' || std::get<0>(_gameMap[i]) == 'T' || std::get<0>(_gameMap[i]) == '6' || std::get<0>(_gameMap[i]) == '9' || std::get<0>(_gameMap[i]) == '|' || std::get<0>(_gameMap[i]) == '-') {
            _gameMap[i] = std::make_tuple(' ', "src/asset/game/nibbler/floor.png", _posYHead, _posXHead);
        }
    }

    int tmpY;
    int tmpX;
    int tmpState;
    char tmpChar;
    std::string tmpStr;
    for (int i = 0; i < _nibbler.size(); ++i) {
        tmpY = std::get<0>(_nibbler[i]);
        tmpX = std::get<1>(_nibbler[i]);
        tmpState = std::get<2>(_nibbler[i]);
        if (tmpState == state::head_up) {
            tmpChar = 'W';
            tmpStr = "src/asset/game/nibbler/head_up.png";
        } else if (tmpState == state::head_down) {
            tmpChar = 'M';
            tmpStr = "src/asset/game/nibbler/head_down.png";
        } else if (tmpState == state::head_left) {
            tmpChar = '3';
            tmpStr = "src/asset/game/nibbler/head_left.png";
        } else if (tmpState == state::head_right) {
            tmpChar = 'E';
            tmpStr = "src/asset/game/nibbler/head_right.png";
        } else if (tmpState == state::tail_up) {
            tmpChar = 'v';
            tmpStr = "src/asset/game/nibbler/tail_down.png";
        } else if (tmpState == state::tail_down) {
            tmpChar = '^';
            tmpStr = "src/asset/game/nibbler/tail_up.png";
        } else if (tmpState == state::tail_left) {
            tmpChar = '<';
            tmpStr = "src/asset/game/nibbler/tail_left.png";
        } else if (tmpState == state::tail_right) {
            tmpChar = '>';
            tmpStr = "src/asset/game/nibbler/tail_right.png";
        } else if (tmpState == state::body_vertical) {
            tmpChar = '|';
            tmpStr = "src/asset/game/nibbler/body_vertical.png";
        } else if (tmpState == state::body_horizontal) {
            tmpChar = '-';
            tmpStr = "src/asset/game/nibbler/body_horizontal.png";
        } else if (tmpState == state::body_topleft) {
            tmpChar = '6';
            tmpStr = "src/asset/game/nibbler/body_topleft.png";
        } else if (tmpState == state::body_topright) {
            tmpChar = '9';
            tmpStr = "src/asset/game/nibbler/body_topright.png";
        } else if (tmpState == state::body_bottomleft) {
            tmpChar = '1';
            tmpStr = "src/asset/game/nibbler/body_bottomleft.png";
        } else if (tmpState == state::body_bottomright) {
            tmpChar = 'T';
            tmpStr = "src/asset/game/nibbler/body_bottomright.png";
        }
        for (int j = 0; j < _gameMap.size(); ++j) {
            if (tmpY == std::get<2>(_gameMap[j]) && tmpX == std::get<3>(_gameMap[j])) {
                if (std::get<0>(_gameMap[j]) == ' ') {
                    _gameMap[j] = std::make_tuple(tmpChar, tmpStr, std::get<0>(_nibbler[i]), std::get<1>(_nibbler[i]));
                    // std::cout << std::get<0>(_gameMap[j]) << " " << std::get<1>(_gameMap[j]) << " " << std::get<2>(_gameMap[j]) << " " << std::get<3>(_gameMap[j]) << std::endl;
                } else if (std::get<0>(_gameMap[j]) == '#' || std::get<0>(_gameMap[j]) == 'H' || std::get<0>(_gameMap[j]) == 'L' || std::get<0>(_gameMap[j]) == 'R' || std::get<0>(_gameMap[j]) == 'D' || std::get<0>(_gameMap[j]) == 'G' || std::get<0>(_gameMap[j]) == 'o') {
                    // std::cout << "Can't move" << std::endl;
                }  else if (std::get<0>(_gameMap[j]) == 'f') {
                    // std::cout << "eat" << std::endl;
                } else {
                    // std::cout << "Game Over" << std::endl;
                    _gameOver = true; return none;
                }
            }
        }
    }
    return nextDirection;
}

/* END Region Init */

/* START Region Getter */

int Nibbler::get_score()
{
    return _score;
}

std::vector<std::tuple<char, std::string, int, int>> Nibbler::get_gameMap()
{
    return _gameMap;
}

std::string Nibbler::get_gameName()
{
    return "Nibbler";
}

bool Nibbler::get_gameOver()
{
    return _gameOver;
}

int Nibbler::get_nbFood()
{
    return _nbFood;
}

/* START Region Setter */

void Nibbler::set_score(int scoreValue)
{
    _score = _score + scoreValue;
}

void Nibbler::set_gameMap(const std::tuple<char, std::string, int, int>& entry)
{
    
}

/* END Region Setter */
