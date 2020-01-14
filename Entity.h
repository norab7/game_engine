#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace _Entity {
	class Entity {
		glm::mat4 matrix;
	public:
		Entity(glm::vec3 pos);
		Entity(glm::mat4 matrix);
		~Entity();

		void transform(glm::mat4 trans);
		void translate(glm::vec3 trans);
		void rotate(float degrees, glm::vec3 axis);
		void scale(float scale);
		void scale(glm::vec3 scale);

	};
}