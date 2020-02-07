#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "AABB_Tree.h"
#include "Render.h"
#include "Player_Character.h"

_Render::Render* render;
_Player_Character::Player_Character* player;

// Variables
bool shut_down = false;
bool KEY_PRESS[1024];

// Settings
const char* WINDOW_NAME = "Game Engine";
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

// Mouse / Camera
bool firstMouse = true;
float lastX = 0;
float lastY = 0;

// Objects and Physics
std::vector<std::shared_ptr<GameObject>> game_objects;
AABB_Tree boundary_volume(10);
std::map<std::shared_ptr<I_AABB>, std::shared_ptr<GameObject>> boundary_map;

// Functions
void process_input();
void create_game_object(const char* id, const char* dir, glm::vec3 position = glm::vec3(0));

// Call Backs
void setup_callbacks();
void callback_window_resize(GLFWwindow* window, int w, int h);
void callback_keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void callback_mouse_input(GLFWwindow* window, int button, int action, int mods);
void callback_mouse_movement(GLFWwindow* window, double x, double y);
void callback_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char** argv);