#include <iostream>
#include "memory.h"
#include "constants.h"
#include "offsets.h"
#include "miscellaneous.h"
#include "entity.h"
#include "maths.h"
#include "vector3.h"
#include <array>


bool enable_debug{};
Miscellaneous misc{};
std::array<Entity, 32> entities{};

void handle_input()
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
	if (GetAsyncKeyState(VK_F9) & 1)
	{
		enable_debug = !enable_debug;
	}
}

void debug_mode()
{
	const size_t current_entities{ offsets::get_max_entities() - 1 };
	for (size_t i{}; i < current_entities; ++i)
	{
		std::cout << std::hex;
		std::cout << "address: 0x" << entities[i].m_address << "\n";
		std::cout << "name: " << entities[i].m_name << "\n";
		std::cout << "health: " << entities[i].m_health << "\n";
		std::cout << "is alive: " << entities[i].isAlive() << "\n";
		std::cout << "team: " << entities[i].m_team << "\n";

		std::cout << "coords: (" << entities[i].m_coords.x << ", "
			<< entities[i].m_coords.y << ", "
			<< entities[i].m_coords.z << ")\n";

		std::cout << "distance from local player: " << entities[i].m_distance_from_local_player << "\n";
		std::cout << "---------------------------------------\n";
	}
	Sleep(100);
	system("cls");

}

int main()
{
	std::cout << "Key Of The Twilight\n";

	while (true/*!(GetAsyncKeyState(VK_ESCAPE) & 1)*/)
	{
		handle_input();

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
		if (enable_debug)
		{
			debug_mode();
		}

		Entity myself{};
		update_local_player(myself);

		populate_entity_array(entities, myself);
		Maths::bubble_sort(entities);
	}


	return 0;
}