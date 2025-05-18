#include "esp.h"
#include <iostream>

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

		Vector2 feet_coords;

		if (!Maths::world_to_screen(entities[i].m_coords, feet_coords, matrix, display_w, display_h))
			continue;

		glLineWidth(1.5f);
		glBegin(GL_LINES);
		if (myself.m_team == entities[i].m_team)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
		}
		glVertex2f(origin_bottom.x, origin_bottom.y);
		glVertex2f(feet_coords.x, feet_coords.y);
		glEnd();
	}
}

void ESP::draw_boxes(size_t current_entities, std::array<Entity, 32> entities, Entity myself, int display_w, int display_h)
{
	for (size_t i{}; i < current_entities; ++i)
	{
		if (!valid_entity(entities[i]))
			continue;

		if (!entities[i].isAlive())
			continue;

		Vector2 feet_coords;
		Vector2 head_coords;

		if (!Maths::world_to_screen(entities[i].m_coords, feet_coords, matrix, display_w, display_h))
			continue;
		if (!Maths::world_to_screen(entities[i].m_head_coords, head_coords, matrix, display_w, display_h))
			continue;

		float h = head_coords.y - feet_coords.y;
		float w = h / 5.0f;

		glLineWidth(2.0f);
		glBegin(GL_LINES);

		if (myself.m_team == entities[i].m_team)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else glColor4f(1.0f, 0.0f, 1.0f, 1.0f);

		glVertex2f(feet_coords.x - w, feet_coords.y);
		glVertex2f(feet_coords.x + w, feet_coords.y);

		glVertex2f(head_coords.x - w, head_coords.y);
		glVertex2f(head_coords.x + w, head_coords.y);

		glVertex2f(head_coords.x - w, head_coords.y);
		glVertex2f(feet_coords.x - w, feet_coords.y);

		glVertex2f(head_coords.x + w, head_coords.y);
		glVertex2f(feet_coords.x + w, feet_coords.y);

		glEnd();
	}
}

void ESP::draw_health(size_t current_entities, std::array<Entity, 32> entities, int display_w, int display_h)
{
	for (size_t i{}; i < current_entities; ++i)
	{
		if (!valid_entity(entities[i]))
			continue;

		if (!entities[i].isAlive())
			continue;

		Vector2 feet_coords;
		Vector2 head_coords;

		if (!Maths::world_to_screen(entities[i].m_coords, feet_coords, matrix, display_w, display_h))
			continue;
		if (!Maths::world_to_screen(entities[i].m_head_coords, head_coords, matrix, display_w, display_h))
			continue;

		float height = head_coords.y - feet_coords.y;
		float width = height / 4.0f;

		float t{ 1.0f - ((entities[i].m_health / 100.0f)) };
		float x = head_coords.x + t * (feet_coords.x - head_coords.x);
		float y = head_coords.y + t * (feet_coords.y - head_coords.y);

		glLineWidth(2.0f);
		glBegin(GL_LINES);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex2f(head_coords.x - width, head_coords.y);
		glVertex2f(feet_coords.x - width, feet_coords.y);

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glVertex2f(x - width, y);
		glVertex2f(feet_coords.x - width, feet_coords.y);
		glEnd();
	}
}