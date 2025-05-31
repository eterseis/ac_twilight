#pragma once
#include "entity.hpp"
#include "vector.h"
#include <array>

namespace Maths
{
	float distance_from(const vec3& a, const vec3& b);
	void bubble_sort(std::array<Entity, 31>& arr, Entity& myself);
	bool world_to_screen(const vec3& pos, vec2& screen, const std::array<float, 16>& matrix, int window_width, int window_height);
}