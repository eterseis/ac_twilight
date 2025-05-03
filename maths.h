#pragma once
#include "entity.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include <array>

namespace Maths
{
	float distance_from_me(Entity& enemy, const Entity& me);
	void bubble_sort(std::array<Entity, 32>& arr, const size_t& current_entities);
	bool world_to_screen(Vector3& pos, Vector2& screen, const std::array<float, 16> matrix, int window_width, int window_height);
}