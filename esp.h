#pragma once

#include <array>
#include "vector.h"
#include "offsets.h"
#include "globals.h"
#include "entity.hpp"
#include "maths.h"
#include "GLCommon.h"

inline constexpr Vector2 origin_top{ 0.0f, 1.0f };
inline constexpr Vector2 origin_bottom{ 0.0f, -1.0f };

class ESP
{
public:
	bool valid_entity(Entity* ent);
	// w == width //
	void draw_rect(bool outlined, float x, float x2, float y, float y2, float w, Vector4 color);
	void draw_filled_rect(bool outlined, float x, float x2, float y, float y2, float w, Vector4 color);
	void draw_lines(float thickness, bool outlined, float x, float x2, float y, float y2, float w, Vector4 color);
	void snaplines(bool ignore_teammates, bool outlined, int display_w, int display_h, Vector4 color);
	void bounding_box(bool ignore_teammates, bool outlined, bool filled, int display_w, int display_h, Vector4 color);
	void health(bool ignore_teammates, bool outlined, int display_w, int display_h, Vector4 color);

public:
	std::array<float, 16> matrix;
	std::array<Entity, 31>& ents;
	Entity* myself;
};