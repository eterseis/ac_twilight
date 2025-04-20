#pragma once
#include "memory.h"
#include "offsets.h"

inline const Memory mem{ L"ac_client.exe" };
inline const uintptr_t moduleBase{ mem.GetModuleBaseAddress(L"ac_client.exe") };
