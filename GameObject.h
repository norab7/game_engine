#pragma once

#include "Model.h"
#include "Entity.h"
#include "I_AABB.h"

namespace _GameObject {
	class GameObject : public _Entity::Entity, public _Model::Model, public I_AABB {

	protected:
		glm::vec3 velocity {0};
		glm::vec3 force {0};
		unsigned time_step = 1;
		float mass = 1;

	public:
		GameObject(const char* id, const char* dir);
		GameObject(const char* id, const char* dir, glm::vec3 position);
		~GameObject();

		void add_force(glm::vec3 force);
		void simulate();

		AABB get_AABB() const override;

	};
}
