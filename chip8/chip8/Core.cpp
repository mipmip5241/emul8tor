#include "Core.h"

Core::Core()
	: _memory(), _gfx(),
	_gp_registers(), _index_register(0), _pc(PC_START),
	_curr_opcode(0),
	_delay_timer(TIMER_START), _sound_timer(TIMER_START),
	_stack(), _sp(0), _keys(), _opcode_handlers()
{
	this->_memory.fill(0);
	this->inst_00E0();
	this->_gp_registers.fill(0);
	this->_keys.fill(false);

	this->load_fontset();

	this->setup_opcode_umap();
}

void Core::emulate_cycle()
{
	constexpr int MERGE_OPCODE = 8;

	//this->curr_opcode = this->memory[this->pc] << MERGE_OPCODE | this->memory[this->pc + 1];

	opcode_handler& handler = this->_opcode_handlers[(this->_curr_opcode & 0xF000)];
	(this->*handler)();

	this->_pc += NEXT_INST;
	this->update_timers();
}

void Core::set_opcode(int val)
{
	this->_curr_opcode = val;
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

	std::copy(chip8_fontset.begin(), chip8_fontset.end(), this->_memory.begin());
}

void Core::update_timers()
{
	if (this->_delay_timer > 0)
	{
		this->_delay_timer--;
	}

	if (this->_sound_timer > 0)
	{
		if (_sound_timer == 1)
		{
			// Make sound
		}
		this->_sound_timer--;
	}
}

void Core::setup_opcode_umap()
{
	this->_opcode_handlers[0x0] = &Core::inst_0_classification;
	this->_opcode_handlers[0x1] = &Core::inst_1NNN;
	this->_opcode_handlers[0x2] = &Core::inst_2NNN;
	this->_opcode_handlers[0x3] = &Core::inst_3XNN;
	this->_opcode_handlers[0x4] = &Core::inst_4XNN;
	this->_opcode_handlers[0x5] = &Core::inst_5XY0;
	this->_opcode_handlers[0x6] = &Core::inst_6XNN;
	this->_opcode_handlers[0x7] = &Core::inst_7XNN;
	this->_opcode_handlers[0x8] = &Core::inst_8_classification;
	this->_opcode_handlers[0x9] = &Core::inst_9XY0;
	this->_opcode_handlers[0xA] = &Core::inst_ANNN;
	this->_opcode_handlers[0xB] = &Core::inst_BNNN;
	this->_opcode_handlers[0xC] = &Core::inst_CXNN;
	this->_opcode_handlers[0xD] = &Core::inst_DXYN;
	this->_opcode_handlers[0xE] = &Core::inst_E_classification;
	this->_opcode_handlers[0xF] = &Core::inst_F_classification;
}

void Core::inst_0_classification()
{
	switch (this->_curr_opcode)
	{
	case 0x00E0:
		this->inst_00E0();
		break;

	case 0x00EE:
		this->inst_00EE();
		break;

	default:
		this->inst_0NNN();
		break;
	}
}

void Core::inst_8_classification()
{
	switch (this->_curr_opcode & 0x000F)
	{
	case 0x0:
		this->inst_8XY0();
		break;

	case 0x1:
		this->inst_8XY1();
		break;

	case 0x2:
		this->inst_8XY2();
		break;

	case 0x3:
		this->inst_8XY3();
		break;

	case 0x4:
		this->inst_8XY4();
		break;

	case 0x5:
		this->inst_8XY5();
		break;

	case 0x6:
		this->inst_8XY6();
		break;

	case 0x7:
		this->inst_8XY7();
		break;

	case 0xE:
		this->inst_8XYE();
		break;

	default:
		break;
	}
}

void Core::inst_E_classification()
{
	switch (this->_curr_opcode & 0x00FF)
	{
	case 0x9E:
		this->inst_EX9E();
		break;

	case 0xA1:
		this->inst_EXA1();
		break;

	default:
		break;
	}
}

void Core::inst_F_classification()
{
	switch (this->_curr_opcode & 0x00FF)
	{
	case 0x07:
		this->inst_FX07();
		break;

	case 0x0A:
		this->inst_FX0A();
		break;
	
	case 0x15:
		this->inst_FX15();
		break;

	case 0x18:
		this->inst_FX18();
		break;

	case 0x1E:
		this->inst_FX1E();
		break;

	case 0x29:
		this->inst_FX29();
		break;

	case 0x33:
		this->inst_FX33();
		break;
	
	case 0x55:
		this->inst_FX55();
		break;

	case 0x65:
		this->inst_FX65();
		break;

	default:
		break;
	}
}


void Core::inst_0NNN()
{
	this->_pc = this->_curr_opcode & 0x0FFF;
}

void Core::inst_00E0()
{
	for (int i = 0; i < GRAPHICS_WIDTH; i++)
	{
		this->_gfx[i].fill(0);
	}
}

void Core::inst_00EE()
{
	this->_pc = this->_stack[this->_sp];
	this->_sp--;
}

void Core::inst_1NNN()
{
	this->inst_0NNN();
}

void Core::inst_2NNN()
{
	this->_stack[this->_sp] = this->_pc;
	this->_sp++;
	this->inst_0NNN();
}

void Core::inst_3XNN()
{
	if ((this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) == ((this->_curr_opcode & 0x00FF) >> EXTRACT_Y_REGISTER))
	{
		this->_pc += NEXT_INST;
	}
}

void Core::inst_4XNN()
{
	if ((this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) != (this->_curr_opcode & 0x00FF))
	{
		this->_pc += NEXT_INST;
	}
}

void Core::inst_5XY0()
{
	if ((this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) == (this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]))
	{
		this->_pc += NEXT_INST;
	}
}

void Core::inst_6XNN()
{
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = (this->_curr_opcode & 0x00FF);
}

void Core::inst_7XNN()
{
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] += (this->_curr_opcode & 0x00FF);
}

void Core::inst_8XY0()
{
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER];
}

void Core::inst_8XY1()
{
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = 
		(this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] | this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]);
}

void Core::inst_8XY2()
{
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = 
		(this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] & this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]);
}

void Core::inst_8XY3()
{
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] =
		(this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] ^ this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]);
}

void Core::inst_8XY4()
{
	if ((this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] + this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]) > 0xFF)
	{
		this->_gp_registers[CARRY_FLAG] = 1;
	}
	else
	{
		this->_gp_registers[CARRY_FLAG] = 0;
	}
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] += this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER];
}

void Core::inst_8XY5()
{
	if ((this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] - this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]) > 0x00)
	{
		this->_gp_registers[CARRY_FLAG] = 1;
	}
	else
	{
		this->_gp_registers[CARRY_FLAG] = 0;
	}
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] -= this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER];
}

void Core::inst_8XY6()
{
	this->_gp_registers[CARRY_FLAG] = (this->_gp_registers[this->_curr_opcode & 0x0F00] & 0x0F);
	this->_gp_registers[this->_curr_opcode & 0x0F00] >>= 1;
}

void Core::inst_8XY7()
{
	if ((this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER] - this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) < 0x00)
	{
		this->_gp_registers[CARRY_FLAG] = 1;
	}
	else
	{
		this->_gp_registers[CARRY_FLAG] = 0;
	}
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]
		= this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER] - this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER];
}

void Core::inst_8XYE()
{
	this->_gp_registers[CARRY_FLAG] = (this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] & 0xF0);
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] <<= 1;
}

void Core::inst_9XY0()
{
	if ((this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]) != (this->_gp_registers[(this->_curr_opcode & 0x00F0) >> EXTRACT_Y_REGISTER]))
	{
		this->_pc += NEXT_INST;
	}
}

void Core::inst_ANNN()
{
	this->_index_register = (this->_curr_opcode & 0x0FFF);
}

void Core::inst_BNNN()
{
	this->_pc = this->_gp_registers[0] + (this->_curr_opcode & 0x0FFF);
}

void Core::inst_CXNN()
{
	constexpr int GET_RANDOM_NUM = 256;
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = ((std::rand() % GET_RANDOM_NUM) & (this->_curr_opcode & 0x00FF));
}

void Core::inst_DXYN()
{
}


void Core::inst_EX9E()
{
	if (this->_keys[this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]] != 0)
	{
		this->_pc += NEXT_INST;
	}
}

void Core::inst_EXA1()
{
	if (this->_keys[this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER]] == 0)
	{
		this->_pc += NEXT_INST;
	}
}

void Core::inst_FX07()
{
	this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = this->_delay_timer;
}

void Core::inst_FX0A()
{
	for (int i = 0; i < KEY_SIZE; i++)
	{
		if (this->_keys[i])
		{
			this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] = i;
			break;
		}
	}
}


void Core::inst_FX15()
{
	this->_delay_timer = this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER];
}

void Core::inst_FX18()
{
	this->_sound_timer = this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER];
}

void Core::inst_FX1E()
{
	this->_index_register += this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER];
}

void Core::inst_FX29()
{
	constexpr int CONVERT_TO_FONT = 5;
	this->_index_register = this->_gp_registers[(this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER] * CONVERT_TO_FONT;
}

void Core::inst_FX33()
{
}


void Core::inst_FX55()
{
	for (int offset = 0; offset < ((this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER); offset++)
	{
		this->_memory[this->_index_register + offset] = this->_gp_registers[offset];
	}
}

void Core::inst_FX65()
{
	for (int offset = 0; offset < ((this->_curr_opcode & 0x0F00) >> EXTRACT_X_REGISTER); offset++)
	{
		this->_gp_registers[offset] = this->_memory[this->_index_register + offset];
	}
}




