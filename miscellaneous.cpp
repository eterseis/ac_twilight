#include "miscellaneous.h"

void Miscellaneous::unlimited_health()
{
	mem.Write<int>(local_player + offsets::health, 1337);
}

void Miscellaneous::unlimited_ammo()
{
	mem.Write<int>(local_player + offsets::ammo, 100);
}

void Miscellaneous::rapidfire()
{
	mem.Write<int>(local_player + offsets::firerate, 40);
}