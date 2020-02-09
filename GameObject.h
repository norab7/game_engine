#pragma once

#include "Model.h"
#include "Entity.h"
#include "I_AABB.h"

namespace _GameObject {
	class GameObject : public _Entity::Entity, public _Model::Model, public I_AABB {

	protected:
		float air_resistance = 2;
		glm::vec3 velocity {0};
		glm::vec3 stored_force {0};
		float mass = 1;

	public:
		GameObject(const char* id, const char* dir);
		GameObject(const char* id, const char* dir, glm::vec3 position);
		~GameObject();

		bool flying = true;

		void add_force(glm::vec3 force, const float& delta);

		void add_velocity(glm::vec3 v);
		void set_velocity(glm::vec3 v);
		glm::vec3 get_velocity();

		void simulate(const float& delta);

		AABB get_AABB() const override;

	};
}
