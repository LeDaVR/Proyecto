#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>


class Camera{
		double xoverflow,yoverflow,altura;
		float DRY,DRX,RA;
		float WIDTH,HEIGHT;
		float fov;
		glm::vec3 cameraPos,cameraDir,cameraUp;

	public:
		Camera(const unsigned int w,const unsigned int h);
		void camera_mouse_callback(GLFWwindow *window,float deltaTime);
		void camera_protection(Shader *ourShader);
		void camera_transformation(Shader *ourShader);
		
		glm::mat4 GetViewMatrix();
		double getXoverflow();
		double getYoverflow();
		double get3dposX(GLFWwindow* window);
		double get3dposY(GLFWwindow* window);
		double getWidth();
		double getHeight();
		float getDRX();
		float getDRY();
};

#endif
