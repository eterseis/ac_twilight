#include "offsets.h"

uintptr_t offsets::get_local_player()
{
	uintptr_t local_player{ mem.Read<uintptr_t>(moduleBase + offsets::local_player_addr) };
	return local_player;
}

uintptr_t offsets::get_entity_list()
{
	uintptr_t entity_list{ mem.Read<uintptr_t>(moduleBase + offsets::entity_list_addr) };
	return entity_list;
}

size_t offsets::get_max_entities()
{
	size_t max_entities{ mem.Read <size_t>(moduleBase + offsets::max_entities_addr) };

	return (max_entities > 0) ? max_entities : 1;
}