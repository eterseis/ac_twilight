#pragma once

#include <array>
#include "vector.h"
#include "offsets.h"
#include "constants.h"
#include "entity.h"
#include "maths.h"
#include "vector.h"
#include "globals.h"
#include "GLCommon.h"

inline constexpr Vector2 origin_top{ 0.0f, 1.0f };
inline constexpr Vector2 origin_bottom{ 0.0f, -1.0f };

class ESP
{
public:
	bool valid_entity(Entity& ent);
	// w == width //
	void draw_rect(bool outlined, float x, float x2, float y, float y2, float w, Vector3 color);
	void draw_filled_rect(bool outlined, float x, float x2, float y, float y2, float w, Vector3 color);
	void draw_lines(float thickness, bool outlined, float x, float x2, float y, float y2, float w, Vector3 color);
	void snaplines(bool outlined, int display_w, int display_h);
	void bounding_box(bool outlined, bool filled, int display_w, int display_h);
	void health(bool outlined, int display_w, int display_h);

public:
	std::array<float, 16> matrix;
};