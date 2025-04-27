#include <cmath>
#include "maths.h"
#include "offsets.h"


float Maths::distance_from_me(Entity& enemy, const Entity& me)
{
	Vector3 p;
	p.x = (enemy.m_coords.x - me.m_coords.x) * (enemy.m_coords.x - me.m_coords.x);
	p.y = (enemy.m_coords.y - me.m_coords.y) * (enemy.m_coords.y - me.m_coords.y);
	p.z = (enemy.m_coords.z - me.m_coords.z) * (enemy.m_coords.z - me.m_coords.z);

	return sqrtf(p.x + p.y + p.z);
}

void Maths::bubble_sort(std::array<Entity, 32>& arr, const size_t& current_entities)
{
	for (size_t i{}; i < current_entities - 1; i++)
	{
		bool flag{};
		for (size_t j{}; j < current_entities - i - 1; ++j)
		{
			if (arr[j].m_distance_from_local_player > arr[j + 1].m_distance_from_local_player)
			{
				Entity backup{ arr[j] };
				arr[j] = arr[j + 1];
				arr[j + 1] = backup;

				flag = true;
			}
		}

		if (!flag)
			break;
	}
}
