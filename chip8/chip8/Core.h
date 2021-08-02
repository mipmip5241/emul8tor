#pragma once
#include <array>

class Core
{
public:
	Core();
	~Core() = default;


	void emulate_cycle();
	//test
	void set_opcode(int val);

private:
	static constexpr int MEMORY_SIZE = 4096;
	static constexpr int GP_REGISTERS_SIZE = 16;
	static constexpr int STACK_SIZE = 16;
	static constexpr int PC_START = 0x200;
	static constexpr int GRAPHICS_SIZE = 2048;
	static constexpr int FONT_SET_SIZE = 80;
	static constexpr int TIMER_START = 60;
	static constexpr int MERGE_OPCODE = 8;

	std::array<unsigned char, MEMORY_SIZE> memory;
	std::array<unsigned char, GRAPHICS_SIZE> gfx;

	std::array<unsigned char, GP_REGISTERS_SIZE> gp_registers;
	unsigned short index_register;
	unsigned short pc;

	unsigned short curr_opcode;

	unsigned char delay_timer;
	unsigned char sound_timer;

	std::array<unsigned short, STACK_SIZE> stack;
	unsigned short sp;


	void load_fontset();
	void update_timers();

	// Opcode handlers
	void call_routine();
	void clear_screen();
	void return_subroutine();
};

