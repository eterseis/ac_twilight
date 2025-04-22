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
std::array<Entity, 32> entities{};

void handle_input(Miscellaneous& misc)
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

void print_entity(const Entity& ent)
{
	std::cout << "address: " << ent.m_address << "\n";
	std::cout << "name: " << ent.m_name << "\n";
	std::cout << "health: " << ent.m_health << "\n";
	std::cout << "team: " << ent.m_team << "\n";
	std::cout << "isAlive: " << ent.isAlive() << "\n";

	std::cout << "xyz: " << "("
		<< ent.m_coords.x << ", " << ent.m_coords.y << ", " << ent.m_coords.z << ")\n";

	std::cout << "distance from local player: " << ent.m_distance_from_local_player;

	system("cls");
}

void debug_mode()
{
	size_t current_entities{ offsets::get_max_entities() };
	for (size_t i{}; i < current_entities; ++i)
	{
		print_entity(entities[i]);
	}
}

int main()
{
	std::cout << "Key Of The Twilight\n";
	Miscellaneous misc{};


	while (!(GetAsyncKeyState(VK_ESCAPE) & 1))
	{
		handle_input(misc);

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
	}


	return 0;
}