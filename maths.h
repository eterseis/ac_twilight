#pragma once
#include "entity.h"
#include "vector.h"
#include <array>

namespace Maths
{
	float distance_from_me(Entity& enemy, const Entity& me);
	void bubble_sort(std::array<Entity, 32>& arr, const size_t& current_entities);
	bool world_to_screen(const Vector3& pos, Vector2& screen, const std::array<float, 16> matrix, int window_width, int window_height);
}