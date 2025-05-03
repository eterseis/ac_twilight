#pragma once
#include "memory.h"
#include "constants.h"

namespace offsets
{
	inline constexpr int ammo{ 0x140 }; // local player only
	inline constexpr int health{ 0xEC };
	inline constexpr int isAlive{ 0x104 }; // local player only
	inline constexpr int name{ 0x205 };
	inline constexpr int firerate{ 0x164 };
	inline constexpr int team{ 0x30C };

	inline constexpr int x_head_coord{ 0x4 };
	inline constexpr int y_head_coord{ 0x8 };
	inline constexpr int z_head_coord{ 0xC };

	inline constexpr int x_feet_coord{ 0x28 };
	inline constexpr int y_feet_coord{ 0x2C };
	inline constexpr int z_feet_coord{ 0x30 };

	inline constexpr int yaw{ 0x34 };
	inline constexpr int pitch{ 0x38 };

	inline constexpr uintptr_t view_matrix{ 0x17DFFC };

	inline constexpr uintptr_t local_player_addr{ 0x17E0A8 };
	inline constexpr uintptr_t entity_list_addr{ 0x191FCC };
	inline constexpr uintptr_t max_entities_addr{ 0x18AC0C };

	uintptr_t get_local_player();
	uintptr_t get_entity_list();
	size_t get_max_entities();
}