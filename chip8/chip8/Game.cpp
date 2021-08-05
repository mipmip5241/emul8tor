#include "Core.h"
#include <iostream>




int main()
{
	std::srand(time(NULL));
	Core chip;
	chip.set_opcode(0x0123);
	chip.emulate_cycle();
	return 0;
}


