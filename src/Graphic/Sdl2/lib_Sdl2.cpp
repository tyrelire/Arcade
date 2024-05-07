/**
 * @file Lib_Sdl2.cpp
 * @author COUSTABEAU Maxime / MIGLIANI Benjamin / LAMAN-DUFLOT Ilhan (maxime.coustabeau@epitech.eu / benjamin.migliani@epitech.eu / Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "lib_Sdl2.hpp"

/* START Region Loader */

LIB_SDL2::LIB_SDL2()
{
    
}

LIB_SDL2::~LIB_SDL2()
{
    close();
    // std::cout << "[arcade_sdl] Exit point !" << std::endl;
}

extern "C" IGraphic *start_lib()
{
    //printf("[arcade_sdl] Entry point !\n");
    return new LIB_SDL2();
}

/* END Region Loader */

/* START Region Init */

void LIB_SDL2::init()
{
    window = SDL_CreateWindow("SDL2 Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(window, -1, 0);
    _writen = false;

    TTF_Init();
    font = TTF_OpenFont("src/asset/arcadeClassic.ttf", 50);
    if (!font) {
        exit(84);
    }

    SDL_Surface* bgSurface = IMG_Load("src/asset/arcadeMenuSDL.jpg");
    if (!bgSurface) {
        exit(84);
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    // main menu
    std::vector<std::string> labels = {_playerName, "Snake", "Nibbler", "Settings", "Exit"};
    for (int i = 0; i < labels.size(); i++) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, labels[i].c_str(), {255, 255, 255});
        SDL_Surface* hoverTextSurface = TTF_RenderText_Solid(font, labels[i].c_str(), {255, 0, 255, 255});
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Texture* hoverTextTexture = SDL_CreateTextureFromSurface(renderer, hoverTextSurface);
        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(hoverTextSurface);
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        SDL_Rect textRect = {windowWidth / 2 - textSurface->w / 2, 200 + i * 100, textSurface->w, textSurface->h};
        menuItems.push_back({textTexture, hoverTextTexture, textRect});
    }

    // pause menu
    std::vector<std::string> labelsPause = {"Resume", "Settings", "Back To Main Menu"};
    for (int i = 0; i < labelsPause.size(); i++) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, labelsPause[i].c_str(), {255, 255, 255});
        SDL_Surface* hoverTextSurface = TTF_RenderText_Solid(font, labelsPause[i].c_str(), {255, 0, 255, 255});
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Texture* hoverTextTexture = SDL_CreateTextureFromSurface(renderer, hoverTextSurface);
        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(hoverTextSurface);
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        SDL_Rect textRect = {windowWidth / 2 - textSurface->w / 2, 200 + i * 100, textSurface->w, textSurface->h};
        pauseItems.push_back({textTexture, hoverTextTexture, textRect});
    }

    // end menu
    std::vector<std::string> labelsEnd = {"playerName", "Score", "Restart", "Back To Main Menu", "Settings", "Exit"};
    for (int i = 0; i < labelsEnd.size(); i++) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, labelsEnd[i].c_str(), {255, 255, 255});
        SDL_Surface* hoverTextSurface = TTF_RenderText_Solid(font, labelsEnd[i].c_str(), {255, 0, 255, 255});
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Texture* hoverTextTexture = SDL_CreateTextureFromSurface(renderer, hoverTextSurface);
        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(hoverTextSurface);
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        SDL_Rect textRect = {windowWidth / 2 - textSurface->w / 2, 200 + i * 100, textSurface->w, textSurface->h};
        endItems.push_back({textTexture, hoverTextTexture, textRect});
    }

    // settings menu
    std::vector<std::string> labelsSettings = {"Back", "Volume Up", "Volume Down"};
    for (int i = 0; i < labelsSettings.size(); i++) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, labelsSettings[i].c_str(), {255, 255, 255});
        SDL_Surface* hoverTextSurface = TTF_RenderText_Solid(font, labelsSettings[i].c_str(), {255, 0, 255, 255});
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Texture* hoverTextTexture = SDL_CreateTextureFromSurface(renderer, hoverTextSurface);
        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(hoverTextSurface);
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        SDL_Rect textRect = {windowWidth / 2 - textSurface->w / 2, 200 + i * 100, textSurface->w, textSurface->h};
        settingsItems.push_back({textTexture, hoverTextTexture, textRect});
    }

    // audio
    sound("./src/asset/audio/arcade.mp3", 30);

    set_selectedItem(0);
    set_nameLib("Sdl2");
    _imgLoaded = 0;
}

/* END Region Init */

/* START Region Menu */

const std::string LIB_SDL2::main_menu()
{
    int padding = 10;

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return "exit";
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP && _writen == false) {
                    _selectedItem = (_selectedItem - 1 + menuItems.size()) % menuItems.size();
                } else if (event.key.keysym.sym == SDLK_DOWN && _writen == false) {
                    _selectedItem = (_selectedItem + 1) % menuItems.size();
                } else if (event.key.keysym.sym == SDLK_g && _writen == false) {
                    return "nextLib";
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (_selectedItem == menuItems.size() - 1 && _writen == false) {
                        return "exit";
                    } else if (_selectedItem == menuItems.size() - 2 && _writen == false) {
                        return "settingsMain";
                    } else if ((_selectedItem == menuItems.size() - 4)  && _writen == false) {
                        return "snake";
                    } else if ((_selectedItem == menuItems.size() - 3) && _writen == false) {
                        return "nibbler";
                    } else if (_selectedItem == menuItems.size() - 5) {
                        _writen = !_writen;
                        if (_writen) {
                            if (_playerName == "playerName")
                                _playerName = "";
                            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                            update();
                            return "setPlayerName";
                        } else {
                            if (_playerName.empty())
                                _playerName = "playerName";
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                            update();
                            return "setPlayerName";
                        }
                    }
                } else if (_writen && event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z || event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) {
                    if (_playerName.size() != 10) {
                        _playerName += event.key.keysym.sym;
                    }
                    update();
                    return "setPlayerName";
                } else if (_writen && event.key.keysym.sym == SDLK_BACKSPACE && !_playerName.empty()) {
                    _playerName.pop_back();
                    update();
                    return "setPlayerName";
                } else if (event.key.keysym.sym == SDLK_ESCAPE && _writen == false) {
                    return "exit";
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        for (int i = 0; i < menuItems.size(); i++) {
            if (i == _selectedItem) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                SDL_Rect paddedRect = {menuItems[i].rect.x - padding, menuItems[i].rect.y - padding, menuItems[i].rect.w + 2 * padding, menuItems[i].rect.h + 2 * padding};
                SDL_RenderDrawRect(renderer, &paddedRect);
                SDL_RenderCopy(renderer, menuItems[i].hoverTexture, NULL, &menuItems[i].rect);
            } else {
                SDL_RenderCopy(renderer, menuItems[i].texture, NULL, &menuItems[i].rect);
            }
            if (i == menuItems.size() - 6 && _writen) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_Rect paddedRect = {menuItems[i].rect.x - padding, menuItems[i].rect.y - padding, menuItems[i].rect.w + 2 * padding, menuItems[i].rect.h + 2 * padding};
                SDL_RenderDrawRect(renderer, &paddedRect);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
        }
        SDL_RenderPresent(renderer);
    }
    return "";
}


const std::string LIB_SDL2::pause_menu()
{
    int padding = 10;

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return "exit";
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    _selectedItem = (_selectedItem - 1 + pauseItems.size()) % pauseItems.size();
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    _selectedItem = (_selectedItem + 1) % pauseItems.size();
                } else if (event.key.keysym.sym == SDLK_g) {
                    return "nextLib";
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (_selectedItem == pauseItems.size() - 3) {
                        return "resume";
                    } else if (_selectedItem == pauseItems.size() - 2) {
                        return "settingsPause";
                    } else if (_selectedItem == pauseItems.size() - 1) {
                        return "backMain";
                    }
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return "resume";
                }
            }

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            for (int i = 0; i < pauseItems.size(); i++) {
                if (i == _selectedItem) {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                    SDL_Rect paddedRect = {pauseItems[i].rect.x - padding, pauseItems[i].rect.y - padding, pauseItems[i].rect.w + 2 * padding, pauseItems[i].rect.h + 2 * padding};
                    SDL_RenderDrawRect(renderer, &paddedRect);
                    SDL_RenderCopy(renderer, pauseItems[i].hoverTexture, NULL, &pauseItems[i].rect);
                } else {
                    SDL_RenderCopy(renderer, pauseItems[i].texture, NULL, &pauseItems[i].rect);
                }
            }
            SDL_RenderPresent(renderer);
        }
    }
    return "";
}


const std::string LIB_SDL2::end_menu(std::string playerName, int score)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, playerName.c_str(), {255, 255, 255, 255});
    SDL_Surface* hoverTextSurface = TTF_RenderText_Solid(font, playerName.c_str(), {255, 0, 255, 255});
    endItems[0].texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    endItems[0].hoverTexture = SDL_CreateTextureFromSurface(renderer, hoverTextSurface);
    int windowWidth, windowHeight;
    if (!_playerName.empty()) {
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        endItems[0].rect = {windowWidth / 2 - textSurface->w / 2, 200 + 0 * 100, textSurface->w, textSurface->h};
    }
    textSurface = TTF_RenderText_Solid(font, ("Score " + std::to_string(score)).c_str(), {255, 255, 255, 255});
    hoverTextSurface = TTF_RenderText_Solid(font, ("Score: " + std::to_string(score)).c_str(), {255, 0, 255, 255});
    endItems[1].texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    endItems[1].hoverTexture = SDL_CreateTextureFromSurface(renderer, hoverTextSurface);
    int windoWidth, windoHeight;
    if (!_playerName.empty()) {
        SDL_GetWindowSize(window, &windoWidth, &windoHeight);
        endItems[1].rect = {windoWidth / 2 - textSurface->w / 2, 300 + 0 * 100, textSurface->w, textSurface->h};
    }
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(hoverTextSurface);

    int padding = 10;

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return "exit";
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    _selectedItem = (_selectedItem - 1 + endItems.size()) % endItems.size();
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    _selectedItem = (_selectedItem + 1) % endItems.size();
                } else if (event.key.keysym.sym == SDLK_g) {
                    return "nextLib";
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (_selectedItem == endItems.size() - 4) {
                        return "restart";
                    } else if (_selectedItem == endItems.size() - 3) {
                        return "backMain";
                    } else if (_selectedItem == endItems.size() - 2) {
                        return "settingsEnd";
                    } else if (_selectedItem == endItems.size() - 1) {
                        return "exit";
                    }
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return "exit";
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        for (int i = 0; i < endItems.size(); i++) {
            if (i == _selectedItem) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                SDL_Rect paddedRect = {endItems[i].rect.x - padding, endItems[i].rect.y - padding, endItems[i].rect.w + 2 * padding, endItems[i].rect.h + 2 * padding};
                SDL_RenderDrawRect(renderer, &paddedRect);
                SDL_RenderCopy(renderer, endItems[i].hoverTexture, NULL, &endItems[i].rect);
            } else {
                SDL_RenderCopy(renderer, endItems[i].texture, NULL, &endItems[i].rect);
            }
        }
        SDL_RenderPresent(renderer);
    }
    return "";
}

const std::string LIB_SDL2::settings_menu()
{
    int padding = 10;

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return "exit";
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    _selectedItem = (_selectedItem - 1 + settingsItems.size()) % settingsItems.size();
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    _selectedItem = (_selectedItem + 1) % settingsItems.size();
                } else if (event.key.keysym.sym == SDLK_g) {
                    return "nextLib";
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (_selectedItem == settingsItems.size() - 3) {
                        return "backSettings";
                    } else if (_selectedItem == settingsItems.size() - 2) {
                        return "volume up";
                    } else if (_selectedItem == settingsItems.size() - 1) {
                        return "volume down";
                    }
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return "backSettings";
                }
            }

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            for (int i = 0; i < settingsItems.size(); i++) {
                if (i == _selectedItem) {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                    SDL_Rect paddedRect = {settingsItems[i].rect.x - padding, settingsItems[i].rect.y - padding, settingsItems[i].rect.w + 2 * padding, settingsItems[i].rect.h + 2 * padding};
                    SDL_RenderDrawRect(renderer, &paddedRect);
                    SDL_RenderCopy(renderer, settingsItems[i].hoverTexture, NULL, &settingsItems[i].rect);
                } else {
                    SDL_RenderCopy(renderer, settingsItems[i].texture, NULL, &settingsItems[i].rect);
                }
            }
            SDL_RenderPresent(renderer);
        }
    }
    return "";
}

const std::string LIB_SDL2::game_menu(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame)
{
    Uint32 startTime = SDL_GetTicks();

    bool action = false;

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return "exit";
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g) {
                return "nextLib";
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) {
                return "backMain";
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_j) {
                return "nextGame";
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                return "restart";
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                return "pause";
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z) {
                return "top";
            }  else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s) {
                return "down";
            }  else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) {
                return "left";
            }  else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d) {
                return "right";
            }
        }
        //draw_game();
        draw_map(_gameMap, nameGame);

        //clock
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - startTime;

        if (elapsedTime >= 500 && !action) {
            // std::cout << "Action déclenchée après 1 seconde." << std::endl;
            action = true;
            return "auto";
        }
    }
    return "";
}

/* END Region Menu */

/* START Region Draw */

void LIB_SDL2::draw_game()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 96, 108, 84, 255);
    SDL_RenderPresent(renderer);
}

void LIB_SDL2::draw_score()
{

}

void LIB_SDL2::draw_playerName()
{

}

void LIB_SDL2::draw_allSprite()
{

}

void LIB_SDL2::draw_map(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame)
{
    SDL_RenderClear(renderer);

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int gridSize = sqrt(_gameMap.size());
    int spriteSize = std::min(windowWidth / gridSize, windowHeight / gridSize);

    int offsetX = (windowWidth - spriteSize * gridSize) / 2;
    int offsetY = (windowHeight - spriteSize * gridSize) / 2;

    if (nameGame == "Snake") {
        SDL_SetRenderDrawColor(renderer, 96, 108, 84, 255);
    } else if (nameGame == "Nibbler") {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    for (const auto& entry : _gameMap) {
        char c = std::get<0>(entry);
        std::string imageFile = std::get<1>(entry);
        int x = std::get<2>(entry);
        int y = std::get<3>(entry);

        if (!imageFile.empty()) {
            SDL_Texture* texture = IMG_LoadTexture(renderer, imageFile.c_str());
            if (!texture) {
                std::cerr << "Unable to load image " << imageFile << ": " << SDL_GetError() << std::endl;
                continue;
            }

            SDL_Rect dst;
            dst.x = offsetX + x * spriteSize;
            dst.y = offsetY + y * spriteSize;
            dst.w = spriteSize;
            dst.h = spriteSize;

            SDL_RenderCopy(renderer, texture, NULL, &dst);

            SDL_DestroyTexture(texture);
        }
    }

    SDL_RenderPresent(renderer);
}

/* END Region Draw */

/* START Region Event */

void LIB_SDL2::close()
{
    for (auto& item : menuItems) {
        SDL_DestroyTexture(item.texture);
    }
    for (auto& item : pauseItems) {
        SDL_DestroyTexture(item.texture);
    }
    SDL_DestroyTexture(backgroundTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    Mix_CloseAudio();

    SDL_Quit();
}

void LIB_SDL2::stop()
{
    
}

void LIB_SDL2::pause()
{
    pause_menu();
}

void LIB_SDL2::clear()
{
    SDL_RenderClear(renderer);
}

/* END Region Event */

/* START Region Update */

void LIB_SDL2::update()
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, _playerName.c_str(), {255, 255, 255, 255});
    SDL_Surface* hoverTextSurface = TTF_RenderText_Solid(font, _playerName.c_str(), {255, 0, 255, 255});
    menuItems[menuItems.size() - 5].texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    menuItems[menuItems.size() - 5].hoverTexture = SDL_CreateTextureFromSurface(renderer, hoverTextSurface);
    int windowWidth, windowHeight;
    if (!_playerName.empty()) {
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        menuItems[menuItems.size() - 5].rect = {windowWidth / 2 - textSurface->w / 2, 200 + 0 * 100, textSurface->w, textSurface->h};
    }
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(hoverTextSurface);
}

/* END Region Update */


/* # START Region Sound */

void LIB_SDL2::sound(std::string pathMusic, int volume)
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS(pathMusic.c_str());
    if (!music) {
        std::cerr << "Impossible de charger la musique: " << Mix_GetError() << std::endl;
    }
    set_volume(volume);
    Mix_PlayMusic(music, -1);
}

void LIB_SDL2::set_volume(int value)
{
    Mix_VolumeMusic(value);
}

/* END Region Sound */

/* START Region Setter */

void LIB_SDL2::set_playerName(std::string name)
{
    _playerName = name;
}

void LIB_SDL2::set_selectedItem(int index)
{
    _selectedItem = index;
}

void LIB_SDL2::set_nameLib(std::string lib)
{
    _nameLib = lib;
}

/* END Region Setter*/

/* START Region Getter */


const std::string LIB_SDL2::get_playerName()
{
    return _playerName;
}

int LIB_SDL2::get_selectedItem()
{
    return _selectedItem;
}

const std::string LIB_SDL2::get_nameLib()
{
    return _nameLib;
}

/* # END Region Getter*/
