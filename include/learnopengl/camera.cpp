#include "camera.h"

Camera::Camera(const unsigned int _WIDTH,const unsigned int _HEIGHT){
	this->WIDTH=float(_WIDTH);
	this->HEIGHT=float(_HEIGHT);
	xoverflow=0.0f;
	yoverflow=0.0f;
	altura=10.0f;
	fov=90.0f;
	RA=WIDTH/HEIGHT;
	DRY=2*altura*1;
	DRX=DRY*RA;
	cameraPos= glm::vec3(0.0f,altura,0.0f);
	cameraDir= glm::vec3(0.0f,-1.0f,0.0f);
	cameraUp = glm::vec3(0.0f,0.0f,-1.0f);
}

void Camera::camera_mouse_callback(GLFWwindow *window,float deltaTime){
	float cameraSpeed = 20.0 * deltaTime;
	int WIDTH,HEIGHT;
	double mousePositionx, mousePositiony;
	glfwGetWindowSize(window,&WIDTH,&HEIGHT);
	glfwGetCursorPos(window,&mousePositionx,&mousePositiony);
	//this->WIDTH=float(WIDTH);
	//this->HEIGHT=float(HEIGHT);
	
	if(mousePositionx>=WIDTH-1.0){
		if(mousePositionx>WIDTH){
			glfwSetCursorPos(window,WIDTH,mousePositiony);
			
		}
		cameraPos.x+=cameraSpeed;
		this->xoverflow+=cameraSpeed;
	}
	
	if(mousePositionx<=1){
		if(mousePositionx<0){
			glfwSetCursorPos(window,0.0f,mousePositiony);
		}
		cameraPos.x-=cameraSpeed;
		this->xoverflow-=cameraSpeed;
	}
	
	if(mousePositiony<=1){
		if(mousePositiony<0){
			glfwSetCursorPos(window,mousePositionx,0);
		}
		cameraPos.z-=cameraSpeed;
		this->yoverflow-=cameraSpeed;
	}
	
	if(mousePositiony>=HEIGHT-1.0){
		if(mousePositiony>HEIGHT){
			glfwSetCursorPos(window,mousePositionx,HEIGHT);
		}
		cameraPos.z+=cameraSpeed;
		this->yoverflow+=cameraSpeed;
	}
}
void Camera::camera_protection(Shader *ourShader){
	glm::mat4 projection = glm::perspective(glm::radians(fov),WIDTH/HEIGHT, 0.1f, 100.0f);
    ourShader->setMat4("projection", projection);
}
void Camera::camera_transformation(Shader *ourShader){
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);
	ourShader->setMat4("view", view);
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);
}


double Camera::getXoverflow(){
	return xoverflow;
}
double Camera::getYoverflow(){
	return yoverflow;
}

double Camera::get3dposX(GLFWwindow* window){
	double xpos,ypos;
	glfwGetCursorPos(window,&xpos,&ypos);
	return (DRX*xpos/WIDTH)-(DRX/2)+xoverflow;
}
double Camera::get3dposY(GLFWwindow* window){
	double xpos,ypos;
	glfwGetCursorPos(window,&xpos,&ypos);
	return +(DRY*ypos/HEIGHT)-(DRY/2)+yoverflow;
}
double Camera::getWidth() {
	return WIDTH;
}
double Camera::getHeight() {
	return HEIGHT;
}

float Camera::getDRX() {
	return this->DRX;
}
float Camera::getDRY() {
	return this->DRY;
}