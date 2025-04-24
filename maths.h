#pragma once
#include "entity.h"
#include "vector3.h"

namespace Maths
{
	double distance_from_me(Entity& enemy, const Entity& me);
	void bubble_sort(std::array<Entity, 32>& arr);
}