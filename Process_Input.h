#pragma once
namespace _Process_Input {
	class Process_Input {

	public:
		virtual void process_keyboard(float delta, const char key) = 0;
		virtual void process_mouse_movement() = 0;
		virtual void process_mouse_scroll() = 0;
	};
}