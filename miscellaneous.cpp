#include "miscellaneous.h"

void Miscellaneous::unlimited_health(uintptr_t& address)
{
	Globals::mem.Write<int>(address + offsets::health, 1337);
}

void Miscellaneous::unlimited_ammo(uintptr_t& address)
{
	Globals::mem.Write<int>(address + offsets::ammo, 100);
}

void Miscellaneous::rapidfire(uintptr_t& address, int value)
{
	Globals::mem.Write<int>(address + offsets::firerate, value);
}