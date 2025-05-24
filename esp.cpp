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

void ESP::draw_rect(bool outlined, float x, float x2, float y, float y2, float w /*width*/, Vector3 color)
{
	if (outlined)
	{
		glLineWidth(2.0f);
		glColor3f(0.0f, 0.0f, 0.f);
		glBegin(GL_LINES);
		glVertex2f(x - w, y);
		glVertex2f(x + w, y);

		glVertex2f(x2 - w, y2);
		glVertex2f(x2 + w, y2);

		glVertex2f(x - w, y);
		glVertex2f(x2 - w, y2);

		glVertex2f(x + w, y);
		glVertex2f(x2 + w, y2);
		glEnd();
	}
	glLineWidth(1.0f);
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINES);
	glVertex2f(x - w, y);
	glVertex2f(x + w, y);

	glVertex2f(x2 - w, y2);
	glVertex2f(x2 + w, y2);

	glVertex2f(x - w, y);
	glVertex2f(x2 - w, y2);

	glVertex2f(x + w, y);
	glVertex2f(x2 + w, y2);
	glEnd();
}

void ESP::draw_filled_rect(bool outlined, float x, float x2, float y, float y2, float w, Vector3 color)
{
	if (outlined)
	{
		glLineWidth(2.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(x - w, y);
		glVertex2f(x + w, y);

		glVertex2f(x2 - w, y2);
		glVertex2f(x2 + w, y2);

		glVertex2f(x - w, y);
		glVertex2f(x2 - w, y2);

		glVertex2f(x + w, y);
		glVertex2f(x2 + w, y2);
		glEnd();
	}
	glLineWidth(1.0f);
	glColor4f(color.x, color.y, color.z, 0.4f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x2 - w, y2);
	glVertex2f(x2 + w, y2);
	glVertex2f(x + w, y);

	glVertex2f(x - w, y);
	glVertex2f(x + w, y);
	glVertex2f(x2 - w, y2);
	glEnd();
}

void ESP::draw_lines(float thickness, bool outlined, float x, float x2, float y, float y2, float w, Vector3 color)
{
	if (outlined)
	{
		glLineWidth(thickness + 1.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(x - w, y);
		glVertex2f(x2 - w, y2);
		glEnd();
	}

	glLineWidth(thickness);
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINES);
	glVertex2f(x - w, y);
	glVertex2f(x2 - w, y2);
	glEnd();
}

void ESP::snaplines(bool ignore_teammates, bool outlined, int display_w, int display_h)
{
	for (size_t i{}; i < Globals::current_entities; ++i)
	{
		if (!valid_entity(Globals::entities[i])) continue;

		if (ignore_teammates && Globals::entities[i].m_team == Globals::myself.m_team) continue;
		if (!Globals::entities[i].isAlive()) continue;

		Vector2 bottom_coords;

		if (!Maths::world_to_screen(Globals::entities[i].m_coords, bottom_coords, matrix, display_w, display_h)) continue;

		Vector3 color;
		if (Globals::myself.m_team == Globals::entities[i].m_team) color = Vector3(1.0f, 1.0f, 1.0f);
		else color = Vector3(1.0f, 0.0f, 0.0f);

		draw_lines(1.0f, outlined, origin_bottom.x, bottom_coords.x, origin_bottom.y, bottom_coords.y, 0.0f, color);
	}
}

void ESP::bounding_box(bool ignore_teammates, bool outlined, bool filled, int display_w, int display_h)
{
	for (size_t i{}; i < Globals::current_entities; ++i)
	{
		if (!valid_entity(Globals::entities[i]))	continue;

		if (ignore_teammates && Globals::entities[i].m_team == Globals::myself.m_team) continue;
		if (!Globals::entities[i].isAlive())	continue;

		Vector3 bot_head{ Globals::entities[i].m_head_coords.x, Globals::entities[i].m_head_coords.y, Globals::entities[i].m_head_coords.z + 0.8f };

		Vector2 bottom_coords;
		Vector2 top_coords;

		if (!Maths::world_to_screen(Globals::entities[i].m_coords, bottom_coords, matrix, display_w, display_h))	 continue;
		if (!Maths::world_to_screen(bot_head, top_coords, matrix, display_w, display_h))	continue;

		float h = top_coords.y - bottom_coords.y;
		float w = h / 5.0f;

		Vector3 color;
		if (Globals::myself.m_team == Globals::entities[i].m_team) color = Vector3{ 1.0f, 1.0f, 1.0f };
		else color = Vector3{ 1.0f, 0.0f, 0.0f };

		if (!filled)
		{
			draw_rect(outlined, top_coords.x, bottom_coords.x, top_coords.y, bottom_coords.y, w, color);
		}
		else
		{
			draw_filled_rect(outlined, top_coords.x, bottom_coords.x, top_coords.y, bottom_coords.y, w, color);
		}
	}
}

void ESP::health(bool ignore_teammates, bool outlined, int display_w, int display_h)
{
	for (size_t i{}; i < Globals::current_entities; ++i)
	{
		if (!valid_entity(Globals::entities[i])) continue;

		if (ignore_teammates && Globals::entities[i].m_team == Globals::myself.m_team) continue;
		if (!Globals::entities[i].isAlive())	continue;

		Vector3 bot_head{ Globals::entities[i].m_head_coords.x, Globals::entities[i].m_head_coords.y, Globals::entities[i].m_head_coords.z + 0.8f };

		Vector2 bottom_coords;
		Vector2 top_coords;

		if (!Maths::world_to_screen(Globals::entities[i].m_coords, bottom_coords, matrix, display_w, display_h))	continue;
		if (!Maths::world_to_screen(bot_head, top_coords, matrix, display_w, display_h))	continue;

		float height = top_coords.y - bottom_coords.y;
		float width = height / 4.0f;

		//linear interpolation between two points using percentage
		float t{ 1.0f - ((Globals::entities[i].m_health / 100.0f)) };
		float x = top_coords.x + t * (bottom_coords.x - top_coords.x);
		float y = top_coords.y + t * (bottom_coords.y - top_coords.y);

		if (outlined)
		{
			Vector3 color_black{ 0.0f, 0.0f, 0.0f };
			draw_lines(2.0f, false, top_coords.x, bottom_coords.x, top_coords.y, bottom_coords.y, width, color_black);
		}

		Vector3 color_green{ 0.0f, 1.0f, 0.0f };
		draw_lines(1.0f, false, x, bottom_coords.x, y, bottom_coords.y, width, color_green);
	}
}