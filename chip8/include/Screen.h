#pragma once
#include "Core.h"
#include "SFML/Graphics.hpp"

class Screen
{
private:
    sf::RenderWindow _window;

public:
    Screen();
    ~Screen();

    void draw(std::array<std::array<unsigned char, Core::GRAPHICS_HEIGHT>, Core::GRAPHICS_WIDTH>& gfx);
};


