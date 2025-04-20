#include <iostream>
#include "memory.h"
#include "constants.h"
#include "offsets.h"
#include "miscellaneous.h"

int main()
{
	std::cout << "Key Of The Twilight\n";
	Miscellaneous misc{};

	while (!(GetAsyncKeyState(VK_ESCAPE) & 1))
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			misc.m_health = !misc.m_health;
		}
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			misc.m_ammo = !misc.m_ammo;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			misc.m_rapidfire = !misc.m_rapidfire;
		}

		if (misc.m_health)
		{
			misc.unlimited_health();
		}
		if (misc.m_ammo)
		{
			misc.unlimited_ammo();
		}
		if (misc.m_rapidfire)
		{
			misc.rapidfire();
		}
	}


	return 0;
}