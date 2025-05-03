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

bool Maths::world_to_screen(Vector3& pos, Vector2& screen, const std::array<float, 16> matrix, int window_width, int window_height)
{
	Vector4 convert;

	convert.x = (pos.x * matrix[0]) + (pos.y * matrix[4]) + (pos.z * matrix[8]) + matrix[12];
	convert.y = (pos.x * matrix[1]) + (pos.y * matrix[5]) + (pos.z * matrix[9]) + matrix[13];
	convert.z = (pos.x * matrix[2]) + (pos.y * matrix[6]) + (pos.z * matrix[10]) + matrix[14];
	convert.w = (pos.x * matrix[3]) + (pos.y * matrix[7]) + (pos.z * matrix[11]) + matrix[15];

	if (convert.w < 0.1f)
		return false;

	Vector3 NDC;
	NDC.x = convert.x / convert.w;
	NDC.y = convert.y / convert.w;
	NDC.z = convert.z / convert.w;

	screen.x = (window_width / 2 * NDC.x) + (NDC.x + window_width / 2);
	screen.y = -(window_height / 2 * NDC.y) + (NDC.y + window_height / 2);

	return true;
}