#include <cmath>
#include "maths.h"
#include "offsets.h"


float Maths::distance_from(const vec3& a, const vec3& b)
{
	vec3 p;
	p.x = (a.x - b.x) * (a.x - b.x);
	p.y = (a.y - b.y) * (a.y - b.y);
	p.z = (a.z - b.z) * (a.z - b.z);

	return sqrtf(p.x + p.y + p.z);
}

void Maths::bubble_sort(std::array<Entity, 31>& ents, Entity& myself)
{
	size_t loaded_ents{ Globals::current_entities };
	for (size_t i{}; i < loaded_ents - 1; i++)
	{
		bool flag{};
		for (size_t j{}; j < loaded_ents - i - 1; ++j)
		{
			float ent_distance{ Maths::distance_from(myself.feet, ents[j].feet) };
			float ent2_distance{ Maths::distance_from(myself.feet, ents[j + 1].feet) };
			if (ent_distance > ent2_distance)
			{
				Entity backup{ ents[j] };
				ents[j] = ents[j + 1];
				ents[j + 1] = backup;

				flag = true;
			}
		}

		if (!flag)
			break;
	}
}

bool Maths::world_to_screen(const vec3& pos, vec2& screen, const std::array<float, 16>& matrix, int window_width, int window_height)
{
	vec4 convert;

	convert.x = (pos.x * matrix[0]) + (pos.y * matrix[4]) + (pos.z * matrix[8]) + matrix[12];
	convert.y = (pos.x * matrix[1]) + (pos.y * matrix[5]) + (pos.z * matrix[9]) + matrix[13];
	convert.z = (pos.x * matrix[2]) + (pos.y * matrix[6]) + (pos.z * matrix[10]) + matrix[14];
	convert.w = (pos.x * matrix[3]) + (pos.y * matrix[7]) + (pos.z * matrix[11]) + matrix[15];

	if (convert.w < 0.1f)
		return false;

	vec3 NDC;
	NDC.x = convert.x / convert.w;
	NDC.y = convert.y / convert.w;
	NDC.z = convert.z / convert.w;

	screen.x = (window_width / 2 * NDC.x) + (NDC.x + window_width / 2);
	screen.y = (window_height / 2 * NDC.y) + (NDC.y + window_height / 2);

	screen.x /= window_width;
	screen.x *= 2.0f;
	screen.x -= 1.0f;

	screen.y /= window_height;
	screen.y *= 2.0f;
	screen.y -= 1.0f;

	return true;
}