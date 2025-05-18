#include "entity.h"
#include "constants.h"
#include "offsets.h"
#include "maths.h"
#include <array>

void update_entity_info(Entity& e, const Entity& myself)
{
	e.vf_table = mem.Read<uintptr_t>(e.m_address);

	mem.ReadString(e.m_address + offsets::name, e.m_name, entity_name_length);

	e.m_team = mem.Read<int>(e.m_address + offsets::team);

	e.m_coords.x = mem.Read<float>(e.m_address + offsets::x_feet_coord);
	e.m_coords.y = mem.Read<float>(e.m_address + offsets::y_feet_coord);
	e.m_coords.z = mem.Read<float>(e.m_address + offsets::z_feet_coord);

	e.m_head_coords.x = mem.Read<float>(e.m_address + offsets::x_head_coord);
	e.m_head_coords.y = mem.Read<float>(e.m_address + offsets::y_head_coord);
	e.m_head_coords.z = mem.Read<float>(e.m_address + offsets::z_head_coord);

	e.m_distance_from_local_player = Maths::distance_from_me(e, myself);
}

void update_local_player(Entity& myself)
{
	myself.m_address = offsets::get_local_player();
	myself.vf_table = mem.Read<uintptr_t>(myself.m_address);

	myself.m_coords.x = mem.Read<float>(myself.m_address + offsets::x_feet_coord);
	myself.m_coords.y = mem.Read<float>(myself.m_address + offsets::y_feet_coord);
	myself.m_coords.z = mem.Read<float>(myself.m_address + offsets::z_feet_coord);

	myself.m_head_coords.x = mem.Read<float>(myself.m_address + offsets::x_head_coord);
	myself.m_head_coords.y = mem.Read<float>(myself.m_address + offsets::y_head_coord);
	myself.m_head_coords.z = mem.Read<float>(myself.m_address + offsets::z_head_coord);

	myself.m_team = mem.Read<int>(myself.m_address + offsets::team);

}

void populate_entity_array(std::array<Entity, 32>& entities, const Entity& myself, const size_t& current_entities)
{
	uintptr_t offset{};
	for (size_t i{}; i < current_entities; ++i)
	{
		entities[i].m_address = offsets::get_entity_list() + offset;
		entities[i].m_address = mem.Read<uintptr_t>(entities[i].m_address);

		entities[i].m_health = mem.Read<int>(entities[i].m_address + offsets::health);
		if (!entities[i].isAlive())
		{
			offset += 0x4;
			continue;
		}
		update_entity_info(entities[i], myself);
		offset += 0x4;
	}
}

Entity& get_closest_entity(std::array<Entity, 32>& entities, const size_t& current_entities)
{
	for (size_t i{}; i < current_entities; ++i)
	{
		if (!entities[i].isAlive())
			continue;

		return entities[i];
	}
	return entities[0];
}