#pragma once
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

class InputHandler
{
public:
	InputHandler();
	~InputHandler()=default;
	void update_keys_states();

	const std::unordered_map<sf::Keyboard::Key, bool> get_key_states() const;
private:
	std::unordered_map<sf::Keyboard::Key, bool> _keys_state;
};

