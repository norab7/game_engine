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

		// Mouse cursor or no cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			std::cout << "GLAD failed to initialize" << std::endl;
		}

		glViewport(0, 0, window_width, window_height);

		// update_viewport(window_width, window_height, 0, 0);
	} catch(const std::exception & e) {
		std::cout << "Render::init(): " << e.what() << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	// Shader Code (Moved into object)
	shader = new Shader(vshader, fshader);
	//nanosuit = new _Model::Model(suit);

	glfwSwapInterval(0);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Uncomment for Wireframe
}

Render::~Render() {
	glfwTerminate();
}

void Render::update(const std::vector<std::shared_ptr<GameObject>>& objects) {

	// Timeing
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->use();

	projection = glm::perspective(glm::radians(45.0f), (float) (window_width / window_height), 0.1f, 100.0f);
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);

	for(unsigned i = 0; i < objects.size(); i++) {

		//g.scale(glm::vec3(0.5, 0.5, 0.5));
		//g.rotate((int) (currentFrame * 100), glm::vec3(0, 1, 0));
		 shader->setMat4("model", (*objects[i]).get_matrix());

		// g.randomize_mesh_vertices();
		 (*objects[i]).Draw(*shader, true);
	}
	// nanosuit->Draw(*shader);

	// Buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

	if(glfwWindowShouldClose(window)) {
		glfwTerminate();
	}
}

GLFWwindow* Render::get_window() {
	return this->window;
}

void Render::set_camera(glm::mat4& camera) {
	this->view = camera;
}