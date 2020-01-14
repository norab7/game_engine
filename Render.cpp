#include "Render.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace _Render;

Render::Render(int window_width, int window_height, const char* title) {
	this->window_width = window_width;
	this->window_height = window_height;
	this->window_title = title;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	try {
		window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
		if(window == NULL) {
			std::cout << "GLFW window failed to create" << std::endl;
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			std::cout << "GLAD failed to initialize" << std::endl;
		}

		update_viewport(window_width, window_height, 0, 0);
	} catch(const std::exception & e) {
		std::cout << "Render::init(): " << e.what() << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	// Shader Code (Moved into object)
	shader = new Shader(vshader, fshader);

	// Vertices data
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//// Element data
	//unsigned int indices[] = {
	//	0, 1, 3,
	//	1, 2, 3
	//};

	//// Texture Coords
	//float texCoords[] = {
	//	0.0f, 0.0f,  // lower-left corner  
	//	1.0f, 0.0f,  // lower-right corner
	//	0.5f, 1.0f   // top-center corner
	//};

	// Generate Buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// glGenBuffers(1, &EBO);

	// Bind Buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Buffer Data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// Interpret Vertex Data: Position, Color, Texture
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Bind and Assign texture 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true); // Flip inputted texture files
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// Bind and Assign texture 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// Set textures in the shader class
	shader->use();
	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);

	glfwSwapInterval(0);

	 // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Uncomment for Wireframe
}

Render::~Render() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}

void Render::update() {
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// Input
	process_input(window);

	// Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Bind textures to shader unifroms
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	shader->use();

	// Basic Camera and View matrices
	//model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	//model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // translate in reverse direction
	projection = glm::perspective(glm::radians(45.0f), (float) (window_width / window_height), 0.1f, 100.0f);
	// retrieve the matrix uniform locations
	unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
	// pass them to the shaders (3 different ways)
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader->setMat4("projection", projection);

	glBindVertexArray(VAO);
	for(unsigned int i = 0; i < 10; i++) {
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 0.0f;
		if(i % 3 == 0) {
			angle = (float) glfwGetTime() * 10;
		} else {
			angle = 20.0f * i;
		}
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
	//glfwWaitEvents();

	if(glfwWindowShouldClose(window)) {
		glfwTerminate();
	}
}

void Render::process_input(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		closing = true;
	}
}

bool Render::update_viewport(int width, int height, int start_width, int start_height) {
	try {
		glViewport(start_width, start_height, width, height);
	} catch(const std::exception & e) {
		std::cout << "Render::update_viewport() " << e.what() << std::endl;
		return false;
	}
	return true;
}

bool Render::is_closing() {
	return (glfwWindowShouldClose(window) || closing);
}

void Render::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}