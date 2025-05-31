#include "entity.hpp"
#include "globals.h"
#include "offsets.h"
#include "maths.h"

void update_local_player(Entity& ent)
{
	Globals::mem.ReadStruct<Entity>(offsets::local_player, ent);
	ent.dead = ent.health < 0;
	ent.address = offsets::get_local_player();
}

void populate_entity_array(std::array<uintptr_t, 31> ents_ptr, std::array<Entity, 31>& entities)
{
	const size_t loaded_entities{ Globals::current_entities };

	for (size_t i{}; i < loaded_entities; ++i)
	{
		Globals::mem.ReadStruct<Entity>(ents_ptr[i], entities[i]);
		entities[i].vf_table = Globals::mem.Read<uintptr_t>(entities[i].vf_table);
		entities[i].dead = entities[i].health < 0;
		entities[i].address = ents_ptr[i];
	}
}

Entity& get_closest_entity(bool ignore_teammates, std::array<Entity, 31>& ents, Entity& myself)
{
	size_t loaded_entities{ Globals::current_entities };
	Maths::bubble_sort(ents, myself);
	for (size_t i{}; i < loaded_entities; ++i)
	{
		if (ents[i].dead) continue;
		if (ignore_teammates && !(ents[i].team == myself.team)) return ents[i];
	}
}