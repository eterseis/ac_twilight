#include "aimbot.h"
#include "maths.h"

void Aimbot::closest_target(bool ignore_teammates, Entity* target, Entity* myself)
{
	if (target->dead) return;
	if (ignore_teammates && target->team == myself->team) return;


	constexpr float pi{ 3.14159265358979323846f };

	float abspos_x = target->head.x - myself->head.x;
	float abspos_y = target->head.y - myself->head.y;
	float abspos_z = target->head.z - myself->head.z;

	float azimuth_xy = atan2f(abspos_y, abspos_x);
	float distance{ Maths::distance_from(target->feet, myself->feet) };
	float azimuth_z = atan2f(abspos_z, distance);

	float yaw = azimuth_xy * (180.0f / pi);
	yaw += 90.0f;

	float pitch = azimuth_z * (180.0f / pi);

	vec2 yaw_pitch{ yaw, pitch };
	uintptr_t myself_address{ offsets::get_local_player() };
	Globals::mem.WriteVector<Vector2>(myself_address + offsets::yaw, yaw_pitch);
}