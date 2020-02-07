#define STB_IMAGE_IMPLEMENTATION // Must be done before using stb_image.h
#include "Main.h"

int main(int argc, char** argv) {

	// Setup Classes
	render = new _Render::Render(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	player = new _Player_Character::Player_Character();

	// Initial Values, references, pointers
	player->set_position(glm::vec3(0, 0, 10));

	// Assign Callback
	setup_callbacks();

	// std::map<std::shared_ptr<I_AABB>, unsigned>
	std::map<std::shared_ptr<I_AABB>, std::shared_ptr<GameObject>> object_map;

	srand(glfwGetTime());
	GameObject left = *new GameObject("left", "resources/graphics_objects/lamp_standing.obj", glm::vec3(-5, 0, 0));
	GameObject right = *new GameObject("right", "resources/graphics_objects/lamp_standing.obj", glm::vec3(1, 0, 0));


	game_objects.push_back(std::make_shared<GameObject>(left));
	game_objects.push_back(std::make_shared<GameObject>(right));

	for(unsigned i = 0; i < game_objects.size(); i++) {
		boundary_volume.insert(game_objects[i]);
		object_map[game_objects[i]] = game_objects[i];
	}

	unsigned max_move = 2000;
	float sensitivity = 1000;

	bool collision = false;

	while(!shut_down) {

		// Process Inputs
		process_input();

		std::vector<std::shared_ptr<I_AABB>> collisions = boundary_volume.check_overlaps(game_objects[0]);
		if(!collisions.empty()) {
			collision = true;

			for(std::shared_ptr<I_AABB> collide : collisions) {
				if(object_map[collide] == game_objects[1]) {
					std::wcout << "Collision: " << (*object_map[collide]).get_id() << std::endl;
				}
			}
		}

		// Update Scene
		for(unsigned i = 0; i < game_objects.size(); i++) {
			if((*game_objects[i]).get_id() == "left") {
				if(collision) {
					(*game_objects[i]).translate(glm::vec3(-0.01, 0, 0));
				} else {
					(*game_objects[i]).translate(glm::vec3(0.01, 0, 0));
				}


				if((*game_objects[i]).get_position().x < -2) { collision = false; }
			}
		}

		// Render Scene
		render->set_camera(player->look_at());
		render->update(game_objects);
	}

	std::cout << "Press return to exit" << std::endl;
	std::cin.ignore();
	return 0;
}

void process_input() {
	player->process_keyboard(KEY_PRESS);
}

void create_game_object(const char* id, const char* dir, glm::vec3 position) {
	GameObject object(id, dir, position);


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