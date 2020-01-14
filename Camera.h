#pragma once
#include <iostream>
#include "Entity.h"
#include "Process_Input.h"

namespace _Camera {
	class Camera : public _Entity::Entity, _Process_Input::Process_Input {
		glm::vec3 target;
		glm::vec3 direction;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 front;

		glm::mat4 view;

		const float speed = 0.005f;
		float delta = 1.0f;

	public:
		Camera(glm::vec3 pos = glm::vec3(0, 0, 0));
		~Camera();

		glm::mat4 look_at();

		void set_target(glm::vec3 target, glm::vec3 world_up = glm::vec3(0, 1, 0));
		void update_delta(float delta);

		void process_keyboard(float delta, const char key) override;
		void process_mouse_movement() override;
		void process_mouse_scroll() override;
	};
}