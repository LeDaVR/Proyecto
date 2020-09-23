#include "element.h"

Element::Element() {
	elementID = "";
	position = glm::vec3(0.0f);
	rotate = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	angle = glm::vec3(0.0f);
	refreshinfo();
}


Element::Element(std::string id, glm::vec3 position, glm::vec3 rotate,glm::vec3 angle, glm::vec3 scale){
	this->elementID = id;
	this->position = position;
	this->rotate = rotate;
	this->scale = scale;
	this->angle = angle;

	refreshinfo();
	//setModel();
}

void Element::refreshinfo() {
	info.clear();
	info.push_back(elementID);
	info.push_back(std::to_string(position.x) + " " + std::to_string(position.y) + " " + std::to_string(position.z));
	info.push_back(std::to_string(rotate.x*angle.x) + " " + std::to_string(rotate.y*angle.y) + " " + std::to_string(rotate.z*angle.z));
	info.push_back(std::to_string(scale.x) + " " + std::to_string(scale.y) + " " + std::to_string(scale.z));
}
void Element::setModel() {
	model.resetModel();
	model.setModel("resources/models/" + elementID + ".obj");
	refreshinfo();
}

void Element::setID(std::string ID) {
	elementID = ID;
	refreshinfo();
}

void Element::setPosition(glm::vec3 position) {
	this->position = position;
	refreshinfo();
}
void Element::setRotation(glm::vec3 rotation, glm::vec3 angle) {
	this->angle = angle;
	this->rotate = rotation;
	refreshinfo();
}
void Element::setScale(glm::vec3 scale) {
	this->scale = scale;
	refreshinfo();
}

void Element::setData(std::string id, glm::vec3 position, glm::vec3 rotate, glm::vec3 angle, glm::vec3 scale) {
	this->elementID;
	setPosition(position);
	setRotation(rotate, angle);
	setScale(scale);
	refreshinfo();
}

std::string Element::getID() {
	return elementID; 
}

glm::vec3 Element::getPosition() {
	return position;
}
glm::vec3 Element::getRotate() {
	return rotate;
}
glm::vec3 Element::getScale() {
	return scale;
}

std::string Element::getInfo() {
	return info[1]+'\n'+info[2]+'\n'+info[3];
}
