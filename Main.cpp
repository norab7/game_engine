#define STB_IMAGE_IMPLEMENTATION // Must be done before using stb_image.h
#include "Main.h"

int main(int argc, char** argv) {

	render = new _Render::Render(1920, 1080, "My Game");

	bool exit = false;
	while(!render->is_closing()) {
		render->update();
	}

	std::cout << "Press return to exit" << std::endl;
	std::cin.ignore();
	return 0;
}
