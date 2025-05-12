#include "esp.h"

bool ESP::valid_entity(Entity& ent)
{
	if (ent.m_address)
	{
		if (ent.vf_table == offsets::vf_table_bot || ent.vf_table == offsets::vf_table_player)
		{
			return true;
		}
	}
	return false;
}

void ESP::draw_lines(size_t current_entities, std::array<Entity, 32> entities, Entity myself, int display_w, int display_h)
{
	for (size_t i{}; i < current_entities; ++i)
	{
		if (!valid_entity(entities[i]))
			continue;

		if (!entities[i].isAlive())
			continue;

		Vector2 screen_coords;

		if (!Maths::world_to_screen(entities[i].m_coords, screen_coords, matrix, display_w, display_h))
			continue;

		glBegin(GL_LINES);
		glVertex2f(origin_bottom.x, origin_bottom.y);
		glVertex2f(screen_coords.x, screen_coords.y);
		glEnd();
	}
}

void ESP::draw_boxes(size_t current_entities, std::array<Entity, 32> entities, Entity myself)
{

}