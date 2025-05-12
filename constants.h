#pragma once
#include "memory.h"
#include "offsets.h"

inline const Memory mem{ "ac_client.exe" };
inline const uintptr_t moduleBase{ mem.GetModuleBaseAddress("ac_client.exe") };
inline constexpr int entity_name_length{ 16 };