#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <iostream>
#include <learnopengl/model.h>
#include <learnopengl/editor.h>
#include <learnopengl/editor.cpp>
#include <learnopengl/camera.h>
#include <learnopengl/camera.cpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	cout << "------------THIS IS A EDITOR DEMO--------------- " << endl;
	cout << "------------ COMANDS: ---------------------------" << endl;
	cout << "PRESS S FOR SAVE YOUR MAP " << endl;
	cout << "PRESS X FOR CHANGE THE CURRENT MODEL " << endl;
	cout << "-------- THE PROGRAM HAS INITIALIZED ------------" << endl;
	cout << "PUT A FILE NAME: " << endl;
	string name;
	cin >> name;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
	glEnable(GL_DEPTH_TEST);
    Camera camara(SCR_WIDTH,SCR_HEIGHT);

	Shader modelshader("1.model_loading.vs", "1.model_loading.fs");

	Shader ourShader("7.3.camera.vs", "7.3.camera.fs");

    Editor editor(name+".rohmap");
	
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*editor.getVerticesSize(), editor.getVerticesArray(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	
	glfwSetCursorPos(window,SCR_WIDTH/2,SCR_HEIGHT/2);

    while (!glfwWindowShouldClose(window))
    {
    	float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();
		camara.camera_protection(&ourShader);
		camara.camera_transformation(&ourShader);
		glm::mat4 model = glm::mat4(1.0f);
		ourShader.setMat4("model", model);
        glBindVertexArray(VAO); 
        glDrawElements(GL_LINE_STRIP,editor.getIndicesSize(), GL_UNSIGNED_INT,editor.getIndicesArray());
		

		camara.camera_mouse_callback(window,deltaTime);
		modelshader.use();
 		editor.use(window,&camara,&modelshader);

		//glBindVertexArray(0);

        glfwSwapBuffers(window);
		glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

