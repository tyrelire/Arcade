/**
 * @file Sfml.cpp
 * @author COUSTABEAU Maxime / MIGLIANI Benjamin / LAMAN-DUFLOT Ilhan (maxime.coustabeau@epitech.eu / benjamin.migliani@epitech.eu / Ilhan.laman-duflot@epitech.eu)
 * @brief EPITECH PROJECT, 2024
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "lib_Sfml.hpp"

/* START Region Loader */

LIB_SFML::LIB_SFML()
{

}

LIB_SFML::~LIB_SFML()
{
    close();
    // std::cout << "[arcade_sfml] Exit point !" << std::endl;
}

extern "C" IGraphic *start_lib()
{
    //printf("[arcade_sfml] Entry point !\n");
    return new LIB_SFML();
}

/* END Region Loader*/

/* START Region Init */

void LIB_SFML::init()
{
    window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "SFML Menu", sf::Style::Fullscreen);
    menuItems;

    if (!backgroundTexture.loadFromFile("src/asset/arcadeMenu.jpg")) {
        exit(84);
    }
    backgroundSprite.setTexture(backgroundTexture);

    float scaleX = window->getSize().x / (float)backgroundTexture.getSize().x;
    float scaleY = window->getSize().y / (float)backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    if (!font.loadFromFile("src/asset/arcadeClassic.ttf")) {
        exit(84);
    }

    _writen = false;

    // Main Menu
    sf::Text text0(_playerName, font, 100);
    sf::Text text1("Snake", font, 100);
    sf::Text text2("Nibbler", font, 100);
    //sf::Text text3("PacMan", font, 100);
    sf::Text text4("Settings", font, 100);
    sf::Text text5("Exit", font, 100);

    std::vector<sf::Text*> texts = {&text0, &text1, &text2, &text4, &text5};
    for (int i = 0; i < texts.size(); i++) {
        sf::FloatRect textRect = texts[i]->getLocalBounds();
        texts[i]->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        texts[i]->setPosition(window->getSize().x / 2, window->getSize().y / (texts.size() + 1) * (i + 1));
        this->menuItems.push_back(*texts[i]);
    }

    // Pause Menu
    sf::Text text6("Resume", font, 100);
    sf::Text text7("Settings", font, 100);
    sf::Text text8("Back To Main Menu", font, 100);

    std::vector<sf::Text*> ptexts = {&text6, &text7, &text8};
    for (int i = 0; i < ptexts.size(); i++) {
        sf::FloatRect ptextRect = ptexts[i]->getLocalBounds();
        ptexts[i]->setOrigin(ptextRect.left + ptextRect.width/2.0f, ptextRect.top  + ptextRect.height/2.0f);
        ptexts[i]->setPosition(window->getSize().x / 2, window->getSize().y / (ptexts.size() + 1) * (i + 1));
        this->pauseItems.push_back(*ptexts[i]);
    }

    // Settings Menu
    sf::Text text9("Back", font, 100);
    sf::Text text10("Volume UP", font, 100);
    sf::Text text11("Volume DOWN", font, 100);

    std::vector<sf::Text*> stexts = {&text9, &text10, &text11};
    for (int i = 0; i < stexts.size(); i++) {
        sf::FloatRect stextRect = stexts[i]->getLocalBounds();
        stexts[i]->setOrigin(stextRect.left + stextRect.width/2.0f, stextRect.top  + stextRect.height/2.0f);
        stexts[i]->setPosition(window->getSize().x / 2, window->getSize().y / (stexts.size() + 1) * (i + 1));
        this->settingsItems.push_back(*stexts[i]);
    }

    // End Menu
    sf::Text text12("Restart", font, 100);
    sf::Text text13("Back To Main Menu", font, 100);
    sf::Text text14("Settings", font, 100);
    sf::Text text15("Exit", font, 100);
    sf::Text text16("Score ", font, 100);
    sf::Text text17("playerName", font, 100);

    std::vector<sf::Text*> etexts = {&text17, &text16, &text12, &text13, &text14, &text15};
    for (int i = 0; i < etexts.size(); i++) {
        sf::FloatRect etextRect = etexts[i]->getLocalBounds();
        etexts[i]->setOrigin(etextRect.left + etextRect.width/2.0f, etextRect.top  + etextRect.height/2.0f);
        etexts[i]->setPosition(window->getSize().x / 2, window->getSize().y / (etexts.size() + 1) * (i + 1));
        this->endItems.push_back(*etexts[i]);
    }

    // Audio
    sound("src/asset/audio/arcade.wav", 30);

    set_selectedItem(0);

    set_nameLib("Sfml");
}

/* END Region Init */

/* START Region Menu */
const std::string LIB_SFML::main_menu()
{
    int padding = 10;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return "exit";
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && _writen == false) {
                    _selectedItem = (_selectedItem - 1 + menuItems.size()) % menuItems.size();
                } else if (event.key.code == sf::Keyboard::Down && _writen == false) {
                    _selectedItem = (_selectedItem + 1) % menuItems.size();
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G && _writen == false) {
                    return "nextLib";
                } else if (event.key.code == sf::Keyboard::Return) {
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
                            update();
                            return "setPlayerName";
                        } else {
                            if (_playerName.empty() == true || _playerName == " ")
                                _playerName = "playerName";
                            update();
                            return "setPlayerName";
                        }
                    }
                } else if (event.key.code == sf::Keyboard::Escape && _writen == false) {
                    return "exit";
                }
            } else if (_writen && event.type == sf::Event::TextEntered && event.text.unicode < 128 && isprint(event.text.unicode)) {
                if (_playerName.size() != 10) {
                    _playerName += static_cast<char>(event.text.unicode);
                }
                update();
                return "setPlayerName";
            } else if (_writen && event.key.code == sf::Keyboard::BackSpace && !_playerName.empty()) {
                _playerName.pop_back();
                update();
                return "setPlayerName";
            }
        }

        window->clear();
        window->draw(backgroundSprite);

        for (int i = 0; i < menuItems.size(); i++) {
            auto& item = menuItems[i];
            if (i == _selectedItem) {
                sf::RectangleShape rectangle(sf::Vector2f(item.getGlobalBounds().width + 2 * padding, item.getGlobalBounds().height + 2 * padding));
                rectangle.setPosition(item.getPosition().x - rectangle.getGlobalBounds().width / 2, item.getPosition().y - rectangle.getGlobalBounds().height / 2);
                rectangle.setOutlineThickness(2);
                rectangle.setOutlineColor(sf::Color::Magenta);
                rectangle.setFillColor(sf::Color::Transparent);
                window->draw(rectangle);
            }
            window->draw(item);
            if (i == menuItems.size() - 6 && _writen) {
                sf::RectangleShape rectangle(sf::Vector2f(item.getGlobalBounds().width + 2 * padding, item.getGlobalBounds().height + 2 * padding));
                rectangle.setPosition(item.getPosition().x - rectangle.getGlobalBounds().width / 2, item.getPosition().y - rectangle.getGlobalBounds().height / 2);
                rectangle.setOutlineThickness(2);
                rectangle.setOutlineColor(sf::Color::White);
                rectangle.setFillColor(sf::Color::Transparent);
                window->draw(rectangle);
            }
        }

        window->display();
    }
    return "";
}

const std::string LIB_SFML::pause_menu()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return "exit";
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return "resume";
                } else if (event.key.code == sf::Keyboard::Up) {
                    _selectedItem = (_selectedItem - 1 + pauseItems.size()) % pauseItems.size();
                } else if (event.key.code == sf::Keyboard::Down) {
                    _selectedItem = (_selectedItem + 1) % pauseItems.size();
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G) {
                    return "nextLib";
                } else if (event.key.code == sf::Keyboard::Return) {
                    if (pauseItems[_selectedItem].getString() == "Resume") {
                        return "resume";
                    } else if (pauseItems[_selectedItem].getString() == "Settings") {
                        return "settingsPause";
                    } else if (pauseItems[_selectedItem].getString() == "Back To Main Menu") {
                        return "backMain";
                    }
                }
            }
        }

        window->clear();
        window->draw(backgroundSprite);

        for (int i = 0; i < pauseItems.size(); i++) {
            auto& item = pauseItems[i];
            if (i == _selectedItem) {
                item.setFillColor(sf::Color::Magenta);
                sf::RectangleShape rectangle(sf::Vector2f(item.getGlobalBounds().width + 20, item.getGlobalBounds().height + 20));
                rectangle.setPosition(item.getPosition().x - 10 - item.getGlobalBounds().width / 2, item.getPosition().y - 10 - item.getGlobalBounds().height / 2);
                rectangle.setOutlineThickness(2);
                rectangle.setOutlineColor(sf::Color::Magenta);
                rectangle.setFillColor(sf::Color::Transparent);
                window->draw(rectangle);
            } else {
                item.setFillColor(sf::Color::White);
            }
            window->draw(item);
        }

        window->display();
    }
    return "";
}

const std::string LIB_SFML::end_menu(std::string playerName, int score)
{
    endItems[0].setString(playerName);
    sf::FloatRect tmpRect = endItems[0].getLocalBounds();
    if (!_playerName.empty()) {
        endItems[0].setOrigin(tmpRect.left + tmpRect.width/2.0f, tmpRect.top  + tmpRect.height/2.0f);
        endItems[0].setPosition(window->getSize().x / 2, 300 + 0 * 100);
    } else {
        endItems[0].setOrigin(144, 34.5);
        endItems[0].setPosition(960, 200);
    }

    endItems[1].setString("Score " + std::to_string(score));
    sf::FloatRect tmpRec = endItems[1].getLocalBounds();
    if (!_playerName.empty()) {
        endItems[1].setOrigin(tmpRec.left + tmpRec.width/2.0f, tmpRec.top  + tmpRec.height/2.0f);
        endItems[1].setPosition(window->getSize().x / 2, 600 + 0 * 100);
    } else {
        endItems[1].setOrigin(144, 34.5);
        endItems[1].setPosition(960, 200);
    }

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return "exit";
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return "exit";
                } else if (event.key.code == sf::Keyboard::Up) {
                    _selectedItem = (_selectedItem - 1 + endItems.size()) % endItems.size();
                } else if (event.key.code == sf::Keyboard::Down) {
                    _selectedItem = (_selectedItem + 1) % endItems.size();
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G) {
                    return "nextLib";
                } else if (event.key.code == sf::Keyboard::Return) {
                    if (endItems[_selectedItem].getString() == "Restart") {
                        return "restart";
                    } else if (endItems[_selectedItem].getString() == "Back To Main Menu") {
                        return "backMain";
                    } else if (endItems[_selectedItem].getString() == "Settings") {
                        return "settingsEnd";
                    } else if (endItems[_selectedItem].getString() == "Exit") {
                        return "exit";
                    }
                }
            }
        }

        window->clear();
        window->draw(backgroundSprite);

        for (int i = 0; i < endItems.size(); i++) {
            auto& item = endItems[i];
            if (i == _selectedItem) {
                item.setFillColor(sf::Color::Magenta);
                sf::RectangleShape rectangle(sf::Vector2f(item.getGlobalBounds().width + 20, item.getGlobalBounds().height + 20));
                rectangle.setPosition(item.getPosition().x - 10 - item.getGlobalBounds().width / 2, item.getPosition().y - 10 - item.getGlobalBounds().height / 2);
                rectangle.setOutlineThickness(2);
                rectangle.setOutlineColor(sf::Color::Magenta);
                rectangle.setFillColor(sf::Color::Transparent);
                window->draw(rectangle);
            } else {
                item.setFillColor(sf::Color::White);
            }
            window->draw(item);
        }

        window->display();
    }
    return "";
}

const std::string LIB_SFML::settings_menu()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return "exit";
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return "backSettings";
                } else if (event.key.code == sf::Keyboard::Up) {
                    _selectedItem = (_selectedItem - 1 + settingsItems.size()) % settingsItems.size();
                } else if (event.key.code == sf::Keyboard::Down) {
                    _selectedItem = (_selectedItem + 1) % settingsItems.size();
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G) {
                    return "nextLib";
                } else if (event.key.code == sf::Keyboard::Return) {
                    if (settingsItems[_selectedItem].getString() == "Back") {
                        return "backSettings";
                    } else if (settingsItems[_selectedItem].getString() == "Volume UP") {
                        return "volume up";
                    } else if (settingsItems[_selectedItem].getString() == "Volume DOWN") {
                        return "volume down";
                    }
                }
            }
        }

        window->clear();
        window->draw(backgroundSprite);

        for (int i = 0; i < settingsItems.size(); i++) {
            auto& item = settingsItems[i];
            if (i == _selectedItem) {
                item.setFillColor(sf::Color::Magenta);
                sf::RectangleShape rectangle(sf::Vector2f(item.getGlobalBounds().width + 20, item.getGlobalBounds().height + 20));
                rectangle.setPosition(item.getPosition().x - 10 - item.getGlobalBounds().width / 2, item.getPosition().y - 10 - item.getGlobalBounds().height / 2);
                rectangle.setOutlineThickness(2);
                rectangle.setOutlineColor(sf::Color::Magenta);
                rectangle.setFillColor(sf::Color::Transparent);
                window->draw(rectangle);
            } else {
                item.setFillColor(sf::Color::White);
            }
            window->draw(item);
        }

        window->display();
    }
    return "";
}


const std::string LIB_SFML::game_menu(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame)
{
    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    sf::Time interval = sf::seconds(0.5f);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return "exit";
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G) {
                return "nextLib";
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                return "backMain";
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J) {
                return "nextGame";
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                return "restart";
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                return "pause";
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
                return "top";
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                return "down";
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                return "left";
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                return "right";
            }
        }

        // clock
        elapsed += clock.restart();

        if (elapsed >= interval)
        {
            return "auto";
            elapsed -= interval;
        }

        //draw_game();
        draw_map(_gameMap, nameGame);
    }
    return "";
}

/* END Region Menu */

/* START Region Draw */

void LIB_SFML::draw_game()
{
    window->clear(sf::Color(96, 108, 84));
    window->display();
}

void LIB_SFML::draw_score()
{

}

void LIB_SFML::draw_playerName()
{

}

void LIB_SFML::draw_allSprite()
{
    if (window != nullptr) {
        for (const auto& item : menuItems) {
            window->draw(item);
        }
    }
}

void LIB_SFML::draw_map(std::vector<std::tuple<char, std::string, int, int>> _gameMap, std::string nameGame)
{
    if (nameGame == "Snake") {
        window->clear(sf::Color(96, 108, 84));
    } else if (nameGame == "Nibbler") {
        window->clear(sf::Color::Black);
    }

    sf::Vector2u windowSize = window->getSize();

    int gridSize = sqrt(_gameMap.size());
    int spriteSize = std::min(static_cast<int>(windowSize.x), static_cast<int>((windowSize.y * 0.95) / gridSize));

    int offsetX = (windowSize.x - spriteSize * gridSize) / 2;
    int offsetY = (windowSize.y - spriteSize * gridSize) / 2;

    for (const auto& entry : _gameMap) {
        char c = std::get<0>(entry);
        std::string imageFile = std::get<1>(entry);
        int x = std::get<2>(entry);
        int y = std::get<3>(entry);

        if (!imageFile.empty()) {
            sf::Texture texture;
            if (texture.loadFromFile(imageFile)) {
                sf::Sprite sprite(texture);
                sprite.setScale(sf::Vector2f(spriteSize / static_cast<float>(texture.getSize().x), spriteSize / static_cast<float>(texture.getSize().y)));
                sprite.setPosition(offsetX + x * spriteSize, offsetY + y * spriteSize);
                window->draw(sprite);
            } else {
                std::cerr << "Unable to load image " << imageFile << std::endl;
            }
        }
    }
    window->display();
}

/* END Region Draw */

/* START Region Event */

void LIB_SFML::stop()
{
    
}

void LIB_SFML::close()
{
    if (window != nullptr) {
        window->close();
    }
    delete window;
}

void LIB_SFML::pause()
{
    
}

void LIB_SFML::clear()
{
    if (window != nullptr) {
        window->clear();
    }
}

/* END Region Event */

/* START Region Update */

void LIB_SFML::update()
{
    menuItems[0].setString(_playerName);
    sf::FloatRect tmpRect = menuItems[0].getLocalBounds();
    if (!_playerName.empty()) {
        menuItems[0].setOrigin(tmpRect.left + tmpRect.width/2.0f, tmpRect.top  + tmpRect.height/2.0f);
        menuItems[0].setPosition(window->getSize().x / 2, 300 + 0 * 100);
    } else {
        menuItems[0].setOrigin(144, 34.5);
        menuItems[0].setPosition(960, 200);
    }
}

/* END Region Update */

/* START Region Music */

void LIB_SFML::sound(std::string pathMusic, int volume)
{
    if (!music.openFromFile(pathMusic)) {
        std::cerr << "Impossible de charger le fichier audio" << std::endl;
    }
    set_volume(volume);
    music.setLoop(true);
    music.play();
}

void LIB_SFML::set_volume(int value)
{
    music.setVolume(value);
}

/* END Region Music */

/* START Region Setter */


void LIB_SFML::set_playerName(std::string name)
{
    _playerName = name;
}

void LIB_SFML::set_selectedItem(int index)
{
    _selectedItem = index;
}

void LIB_SFML::set_nameLib(std::string lib)
{
    _nameLib = lib;
}

/* # END Region Setter*/

/* # START Region Getter */

const std::string LIB_SFML::get_playerName()
{
    return _playerName;
}

int LIB_SFML::get_selectedItem()
{
    return _selectedItem;
}

const std::string LIB_SFML::get_nameLib()
{
    return _nameLib;
}

/* # END Region Getter*/
