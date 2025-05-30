#pragma once
#include "vector.h"
#include <cstdint>
#include <cstddef>
#include <array>

inline constexpr int entity_name_length{ 16 };

struct Entity
{
	uintptr_t vf_table;
	vec3 head;

	char padding[0x28 - 0x10];
	vec3 feet;

	float yaw;
	float pitch;

	char pading2[0xEC - 0x3C];
	int health;

	char padding3[0x205 - 0xF0];
	char name[entity_name_length];

	char padding4[0x30C - 0x21B];
	std::byte team;

	bool dead;
};

void update_local_player(Entity& ent);
void populate_entity_array(std::array<Entity, 31>& entities);
Entity& get_closest_entity(bool ignore_teammates, std::array<Entity, 31>& ents, Entity& myself);