#include "GameObject.h"

using namespace _GameObject;

GameObject::GameObject(const char* id, const char* dir) : Entity(id), Model(id, dir) {

}

GameObject::GameObject(const char* id, const char* dir, glm::vec3 position) : Entity(id, position), Model(id, dir) {

}

GameObject::~GameObject() {

}

void GameObject::add_force(glm::vec3 f , const float& delta) {
	glm::vec3 force = (f * mass);
	glm::vec3 acceleration = force / mass;
	velocity += acceleration * delta;
	std::cout << velocity.y << std::endl;
}

void GameObject::simulate(const float& delta) {
	set_position(get_position() + velocity * delta);
}

void GameObject::add_velocity(glm::vec3 v) {
	velocity += v;
}

void GameObject::set_velocity(glm::vec3 v) {
	velocity = v;
}

glm::vec3 GameObject::get_velocity() {
	return velocity;
}

AABB GameObject::get_AABB() const {

	const glm::vec3 position = get_position();
	return *new AABB(bounds_min.x + position.x, bounds_min.y + position.y, bounds_min.z + position.z, bounds_max.x + position.x, bounds_max.y + position.y, bounds_max.z + position.z);
}