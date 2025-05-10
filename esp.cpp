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
	/*static unsigned int vertex_shader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	static unsigned int fragment_shader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragment_shader);

	static unsigned int shader_program{ glCreateProgram() };
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);*/

	for (size_t i{}; i < current_entities; ++i)
	{
		if (!entities[i].isAlive())
			continue;
		Vector2 screen_coords;
		if (!Maths::world_to_screen(entities[i].m_coords, screen_coords, matrix, screen_width, screen_height))
			continue;

		float line[]{
			origin_top.x, origin_top.y, 0.0f,
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

		//glUseProgram(shader_program);
		glDrawArrays(GL_LINES, 0, 6);

		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}
	//glDeleteProgram(shader_program);
}