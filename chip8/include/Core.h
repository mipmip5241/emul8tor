#pragma once
#include <array>
#include "InputHandler.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Core
{
public:

	static constexpr int GRAPHICS_HEIGHT = 32;
	static constexpr int GRAPHICS_WIDTH = 64;

	Core();
	~Core() = default;

	bool load_game(std::string path);
	
	bool emulate_cycle();
	void draw();
	void update_keys();
private:

	typedef void (Core::*opcode_handler)(void);

	static constexpr int MEMORY_SIZE = 4096;
	static constexpr int GP_REGISTERS_SIZE = 16;
	static constexpr int STACK_SIZE = 16;
	static constexpr int PC_START = 0x200;

	static constexpr int FONT_SET_SIZE = 80;
	static constexpr int TIMER_START = 60;
	static constexpr int NEXT_INST = 2;
	static constexpr int CARRY_FLAG = 15;
	static constexpr int EXTRACT_X_REGISTER = 8;
	static constexpr int EXTRACT_Y_REGISTER = 4;

	std::array<unsigned char, MEMORY_SIZE> _memory;
	std::array<std::array<unsigned char, GRAPHICS_WIDTH>, GRAPHICS_HEIGHT> _gfx;

	std::array<unsigned char, GP_REGISTERS_SIZE> _gp_registers;
	unsigned short _index_register;
	unsigned short _pc;

	unsigned short _curr_opcode;

	unsigned char _delay_timer;
	unsigned char _sound_timer;

	std::array<unsigned short, STACK_SIZE> _stack;
	unsigned short _sp;

	InputHandler _input;

	std::unordered_map<unsigned short, opcode_handler> _opcode_handlers;


	sf::RenderWindow _window;
	bool _draw_flag;

	void load_fontset();
	void update_timers();
	void setup_opcode_umap();

	void inst_0_classification();
	void inst_8_classification();
	void inst_E_classification();
	void inst_F_classification();


	// Opcode handlers
	void inst_0NNN(); 
	void inst_00E0(); 
	void inst_00EE(); 
	void inst_1NNN(); 
	void inst_2NNN(); 
	void inst_3XNN(); 
	void inst_4XNN(); 
	void inst_5XY0(); 
	void inst_6XNN(); 
	void inst_7XNN(); 
	void inst_8XY0(); 
	void inst_8XY1();
	void inst_8XY2();
	void inst_8XY3();
	void inst_8XY4();
	void inst_8XY5();
	void inst_8XY6();
	void inst_8XY7();
	void inst_8XYE();
	void inst_9XY0();
	void inst_ANNN();
	void inst_BNNN();
	void inst_CXNN();
	void inst_DXYN();
	void inst_EX9E();
	void inst_EXA1();
	void inst_FX07();
	void inst_FX0A();
	void inst_FX15();
	void inst_FX18();
	void inst_FX1E();
	void inst_FX29();
	void inst_FX33();
	void inst_FX55();
	void inst_FX65();

	
};

