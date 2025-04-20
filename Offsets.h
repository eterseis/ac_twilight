#pragma once
#include "memory.h"
#include "constants.h"

namespace offsets
{
	inline constexpr int ammo{ 0x140 };
	inline constexpr int health{ 0xEC };
	inline constexpr int isDead{ 0x104 };
	inline constexpr int name{ 0x205 };
	inline constexpr int firerate{ 0x164 };
	inline constexpr int team{ 0x30C };

	inline constexpr uintptr_t local_player_addr{ 0x17E0A8 };
	inline constexpr uintptr_t entity_list_addr{ 0x191FCC };
	inline constexpr uintptr_t max_entities_addr{ 0x18AC0C };

	uintptr_t get_local_player();
	uintptr_t get_entity_list();
	int get_max_entities();
}