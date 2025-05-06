#include <iostream>
#include <array>
#include "memory.h"
#include "constants.h"
#include "offsets.h"
#include "miscellaneous.h"
#include "entity.h"
#include "maths.h"
#include "vector.h"
#include "aimbot.h"
#include "esp.h"

#include "GLCommon.h"
//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"



bool enable_debug{};
bool enable_aimbot{};
bool enable_lines{};

Miscellaneous misc{};
std::array<Entity, 32> entities{};
//Entity entities[32];

void handle_input()
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		misc.m_health = !misc.m_health;
	}
	if (GetAsyncKeyState(VK_DELETE) & 1)
	{
		misc.m_ammo = !misc.m_ammo;
	}
	if (GetAsyncKeyState(VK_DOWN) & 1)
	{
		misc.m_rapidfire = !misc.m_rapidfire;
	}
	if (GetAsyncKeyState(VK_UP) & 1)
	{
		enable_aimbot = !enable_aimbot;
	}
	if (GetAsyncKeyState(VK_F9) & 1)
	{
		enable_debug = !enable_debug;
	}
	if (GetAsyncKeyState(VK_RCONTROL) & 1)
	{
		enable_lines = !enable_lines;
	}
}

void debug_mode(const size_t& current_entities)
{
	std::cout << "---DEBUG MODE---\n\n";
	for (size_t i{}; i < current_entities; ++i)
	{
		std::cout << std::hex;
		std::cout << "address: 0x" << entities[i].m_address << "\n";
		std::cout << "vTable: 0x" << entities[i].vf_table << "\n";
		std::cout << std::dec;
		std::cout << "name: " << entities[i].m_name << "\n";
		std::cout << "health: " << entities[i].m_health << "\n";
		std::cout << "is alive: " << entities[i].isAlive() << "\n";
		std::cout << "team: " << entities[i].m_team << "\n";

		std::cout << "coords: (" << entities[i].m_coords.x << ", "
			<< entities[i].m_coords.y << ", "
			<< entities[i].m_coords.z << ")\n";

		std::cout << "distance from local player: " << entities[i].m_distance_from_local_player << "\n";
		std::cout << "---------------------------------------\n";
	}
	Sleep(10);
	system("cls");

}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_FLOATING, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GL_TRUE);
	glfwWindowHint(GLFW_DECORATED, FALSE);

	GLFWwindow* window{ glfwCreateWindow(800, 600, "twilight", nullptr, nullptr) };

	if (!window)
	{
		std::cout << "Failed to create window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	Entity myself;
	size_t current_entities;

	ESP visuals;

	while (!glfwWindowShouldClose(window))
	{
		handle_input();

		current_entities = offsets::get_max_entities() - 1 /*except me*/;
		update_local_player(myself);

		if (current_entities > 0)
		{
			populate_entity_array(entities, myself, current_entities);
			Maths::bubble_sort(entities, current_entities);
		}

		if (misc.m_health)
		{
			misc.unlimited_health(myself.m_address);
		}
		if (misc.m_ammo)
		{
			misc.unlimited_ammo(myself.m_address);
		}
		if (misc.m_rapidfire)
		{
			misc.rapidfire(myself.m_address);
		}
		if (enable_debug)
		{
			debug_mode(current_entities);
		}
		if (enable_aimbot)
		{
			Aimbot::closest_target(get_closest_entity(entities, current_entities), myself);
		}

		//RENDERING
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);

		if (enable_lines)
		{
			visuals.matrix = offsets::get_view_matrix();
			visuals.draw_lines(current_entities, entities);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}