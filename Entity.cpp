#include "Entity.h"

using namespace _Entity;

Entity::Entity(glm::vec3 pos) {
	matrix = glm::translate(glm::mat4(1.0f), pos);
}

Entity::Entity(glm::mat4 matrix) {
	this->matrix = matrix;
}

void Entity::transform(glm::mat4 trans) {
	matrix *= trans;
}

void Entity::translate(glm::vec3 trans) {
	matrix = glm::translate(matrix, trans);
}

void Entity::rotate(float degrees, glm::vec3 axis) {
	matrix = glm::rotate(matrix, glm::radians(degrees), axis);
}

void Entity::scale(float scale) {
	matrix = glm::scale(matrix, glm::vec3(scale));
}

void Entity::scale(glm::vec3 scale) {
	matrix = glm::scale(matrix, scale);
}

Entity::~Entity() {

}