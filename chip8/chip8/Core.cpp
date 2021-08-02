#include "Core.h"



Core::Core()
	: memory(), gfx(),
	gp_registers(), index_register(0), pc(PC_START),
	curr_opcode(0),
	delay_timer(TIMER_START), sound_timer(TIMER_START),
	stack(), sp(0)
{
	this->memory.fill(0);
	this->gfx.fill(0);
	this->gp_registers.fill(0);

	this->load_fontset();
}

void Core::emulate_cycle()
{
	this->curr_opcode = this->memory[this->pc] << MERGE_OPCODE | this->memory[this->pc + 1];



	this->update_timers();
}

void Core::set_opcode(int val)
{
	this->curr_opcode = val;
}

void Core::load_fontset()
{
	const std::array<unsigned char, FONT_SET_SIZE> chip8_fontset =
	{
	  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	  0x20, 0x60, 0x20, 0x20, 0x70, // 1
	  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	std::copy(chip8_fontset.begin(), chip8_fontset.end(), this->memory.begin());
}

void Core::update_timers()
{
	if (this->delay_timer > 0)
	{
		this->delay_timer--;
	}

	if (this->sound_timer > 0)
	{
		if (sound_timer == 1)
		{
			// Make sound
		}
		this->sound_timer--;
	}
}

void Core::call_routine()
{
	pc = this->curr_opcode & 0x0FFF;
}

void Core::clear_screen()
{
	this->gfx.fill(0);
}

void Core::return_subroutine()
{
	pc = this->stack[this->sp];
	sp--;
}


