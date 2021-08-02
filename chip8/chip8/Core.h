#pragma once
#include <array>
#include <stack>

class Core
{
public:
	Core();
	~Core() = default;

private:
	static constexpr int MEMORY_SIZE = 4096;
	static constexpr int GP_REGISTERS_SIZE = 16;
	static constexpr int STACK_SIZE = 16;
	static constexpr int PC_START = 0x200;
	static constexpr int GRAPHICS_SIZE = 2048;
	static constexpr int FONST_SET_SIZE = 80;
	static constexpr int TIMER_START = 60;

	std::array<uint8_t, MEMORY_SIZE> memory;
	std::array<uint8_t, GRAPHICS_SIZE> gfx;

	std::array<uint8_t, GP_REGISTERS_SIZE> gp_registers;
	unsigned short index_register;
	unsigned short pc;

	unsigned short curr_opcode;

	unsigned char delay_timer;
	unsigned char sound_timer;

	std::stack<unsigned short> stack;


	void load_fontset();
};

