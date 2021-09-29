#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	InputHandler();
	~InputHandler()=default;

	void key_press(sf::Keyboard::Key  key_pressed);
	void key_release(sf::Keyboard::Key  key_released);

	const std::unordered_map<int, bool> get_key_states() const;
private:
	std::unordered_map<int, bool> _keys_state;

	int sfml_key_translate(sf::Keyboard::Key key);
};

