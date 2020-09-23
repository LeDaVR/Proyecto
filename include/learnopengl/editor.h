#ifndef EDITOR_H
#define EDITOR_H

#include "dinamicarray.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include "camera.h"
#include <learnopengl/model.h>
#include <fstream>
#include <string>
#include <vector>
#include <learnopengl/element.h>
#include <learnopengl/element.cpp>

class EditorData {
		int currentindex;
		Element currentelement;
		vector<std::string> models;
	public:
		EditorData();
		void changeModel();
		Element getElement();

		void save(vector<Element>,std::string);

};

class Editor{
	private:
		std::string mapaname;
		EditorData data;

		glm::mat4 modeltransform;
		Element currentelement;
		
		int dimension;
		float cuadrante;

		std::vector<float> vertices;         //cuadricula
		std::vector<unsigned int> indices;

		int index;					        //gestion de objetos
		bool* memorystatus;
		std::vector<Element> objects;
		std::vector<int> memory;

		void drawObjects(GLFWwindow*, Shader*, Camera*);
		void addModel();
		void deleteModel();
	public:
		Editor(std::string mapaname);
		
		bool isinside(GLFWwindow* window,Camera* camara);
		void use(GLFWwindow* window,Camera* camara,Shader *modelshader);	
		
		
		int getVerticesSize();
		int getIndicesSize();
		float* getVerticesArray();
		unsigned int* getIndicesArray();

		~Editor();
	
};


#endif
