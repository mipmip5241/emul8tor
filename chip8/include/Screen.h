#include "SFML/Graphics.hpp"

class Screen
{
private:
    static constexpr int WINDOW_WIDTH = 320;
    static constexpr int WINDOW_HEIGHT = 640;
    
    sf::RenderWindow _window;

public:
    Screen();
    ~Screen() = default;
};


