
#include "../include/Core.h"
#include <ctime>
#include <chrono>
#include <thread>

int main()
{
	Core chip;

	chip.load_game("../roms/PONG");

	bool run = true;

	while(run)
	{
		run = chip.emulate_cycle();

		chip.draw();

		chip.update_keys();

		std::this_thread::sleep_for(std::chrono::microseconds(2000)); // delay
	}
    return 0;
}