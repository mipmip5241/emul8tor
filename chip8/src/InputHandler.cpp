#include "../include/InputHandler.h"

InputHandler::InputHandler() : _keys_state()
{
	this->_keys_state[sf::Keyboard::Num1] = false;
	this->_keys_state[sf::Keyboard::Num2] = false;
	this->_keys_state[sf::Keyboard::Num3] = false;
	this->_keys_state[sf::Keyboard::Num4] = false;
	this->_keys_state[sf::Keyboard::Q] = false;
	this->_keys_state[sf::Keyboard::W] = false;
	this->_keys_state[sf::Keyboard::E] = false;
	this->_keys_state[sf::Keyboard::R] = false;
	this->_keys_state[sf::Keyboard::A] = false;
	this->_keys_state[sf::Keyboard::S] = false;
	this->_keys_state[sf::Keyboard::D] = false;
	this->_keys_state[sf::Keyboard::F] = false;
	this->_keys_state[sf::Keyboard::Z] = false;
	this->_keys_state[sf::Keyboard::X] = false;
	this->_keys_state[sf::Keyboard::C] = false;
	this->_keys_state[sf::Keyboard::V] = false;
}

void InputHandler::key_press(sf::Keyboard::Key key_pressed)
{
	this->_keys_state[key_pressed] = true;
}

void InputHandler::key_release(sf::Keyboard::Key key_released)
{
	this->_keys_state[key_released] = false;
}

const std::unordered_map<sf::Keyboard::Key, bool> InputHandler::get_key_states() const
{
	return this->_keys_state;
}
