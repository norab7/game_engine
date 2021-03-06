#pragma once
#include "Camera.h"
#include "I_Input.h"

namespace _Player_Character {
	class Player_Character : public _Camera::Camera, _I_Input::I_Input {
		bool firstMouse = true;
		float sensitivity = 0.025;
	protected:
	public:
		Player_Character();
		~Player_Character();

		void process_keyboard(bool* KEYS) override;
		void process_mouse_movement(double xpos, double ypos) override;
		void process_mouse_scroll() override;

	};
}