#include "GameObject.h"

using namespace _GameObject;

GameObject::GameObject(const char* id, const char* dir) : Entity(id), Model(id, dir) {

}

GameObject::GameObject(const char* id, const char* dir, glm::vec3 position) : Entity(id, position), Model(id, dir) {

}

GameObject::~GameObject() {

}

void GameObject::add_force(glm::vec3 f) {
	force += f;
}

void GameObject::simulate() {
	velocity.x = ((force.x / mass) * time_step);
	velocity.y = ((force.y / mass) * time_step);
	velocity.z = ((force.z / mass) * time_step);
	set_position(get_position() + velocity);
	time_step++;

	force *= 0;
}

AABB GameObject::get_AABB() const {

	const glm::vec3 position = get_position();
	return *new AABB(bounds_min.x + position.x, bounds_min.y + position.y, bounds_min.z + position.z, bounds_max.x + position.x, bounds_max.y + position.y, bounds_max.z + position.z);
}