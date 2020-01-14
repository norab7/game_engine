#pragma once

#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef STB_IMAGE_H
#define STB_IMAGE_H
#include <stb_image.h>
#endif // !STB_IMAGE_H

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

namespace _Render {
	class Render {
		const char* window_title;
		int window_width;
		int window_height;

		GLFWwindow* window;
		unsigned int VBO, VAO, EBO;

		unsigned int vertexShader;
		unsigned int fragmentShader;
		int shaderProgram;

		glm::mat4 model, view, projection;

		// Shader
		Shader* shader;
		const char* vshader = "shader_vertex.vs";
		const char* fshader = "shader_fragment.fs";

		// Texture
		unsigned int texture1, texture2;
		_Texture::Texture* tex1;
		_Texture::Texture* tex2;

		// Camera
		_Camera::Camera* camera;

		// Timeing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		bool closing = false; // TODO: better way to close

	protected:
	public:
		Render(int width, int height, const char* title);
		~Render();

		void update();
		void process_keyboard(GLFWwindow* window, float delta);
		void process_mouse_movement(GLFWwindow* window);
		void process_mouse_scroll(GLFWwindow* window);
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