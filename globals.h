#pragma once

#include <array>
#include "entity.h"
#include "memory.h"

namespace Globals
{
	inline const Memory mem{ "ac_client.exe" };
	inline const uintptr_t moduleBase{ mem.GetModuleBaseAddress("ac_client.exe") };
	inline Entity myself;
	inline size_t current_entities;
	inline std::array<Entity, 32> entities;
}
