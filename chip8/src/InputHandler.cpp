#include "../include/InputHandler.h"

InputHandler::InputHandler() : _keys_state()
{
	this->_keys_state[1] = false; // 1
	this->_keys_state[2] = false; // 2
	this->_keys_state[3] = false; // 3
	this->_keys_state[12] = false; // 4
	this->_keys_state[4] = false; // Q
	this->_keys_state[5] = false; // W
	this->_keys_state[6] = false; // E
	this->_keys_state[13] = false; //R
	this->_keys_state[7] = false; // A
	this->_keys_state[8] = false; // S
	this->_keys_state[9] = false; // D
	this->_keys_state[14] = false; // F
	this->_keys_state[10] = false; // Z
	this->_keys_state[0] = false; // X
	this->_keys_state[11] = false; // C
	this->_keys_state[15] = false; // V
}

void InputHandler::key_press(sf::Keyboard::Key key_pressed)
{
	this->_keys_state[this->sfml_key_translate(key_pressed)] = true;
}

void InputHandler::key_release(sf::Keyboard::Key  key_released)
{
	this->_keys_state[this->sfml_key_translate(key_released)] = false;
}

int InputHandler::sfml_key_translate(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Num1:
		return 1;
	
	case sf::Keyboard::Key::Num2:
		return 2;

	case sf::Keyboard::Key::Num3:
		return 3;	

	case sf::Keyboard::Key::Num4:
		return 12;

	case sf::Keyboard::Key::Q:
		return 4;	

	case sf::Keyboard::Key::W:
		return 5;	

	case sf::Keyboard::Key::E:
		return 6;

	case sf::Keyboard::Key::R:
		return 13;

	case sf::Keyboard::Key::A:
		return 7;

	case sf::Keyboard::Key::S:
		return 8;

	case sf::Keyboard::Key::D:
		return 9;

	case sf::Keyboard::Key::F:
		return 14;

	case sf::Keyboard::Key::Z:
		return 10;

	case sf::Keyboard::Key::X:
		return 0;

	case sf::Keyboard::Key::C:
		return 11;

	case sf::Keyboard::Key::V:
		return 15;
	
	default:
		return -1;
	}
}

const std::unordered_map<int, bool> InputHandler::get_key_states() const
{
	return this->_keys_state;
}
