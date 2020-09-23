#include "editor.h"

EditorData::EditorData(){
	std::string modelname="";
	std::string archivo="";
	ifstream source("models.txt");
	getline(source, archivo,'\0');
	source.close();
	cout << archivo.size() << endl;
	for (int i = 0; i<archivo.size()+1; i++) {
		if(archivo[i]!='\n'&&archivo[i]!='\0')
			modelname += archivo[i];
		else {
			models.push_back(modelname);
			modelname = "";
		}
	}
	cout << "MODELS " << endl;
	for (int i = 0; i < models.size(); i++)
		std::cout << models[i] << std::endl;
	currentelement.setID(models[0]);
	currentelement.model.setModel("resources/models/"+models[0]+".obj");
	currentindex = 0;
}

void EditorData::changeModel() {
	if (currentindex < models.size() - 1)
		currentindex++;
	else
		currentindex = 0;
	currentelement.setID(models[currentindex]);
	currentelement.model.resetModel();
	currentelement.model.setModel("resources/models/" + currentelement.getID() + ".obj");
}

Element EditorData::getElement() {
	return currentelement;
}

void EditorData::save(vector<Element> objects,std::string mapaname) {
	ofstream o(mapaname);
	int cont = 0;
	for (int i = 0; i < models.size(); i++){
		for (int j = 0; j < objects.size(); j++){
			if (models[i] == objects[j].getID())
				cont++;
		}
		if (cont > 0) {
			o << models[i] << " " << cont << '\n';
			cont = 0;
			for (int k = 0; k < objects.size(); k++) {
				if (models[i] == objects[k].getID())
					o << objects[k].getInfo() << '\n';
			}
		}
	}
	o << -1;
	o.close();
}

Editor::Editor(std::string mapaname){
	this->mapaname = mapaname;
	dimension=80;
	cuadrante=1.0f;
	memorystatus = new bool[dimension * dimension];
	for (int i = 0; i < dimension * dimension; i++) {
		memorystatus[i] = true;
	}
	for(int i=0;i<=dimension;i++){
		for(int j=0;j<=dimension;j++){
			vertices.push_back(float(j)*cuadrante);
			vertices.push_back(0.0f);
			vertices.push_back(-float(i) * cuadrante);
		}
	}
	
	int cont=0;
	for(int i=0;i<dimension;i++){
		for(int j=0;j<dimension;j++){
			indices.push_back(cont);
			indices.push_back(cont+1);
			indices.push_back(cont+dimension+2);
			indices.push_back(cont+dimension+1);
			indices.push_back(cont);	
			cont++;
		}
		indices.push_back(cont+dimension);
		cont++;
	}
	currentelement = data.getElement();
}

bool Editor::isinside(GLFWwindow* window,Camera* camara){
	double xpos,ypos;
	xpos=camara->get3dposX(window);
	ypos=camara->get3dposY(window);
	if(xpos>=0&&xpos<=dimension*cuadrante&&ypos<=0&&ypos>=-dimension*cuadrante)
		return true;
	return false;
}

void Editor::drawObjects(GLFWwindow *window ,Shader *modelshader,Camera *camara) {
	for (int i = 0; i < objects.size(); i++) {
		modelshader->use();
		camara->camera_protection(modelshader);
		camara->camera_transformation(modelshader);
		modeltransform = glm::mat4(1.0f);
		modeltransform = glm::translate(modeltransform,objects[i].getPosition());
		modeltransform = glm::scale(modeltransform, objects[i].getScale());
		//modeltransform = glm::rotate(modeltransform, glm::radians(90.0f),objects[i].getRotate());
		modelshader->setMat4("model", modeltransform);
		objects[i].model.Draw(*modelshader);
	}
}

void Editor::addModel() {
	memorystatus[this->index] = false;
	memory.push_back(this->index);
	objects.push_back(currentelement);

	int xpos, ypos;
	xpos = index % dimension;
	ypos = index / dimension + 1;
	glm::vec3 position=glm::vec3(xpos + cuadrante / 2.0f,0.0f,-ypos +cuadrante / 2.0f);
	glm::vec3 rotate = glm::vec3(0, 0, 0);
	glm::vec3 angle = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	objects[objects.size() - 1].setID(currentelement.getID());
	objects[objects.size() - 1].setPosition(position);
	objects[objects.size() - 1].setRotation(rotate,angle);
	objects[objects.size() - 1].setScale(scale);
	cout << objects[objects.size() - 1].getInfo(); 
}

void Editor::deleteModel(){
	for (int i = 0; i < memory.size(); i++) {
		if (memory[i] == index) {
			memory.erase(memory.begin()+i);
			objects.erase(objects.begin() + i);
			break;
		}
	}
	memorystatus[this->index] = true;
}

void Editor::use(GLFWwindow* window,Camera* camara,Shader *modelshader){
			drawObjects(window, modelshader, camara);
			if (isinside(window,camara)){
				int leftclick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
				int rightclick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
				double xpos, ypos;
				xpos = camara->get3dposX(window);
				ypos = camara->get3dposY(window);
				float cx, cy;
				cx = int(xpos / cuadrante) + (cuadrante / 2.0f);
				cy = int(ypos / cuadrante) + 1 - (cuadrante / 2.0f);
				index = int(xpos / cuadrante) + dimension * int(-ypos / cuadrante);

				modelshader->use();
				camara->camera_protection(modelshader);
				camara->camera_transformation(modelshader);
				modeltransform = glm::mat4(1.0f);
				modeltransform = glm::translate(modeltransform,glm::vec3(camara->get3dposX(window),0.0f ,camara->get3dposY(window)));
				//modeltransform = glm::rotate(modeltransform, glm::radians(90.0f),glm::vec3(1,0,0));
				modelshader->setMat4("model", modeltransform);
				currentelement.model.Draw(*modelshader);

				if (leftclick == GLFW_PRESS) {
					if (memorystatus[index]) {
						addModel();
					}

				}
				if (rightclick == GLFW_PRESS) {
					if (!memorystatus[index]) {
						deleteModel();
					}
				}
			}
			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
				data.changeModel();
				this->currentelement = data.getElement();
			}

			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				data.save(objects, mapaname);
			}
}

int Editor::getVerticesSize(){
	return vertices.size();
}

int Editor::getIndicesSize(){
	return indices.size();
}

float* Editor::getVerticesArray(){
	return &vertices[0];
}
unsigned int* Editor::getIndicesArray(){
	return &indices[0];
}

Editor::~Editor(){
	delete[] memorystatus;
}

