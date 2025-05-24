#include "entity.h"
#include "globals.h"
#include "offsets.h"
#include "maths.h"
#include <array>

void update_entity_info(Entity& e)
{
	e.vf_table = Globals::mem.Read<uintptr_t>(e.m_address);

	Globals::mem.ReadString(e.m_address + offsets::name, e.m_name, entity_name_length);

	e.m_team = Globals::mem.Read<int>(e.m_address + offsets::team);

	e.m_coords.x = Globals::mem.Read<float>(e.m_address + offsets::x_feet_coord);
	e.m_coords.y = Globals::mem.Read<float>(e.m_address + offsets::y_feet_coord);
	e.m_coords.z = Globals::mem.Read<float>(e.m_address + offsets::z_feet_coord);

	e.m_head_coords.x = Globals::mem.Read<float>(e.m_address + offsets::x_head_coord);
	e.m_head_coords.y = Globals::mem.Read<float>(e.m_address + offsets::y_head_coord);
	e.m_head_coords.z = Globals::mem.Read<float>(e.m_address + offsets::z_head_coord);

	e.m_distance_from_local_player = Maths::distance_from_me(e, Globals::myself);
}

void update_local_player()
{
	Globals::myself.m_address = offsets::get_local_player();
	Globals::myself.vf_table = Globals::mem.Read<uintptr_t>(Globals::myself.m_address);

	Globals::myself.m_coords.x = Globals::mem.Read<float>(Globals::myself.m_address + offsets::x_feet_coord);
	Globals::myself.m_coords.y = Globals::mem.Read<float>(Globals::myself.m_address + offsets::y_feet_coord);
	Globals::myself.m_coords.z = Globals::mem.Read<float>(Globals::myself.m_address + offsets::z_feet_coord);

	Globals::myself.m_head_coords.x = Globals::mem.Read<float>(Globals::myself.m_address + offsets::x_head_coord);
	Globals::myself.m_head_coords.y = Globals::mem.Read<float>(Globals::myself.m_address + offsets::y_head_coord);
	Globals::myself.m_head_coords.z = Globals::mem.Read<float>(Globals::myself.m_address + offsets::z_head_coord);

	Globals::myself.m_team = Globals::mem.Read<int>(Globals::myself.m_address + offsets::team);

}

void populate_entity_array(std::array<Entity, 32>& entities, const size_t& current_entities)
{
	uintptr_t offset{};
	for (size_t i{}; i < current_entities; ++i)
	{
		entities[i].m_address = offsets::get_entity_list() + offset;
		entities[i].m_address = Globals::mem.Read<uintptr_t>(entities[i].m_address);

		entities[i].m_health = Globals::mem.Read<int>(entities[i].m_address + offsets::health);
		if (!entities[i].isAlive())
		{
			offset += 0x4;
			continue;
		}
		update_entity_info(entities[i]);
		offset += 0x4;
	}
}

Entity& get_closest_entity(bool ignore_teammates, std::array<Entity, 32>& entities, const size_t& current_entities)
{
	for (size_t i{}; i < current_entities; ++i)
	{
		if (ignore_teammates && entities[i].m_team == Globals::myself.m_team) continue;
		if (!entities[i].isAlive())
			continue;

		return entities[i];
	}
	return entities[0];
}