#pragma once
#include <cstdint>
#include "vector.h"
#include "constants.h"
#include <array>

class Entity
{
public:
	constexpr bool isAlive() const { return m_health > 0; }

	uintptr_t vf_table;
	uintptr_t m_address;
	char m_name[entity_name_length];
	int m_health;
	int m_team;
	Vector3 m_coords;
	Vector3 m_head_coords;
	float m_distance_from_local_player;
};

void update_entity_info(Entity& e, Entity& myself);
void update_local_player(Entity& myself);
void populate_entity_array(std::array<Entity, 32>& entities, const Entity& myself, const size_t& current_entities);
Entity& get_closest_entity(std::array<Entity, 32>& entities, const size_t& current_entities);