#include "offsets.h"

uintptr_t offsets::get_local_player()
{
	uintptr_t local_player{ Globals::mem.Read<uintptr_t>(Globals::moduleBase + offsets::local_player_addr) };
	return local_player;
}

uintptr_t offsets::get_entity_list()
{
	uintptr_t entity_list{ Globals::mem.Read<uintptr_t>(Globals::moduleBase + offsets::entity_list_addr) };
	return entity_list;
}

size_t offsets::get_max_entities()
{
	size_t max_entities{ Globals::mem.Read <size_t>(Globals::moduleBase + offsets::max_entities_addr) };

	return (max_entities > 0) ? max_entities : 1;
}

std::array<float, 16> offsets::get_view_matrix()
{
	uintptr_t address{ Globals::moduleBase + offsets::view_matrix_addr };
	address = address - 0x6C + 0x4 * 0x10;

	return Globals::mem.Read<std::array<float, 16>>(address);
}