#pragma once

#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <iostream>

#include "Shader.h"

namespace _Render {
	class Render {
		GLFWwindow* window;
		unsigned int VBO, VAO, EBO;

		unsigned int vertexShader;
		unsigned int fragmentShader;
		int shaderProgram;

		const char* window_title;
		int window_width;
		int window_height;

		// Shader
		Shader* shader;
		const char* vshader = "shader_vertex.vs";
		const char* fshader = "shader_fragment.fs";

		// Texture
		unsigned int texture;

		bool closing = false; // TODO: better way to close

	protected:
	public:
		Render(int width, int height, const char* title);
		~Render();

		void update();
		void process_input(GLFWwindow* window);
		bool update_viewport(int width, int height, int start_width = 0, int start_height = 0);
		bool is_closing();

		// Static Methods
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	};
}

/* TODO LIST:
conversion from obj to vertices/entites
import obj
parameterize obj input to renderer

*/