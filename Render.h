#pragma once

#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>

#ifndef STB_IMAGE_H
#define STB_IMAGE_H
#include <stb_image.h>
#endif // !STB_IMAGE_H

#include "Shader.h"
#include "GameObject.h"

using namespace _GameObject;

namespace _Render {
	class Render {
		const char* window_title;
		int window_width;
		int window_height;

		GLFWwindow* window;
		// unsigned int VBO, VAO, EBO;

		unsigned int vertexShader;
		unsigned int fragmentShader;
		int shaderProgram;

		glm::mat4 model, projection;
		glm::mat4 view;

		// Shader
		Shader* shader;
		const char* vshader = "shader_vertex.vs";
		const char* fshader = "shader_fragment.fs";

		// Timeing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		bool closing = false; // TODO: better way to close
		std::vector<GameObject> objects;

	protected:
	public:
		Render(int width, int height, const char* title);
		~Render();

		GLFWwindow* get_window();
		
		void set_camera(glm::mat4& camera);

		void update();
		void add_game_object(GameObject);
	};
}

/* TODO LIST:
conversion from obj to vertices/entites
import obj
parameterize obj input to renderer

*/