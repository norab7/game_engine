#include "Main.h"

int main(int argc, char** argv) {
	
	render = new _Render::Render(1920, 1080, "Window Title");


	bool exit = false;
	while (!render->is_closing()) {
		render->update();
	}

	std::cout << "Press return to exit" << std::endl;
	std::cin.ignore();
	return 0;
}
