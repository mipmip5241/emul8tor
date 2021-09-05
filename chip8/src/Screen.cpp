#include "../include/Screen.h"


Screen::Screen() 
: _window((sf::VideoMode(this->WINDOW_WIDTH, this->WINDOW_HEIGHT)), "chip8") {}

Screen::~Screen()
{
    this->_window.close();
}

