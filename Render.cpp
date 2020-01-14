#include "Render.h"

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

	// Create textures using texture object
	tex1 = new _Texture::Texture("container.jpg", GL_RGB);
	tex2 = new _Texture::Texture("awesomeface.png", GL_RGBA);

	// Set textures in the shader class
	shader->use();
	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);

	glfwSwapInterval(0);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Uncomment for Wireframe

	camera = new _Camera::Camera(glm::vec3(0, 0, 10));
	camera->set_target(glm::vec3(0, 0, 0));
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

	// Timeing
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Input
	process_keyboard(window, deltaTime);

	// Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind textures to shader unifroms
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex1->get());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex2->get());
	shader->use();

	const float radius = 10.0f;
	// camera->set_position(glm::vec3(sin(glfwGetTime()) * radius, 0, cos(glfwGetTime()) * radius));
	view = camera->look_at();

	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float) (window_width / window_height), 0.1f, 100.0f);

	unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
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

void Render::process_keyboard(GLFWwindow* window, float delta) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		closing = true;
	}

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera->process_keyboard(delta, 'W'); }
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera->process_keyboard(delta, 'S'); }
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera->process_keyboard(delta, 'A'); }
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera->process_keyboard(delta, 'D'); }

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