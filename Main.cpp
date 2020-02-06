#define STB_IMAGE_IMPLEMENTATION // Must be done before using stb_image.h
#include "Main.h"

int main(int argc, char** argv) {

	// Setup Classes
	render = new _Render::Render(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	player = new _Player_Character::Player_Character();

	// Initial Values, references, pointers
	player->set_position(glm::vec3(0, 0, 10));

	int base_position = 3;
	render->add_game_object(*new GameObject("lamp_standing", "resources/graphics_objects/lamp_standing.obj", glm::vec3(-1, -2, -3)));

	// Assign Callback
	setup_callbacks();

	srand(glfwGetTime());
	for(unsigned int i = 0; i < 10; i++) {
		render->add_game_object(*new GameObject("lamp_standing", "resources/graphics_objects/lamp_standing.obj", glm::vec3((rand() % 20) - 10)));
	}
	for(unsigned int i = 0; i < 10; i++) {
		render->add_game_object(*new GameObject("lamp_standing", "resources/graphics_objects/lamp_standing.obj", glm::vec3((rand() % 20) - 10, (rand() % 20) - 10, (rand() % 20) - 10)));
	}

	while(!shut_down) {

		// Process Inputs
		process_input();

		// Update Scene


		// Render Scene
		render->set_camera(player->look_at());
		render->update();
	}

	std::cout << "Press return to exit" << std::endl;
	std::cin.ignore();
	return 0;
}

void process_input() {
	player->process_keyboard(KEY_PRESS);
}

void setup_callbacks() {
	GLFWwindow* window = render->get_window();
	glfwSetWindowSizeCallback(window, callback_window_resize);
	glfwSetKeyCallback(window, callback_keyboard_input);
	glfwSetCursorPosCallback(window, callback_mouse_movement);
	glfwSetMouseButtonCallback(window, callback_mouse_input);
	glfwSetScrollCallback(window, callback_mouse_scroll);
}

void callback_window_resize(GLFWwindow* window, int width, int height) {
	// TODO: handle resizing the window or make fullscreen
}

void callback_keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// Moved to using bool array as checking for key & press caused choppy input
	if(action == GLFW_PRESS) { KEY_PRESS[key] = true; }
	if(action == GLFW_RELEASE) { KEY_PRESS[key] = false; }

	if(KEY_PRESS[GLFW_KEY_ESCAPE]) {
		glfwSetWindowShouldClose(window, true);
		shut_down = true;
	}
}

void callback_mouse_movement(GLFWwindow* window, double xpos, double ypos) {
	if(firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	player->process_mouse_movement(xpos - lastX, lastY - ypos);
	lastX = xpos;
	lastY = ypos;
}

void callback_mouse_input(GLFWwindow* window, int button, int action, int mods) {

}

void callback_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset) {

}

/*
Main controller to accept various different object/class files to run differently dependent on what class is given for each section
Character,
Grpahics,
Scene,
Physics,
Etc.
*/