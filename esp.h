#pragma once

#include <array>
#include "vector.h"
#include "offsets.h"
#include "constants.h"
#include "entity.h"
#include "maths.h"
#include "GLCommon.h"

inline const Vector2 origin_top{ 0.0f, 1.0f };
inline const Vector2 origin_bottom{ 0.0f, -1.0f };

class ESP
{
public:
	bool valid_entity(Entity& ent);
	void draw_lines(size_t current_entities, std::array<Entity, 32> entities, Entity myself, int display_w, int display_h);
	void draw_boxes(size_t current_entities, std::array<Entity, 32> entities, Entity myself, int display_w, int display_h);

public:
	std::array<float, 16> matrix;
};