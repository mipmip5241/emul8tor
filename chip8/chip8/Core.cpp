#include "Core.h"

Core::Core()
	: memory(), gfx(),
	gp_registers(), index_register(0), pc(PC_START),
	curr_opcode(0),
	delay_timer(TIMER_START), sound_timer(TIMER_START),
	stack(), sp(0), keys()
{
	this->memory.fill(0);
	this->inst_00E0();
	this->gp_registers.fill(0);
	this->keys.fill(0);

	this->load_fontset();
}

void Core::emulate_cycle()
{
	constexpr int MERGE_OPCODE = 8;

	this->curr_opcode = this->memory[this->pc] << MERGE_OPCODE | this->memory[this->pc + 1];


	this->pc += NEXT_INST;
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

void Core::inst_0NNN()
{
	this->pc = this->curr_opcode & 0x0FFF;
}

void Core::inst_00E0()
{
	for (int i = 0; i < GRAPHICS_WIDTH; i++)
	{
		this->gfx[i].fill(0);
	}
}

void Core::inst_00EE()
{
	this->pc = this->stack[this->sp];
	this->sp--;
}

void Core::inst_1NNN()
{
	this->inst_0NNN();
}

void Core::inst_2NNN()
{
	this->stack[this->sp] = this->pc;
	this->sp++;
	this->inst_0NNN();
}

void Core::inst_3XNN()
{
	if ((this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) == ((this->curr_opcode & 0x00FF) >> EXTRACT_Y_REGISTER))
	{
		this->pc += NEXT_INST;
	}
}

void Core::inst_4XNN()
{
	if ((this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) != (this->curr_opcode & 0x00FF))
	{
		this->pc += NEXT_INST;
	}
}

void Core::inst_5XY0()
{
	if ((this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) == (this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]))
	{
		this->pc += NEXT_INST;
	}
}

void Core::inst_6XNN()
{
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = (this->curr_opcode & 0x00FF);
}

void Core::inst_7XNN()
{
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] += (this->curr_opcode & 0x00FF);
}

void Core::inst_8XY0()
{
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER];
}

void Core::inst_8XY1()
{
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = 
		(this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] | this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]);
}

void Core::inst_8XY2()
{
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = 
		(this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] & this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]);
}

void Core::inst_8XY3()
{
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] =
		(this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] ^ this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]);
}

void Core::inst_8XY4()
{
	if ((this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] + this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]) > 0xFF)
	{
		this->gp_registers[CARRY_FLAG] = 1;
	}
	else
	{
		this->gp_registers[CARRY_FLAG] = 0;
	}
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] += this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER];
}

void Core::inst_8XY5()
{
	if ((this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] - this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]) > 0x00)
	{
		this->gp_registers[CARRY_FLAG] = 1;
	}
	else
	{
		this->gp_registers[CARRY_FLAG] = 0;
	}
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] -= this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER];
}

void Core::inst_8XY6()
{
	this->gp_registers[CARRY_FLAG] = (this->gp_registers[this->curr_opcode & 0x0F00] & 0x0F);
	this->gp_registers[this->curr_opcode & 0x0F00] >>= 1;
}

void Core::inst_8XY7()
{
	if ((this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER] - this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) < 0x00)
	{
		this->gp_registers[CARRY_FLAG] = 1;
	}
	else
	{
		this->gp_registers[CARRY_FLAG] = 0;
	}
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]
		= this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER] - this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER];
}

void Core::inst_8XYE()
{
	this->gp_registers[CARRY_FLAG] = (this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] & 0xF0);
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] <<= 1;
}

void Core::inst_9XY0()
{
	if ((this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) != (this->gp_registers[(this->curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]))
	{
		this->pc += NEXT_INST;
	}
}

void Core::inst_ANNN()
{
	this->index_register = (this->curr_opcode & 0x0FFF);
}

void Core::inst_BNNN()
{
	this->pc = this->gp_registers[0] + (this->curr_opcode & 0x0FFF);
}

void Core::inst_CXNN()
{
	constexpr int GET_RANDOM_NUM = 256;
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = ((std::rand() % GET_RANDOM_NUM) & (this->curr_opcode & 0x00FF));
}


void Core::inst_EX9E()
{
	if (this->keys[this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]] != 0)
	{
		this->pc += NEXT_INST;
	}
}

void Core::inst_EXA1()
{
	if (this->keys[this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]] == 0)
	{
		this->pc += NEXT_INST;
	}
}

void Core::inst_FX07()
{
	this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = this->delay_timer;
}


void Core::inst_FX15()
{
	this->delay_timer = this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER];
}

void Core::inst_FX18()
{
	this->sound_timer = this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER];
}

void Core::inst_FX1E()
{
	this->index_register += this->gp_registers[(this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER];
}


void Core::inst_FX55()
{
	for (int offset = 0; offset < ((this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER); offset++)
	{
		this->memory[this->index_register + offset] = this->gp_registers[offset];
	}
}

void Core::inst_FX65()
{
	for (int offset = 0; offset < ((this->curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER); offset++)
	{
		this->gp_registers[offset] = this->memory[this->index_register + offset];
	}
}




