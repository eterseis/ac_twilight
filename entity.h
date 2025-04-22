#pragma once
#include <cstdint>
#include "vector3.h"
#include "constants.h"
#include <array>

struct Entity
{
	uintptr_t m_address{};
	char m_name[entity_name_length]{};
	int m_health{};
	int m_team{};
	Vector3 m_coords{};
	double m_distance_from_local_player{};

	const bool isAlive() const { return m_health > 0; }
};

void update_entity_info(Entity& e, Entity& myself);
void update_local_player(Entity& myself);
void populate_entity_array(std::array<Entity, 32>& entities, const Entity& myself);