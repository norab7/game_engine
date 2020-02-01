#pragma once
#include "Camera.h"
#include "Process_Input.h"

namespace _Player_Character {
	class Player_Character : public _Camera::Camera, _Process_Input::Process_Input {
		bool firstMouse = true;

	protected:
	public:
		Player_Character();
		~Player_Character();

		void process_keyboard(bool* KEYS) override;
		void process_mouse_movement(double xpos, double ypos) override;
		void process_mouse_scroll() override;

	};
}