#pragma once
#include "memory.h"
#include "offsets.h"
#include "constants.h"

const uintptr_t local_player{ offsets::get_local_player() };

class Miscellaneous
{
public:
	void unlimited_health();
	void unlimited_ammo();
	void rapidfire();
public:
	bool m_health{};
	bool m_ammo{};
	bool m_rapidfire{};
};