#pragma once
#include "memory.h"
#include "offsets.h"
#include "constants.h"

class Miscellaneous
{
public:
	void unlimited_health(uintptr_t address);
	void unlimited_ammo(uintptr_t address);
	void rapidfire(uintptr_t address);
public:
	bool m_health{};
	bool m_ammo{};
	bool m_rapidfire{};
};