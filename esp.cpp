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

void ESP::draw_lines(size_t current_entities, std::array<Entity, 32> entities)
{
	for (size_t i{}; i < current_entities; ++i)
	{
		Vector2 screen_coords;
		if (!Maths::world_to_screen(entities[i].m_coords, screen_coords, matrix, screen_width, screen_height))
			continue;

		float line[]{
			origin_bottom.x, origin_bottom.y, 0.0f,
			screen_coords.x, screen_coords.y, 0.0f
		};

		unsigned int vao, vbo;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_LINES, 0, 6);

		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}
}