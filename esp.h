#pragma once

#include <array>
#include "vector.h"
#include "offsets.h"
#include "constants.h"
#include "entity.h"
#include "maths.h"
#include "GLCommon.h"

inline const char* vertex_shader_source
{
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0"
};
inline const char* fragment_shader_source
{
	"#version 330 core\n"
	"out vec4 frag_color;\n"
	"void main()\n"
	"{\n"
	"	frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0"
};

inline const Vector2 origin_top{ 0.0f, 1.0f };
inline const Vector2 origin_bottom{ 0.0f, -1.0f };
inline const int screen_width{ GetSystemMetrics(SM_CXSCREEN) };
inline const int screen_height{ GetSystemMetrics(SM_CYSCREEN) };


class ESP
{
public:
	bool valid_entity(Entity& ent);
	void draw_lines(size_t current_entities, std::array<Entity, 32> entities);
	void draw_boxes(size_t current_entities, std::array<Entity, 32> entities);

public:
	std::array<float, 16> matrix;
};