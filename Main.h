#pragma once

#include <iostream>

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

// Functions
void process_input();

// Call Backs
void setup_callbacks();
void callback_window_resize(GLFWwindow* window, int w, int h);
void callback_keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void callback_mouse_input(GLFWwindow* window, int button, int action, int mods);
void callback_mouse_movement(GLFWwindow* window, double x, double y);
void callback_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char** argv);