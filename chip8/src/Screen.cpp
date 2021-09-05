#include "../include/Screen.h"
#include "SFML/Window.hpp"

Screen::Screen() 
: _window((sf::VideoMode(Core::GRAPHICS_WIDTH, Core::GRAPHICS_HEIGHT, 1)), "chip8") {}

Screen::~Screen()
{
    this->_window.close();
}


void Screen::draw(std::array<std::array<unsigned char, Core::GRAPHICS_HEIGHT>, Core::GRAPHICS_WIDTH>& gfx)
{
    this->_window.clear(sf::Color::Black);
    sf::Image image(Core::GRAPHICS_WIDTH, Core::GRAPHICS_HEIGHT, sf::Color(0, 0, 0));
    sf::Sprite sprite;
    image.LoadFromPixels(Core::GRAPHICS_WIDTH, Core::GRAPHICS_HEIGHT, gfx);
    sprite.SetImage(image);
    this->_window.Draw(sprite);
    this->_window.display();
}