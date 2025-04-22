#include <math.h>
#include "maths.h"

double Maths::distance_from_me(Entity& enemy, const Entity& me)
{
	Vector3 p{};
	p.x = (enemy.m_coords.x - me.m_coords.x) * (enemy.m_coords.x - me.m_coords.x);
	p.y = (enemy.m_coords.y - me.m_coords.y) * (enemy.m_coords.y - me.m_coords.y);
	p.z = (enemy.m_coords.z - me.m_coords.z) * (enemy.m_coords.z - me.m_coords.z);

	return sqrt(p.x + p.y + p.z);
}
