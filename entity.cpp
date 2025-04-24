#include "entity.h"
#include "constants.h"
#include "offsets.h"
#include "maths.h"
#include <array>

void update_entity_info(Entity& e, const Entity& myself)
{
	mem.ReadString(e.m_address + offsets::name, e.m_name, entity_name_length);

	e.m_health = mem.Read<int>(e.m_address + offsets::health);
	e.m_team = mem.Read<int>(e.m_address + offsets::team);

	e.m_coords.x = mem.Read<float>(e.m_address + offsets::x_feet_coord);
	e.m_coords.y = mem.Read<float>(e.m_address + offsets::y_feet_coord);
	e.m_coords.z = mem.Read<float>(e.m_address + offsets::z_feet_coord);

	//head coordinates after


	e.m_distance_from_local_player = Maths::distance_from_me(e, myself);
}

void update_local_player(Entity& myself)
{
	myself.m_address = offsets::get_local_player();

	mem.ReadString(myself.m_address + offsets::name, myself.m_name, entity_name_length);

	myself.m_coords.x = mem.Read<float>(myself.m_address + offsets::x_feet_coord);
	myself.m_coords.y = mem.Read<float>(myself.m_address + offsets::y_feet_coord);
	myself.m_coords.z = mem.Read<float>(myself.m_address + offsets::z_feet_coord);
}

void populate_entity_array(std::array<Entity, 32>& entities, const Entity& myself)
{
	const size_t current_entities{ offsets::get_max_entities() - 1 };
	uintptr_t offset{};
	for (size_t i{}; i < current_entities; ++i)
	{
		entities[i].m_address = offsets::get_entity_list() + offset;
		entities[i].m_address = mem.Read<uintptr_t>(entities[i].m_address);
		update_entity_info(entities[i], myself);
		offset += 0x4;
	}
}