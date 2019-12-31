#pragma once
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

const char* window_title = "Window Title";
const int window_width = 1920;
const int window_height = 1080;

GLFWwindow* window;

int main(int argc, char** argv);
bool init_systems();