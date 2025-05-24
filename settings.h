#pragma once
#include "vector.h"

namespace Settings
{
	inline bool enable_menu{};

	inline bool visuals_enabled{};
	inline bool visuals_ignore_teammates{};
	inline bool visuals_outlined{};

	inline bool visuals_bounding_box{};
	inline Vector4 visuals_bounding_box_color{ 1.0f, 0.0f, 0.0f, 1.0f };

	inline bool visuals_filled_bounding_box{};

	inline bool visuals_snaplines{};
	inline Vector4 visuals_snaplines_color{ 1.0f, 0.0f, 0.0f, 1.0f };

	inline bool visuals_health_bar{};
	inline Vector4 visuals_health_bar_color{ 0.0f, 1.0f, 0.0f, 1.0f };

	inline bool misc_enabled{};

	inline bool misc_unlimited_health{};
	inline bool misc_unlimited_ammo{};

	inline bool misc_rapidfire{};
	inline int misc_rapidfire_delay{};

	inline bool aim_enabled{};
	inline bool aim_ignore_teammates{ };
}