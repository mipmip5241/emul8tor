
#include "../include/Core.h"
int main()
{
	Core chip;

	chip.load_game("../Pong.ch8");


	while(true)
	{
		chip.emulate_cycle();

		chip.draw();

		chip.update_keys();
	}
    return 0;
}