#pragma once
#include "memory.h"
#include "offsets.h"
#include "globals.h"

class Miscellaneous
{
public:
	void unlimited_health(uintptr_t& address);
	void unlimited_ammo(uintptr_t& address);
	void rapidfire(uintptr_t& address, int value);
};