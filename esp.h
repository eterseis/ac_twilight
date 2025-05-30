#pragma once

#include <array>
#include "vector.h"
#include "offsets.h"
#include "globals.h"
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
	void draw_rect(bool outlined, float x, float x2, float y, float y2, float w, Vector4 color);
	void draw_filled_rect(bool outlined, float x, float x2, float y, float y2, float w, Vector4 color);
	void draw_lines(float thickness, bool outlined, float x, float x2, float y, float y2, float w, Vector4 color);
	void snaplines(Vector4 color);
	void bounding_box(bool filled, Vector4 color);
	void health(Vector4 color);

public:
	std::array<float, 16> m_matrix{};
	bool m_ignore_teammates{};
	bool m_outlined{};
	int m_display_w{};
	int m_display_h{};
};