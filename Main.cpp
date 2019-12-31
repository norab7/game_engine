#include "Main.h"

int main(int argc, char** argv) {
	
	init_systems();

	bool exit = true;
	while (!exit) {
		
		// input

	}


	std::cout << "Press return to exit" << std::endl;
	std::cin.ignore();
	return 0;
}

bool init_systems() {
	try{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
		if (window == NULL){
			std::cout << "GLFW window failed to create" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
			std::cout << "GLAD failed to initialize" << std::endl;
			return false;
		}

		glViewport(0, 0, window_width, window_height);

	}catch (const std::exception&){
		return false;
	}
	return true;
}