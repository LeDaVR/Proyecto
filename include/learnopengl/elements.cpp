#include "elements.h"
ElementData::ElementData(){
	data.push_back(arbol);
}

Elements* ElementData::Begin() {
	return &data[0];
}


Elements::Elements() {
}


std::string Elements::getInfo() {
	return info;
}

std::string Resources::getInfo() {
	return info;
}

CampodeLino::CampodeLino() {
	model.setModel("");
}
Mina::Mina() {
	model.setModel("");
}
Arbol::Arbol() {
	model.setModel("resources/models/arbol.obj");
}