#pragma once

#include "memory.h"
//#include "entity.hpp"
//#include <array>

namespace Globals
{
	inline const Memory mem{ "ac_client.exe" };
	inline const uintptr_t moduleBase{ mem.GetModuleBaseAddress("ac_client.exe") };
	//inline Entity myself;
	inline size_t current_entities;
	//inline std::array<Entity, 31> entities;
}
