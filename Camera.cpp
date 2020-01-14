#include "Camera.h"

using namespace _Camera;

// TODO: Remove camera string

Camera::Camera(glm::vec3 pos) : Entity::Entity("Camera", pos) {
	set_target(glm::vec3(pos.x, pos.y, pos.z - 3));
}

void Camera::set_target(glm::vec3 target, glm::vec3 world_up) {
	this->target = target;
	this->direction = glm::normalize(this->position - this->target);
	this->right = glm::normalize(glm::cross(world_up, direction));
	this->up = glm::normalize(glm::cross(direction, right));
	this->front = glm::normalize(-direction);
	this->view = look_at();
}

glm::mat4 Camera::look_at() {
	view = glm::lookAt(position, position + front, up);
	return view;
}

void Camera::update_delta(float delta) {
	this->delta = delta;
}

void Camera::process_keyboard(float delta, const char key) {
	// TODO: figure out why adding deltaTime causes huge lag
	float deltaSpeed = speed; // * delta;
	if(key == 'W') { position += deltaSpeed * front; }
	if(key == 'S') { position -= deltaSpeed * front; }
	if(key == 'A') { position -= glm::normalize(glm::cross(front, up)) * deltaSpeed; }
	if(key == 'D') { position += glm::normalize(glm::cross(front, up)) * deltaSpeed; }
}

void Camera::process_mouse_movement() {

}

void Camera::process_mouse_scroll() {

}

Camera::~Camera() {

}