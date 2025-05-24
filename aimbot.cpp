#include "aimbot.h"

void Aimbot::closest_target(bool ignore_teammates, Entity& target, Entity& local_player)
{
	if (ignore_teammates && target.m_team == local_player.m_team) return;
	if (!target.isAlive())
		return;

	constexpr float pi{ 3.14159265358979323846f };

	float abspos_x = target.m_head_coords.x - local_player.m_head_coords.x;
	float abspos_y = target.m_head_coords.y - local_player.m_head_coords.y;
	float abspos_z = target.m_head_coords.z - local_player.m_head_coords.z;

	float azimuth_xy = atan2f(abspos_y, abspos_x);
	float azimuth_z = atan2f(abspos_z, target.m_distance_from_local_player);

	float yaw = azimuth_xy * (180.0f / pi);
	yaw += 90.0f;

	float pitch = azimuth_z * (180.0f / pi);

	Globals::mem.Write<float>(local_player.m_address + offsets::yaw, yaw);
	Globals::mem.Write<float>(local_player.m_address + offsets::pitch, pitch);
}