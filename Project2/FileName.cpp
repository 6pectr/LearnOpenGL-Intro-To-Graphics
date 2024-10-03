#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/* 
using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"  // Position attribute
"layout (location = 1) in vec4 aColor;\n" // Color attribute
"out vec4 verColor;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"    gl_Position = transform * vec4(aPos, 1.0);\n"
"    verColor = aColor;\n"
"}";

const char* fragmentShaderSource = "#version 330 core\n"
"precision mediump float;\n"
"in vec4 verColor;\n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"    FragColor = verColor; \n"
"}";


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//x    y     z
	float positions[] = {
		0.5f, -0.5f, 0.0f,   
	   -0.5f, -0.5f, 0.0f,   
	    0.0f,  0.5f, 0.0f    
	};

	float colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,  // Red
		0.0f, 1.0f, 0.0f, 1.0f,  // Green
		0.0f, 0.0f, 1.0f, 1.0f  // Blue
	};


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	unsigned int VBOs[2];
	unsigned int VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBOs);
	glBindVertexArray(VAO);

	// First VBO for vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Location 0 for aPos, 3 floats for vertex (x,y,z), 3 floats per vertex (size memory).
	glEnableVertexAttribArray(0); // Location 0 for aPos

	// Second VBO for vertex colors
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // Location 1 for aColor from my VertexShader, 4 floats for vertex (r,g,b,a), 4 floats per vertex (size memory).
	glEnableVertexAttribArray(1); // Location 1 for aColor

	// Unbind the VAO
	glBindVertexArray(0);
	                                                                                                 

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timevalue = glfwGetTime();
		float redvalue = (sin(timevalue) / 2.0f) + 0.5f; 
		float greenvalue = (sin(timevalue) / 1.5f) + 0.5f;
		float bluevalue = (sin(timevalue) / 1.0f) + 0.5f;

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 1, &redvalue);
		glBufferSubData(GL_ARRAY_BUFFER, 20, sizeof(float) * 1, &greenvalue);
		glBufferSubData(GL_ARRAY_BUFFER, 40, sizeof(float) * 1, &bluevalue);
		/* 
		float positions[] = {
			0.5f, -0.5f, 0.0f, // 0  , 4  , 8  (x)
		   -0.5f, -0.5f, 0.0f, // 12 , 16 , 20 (y)
			0.0f,  0.5f, 0.0f  // 24 , 28 , 32 (z)
		};
		*/
		/*
		float angle = sin(timevalue) * (2 * 3.14);;

		float RotationmatrixY[] = {
			cos(angle), 0.0f, sin(angle),
			0.0f, 1.0f, 0.0f,
			-sin(angle), 0.0f, cos(angle)
		};
		float RotationmatrixZ[] = {
			cos(angle), -sin(angle), 0.0f,
			sin(angle), cos(angle), 0.0f,
			0.0f, 0.0f, 1.0f
		};
		float RotationmatrixX[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, cos(angle), -sin(angle),
			0.0f, sin(angle), cos(angle)
		};

		// MAKE PYRAMID ROTATION xD

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3, &RotationmatrixY);
		glBufferSubData(GL_ARRAY_BUFFER, 8, sizeof(float) * 3, &RotationmatrixX);
		glBufferSubData(GL_ARRAY_BUFFER, 20, sizeof(float) * 3, &RotationmatrixZ);




		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "aColor");

		glUseProgram(shaderProgram);


		//glUniform4f(vertexColorLocation, redvalue, 0.0f, 0.0f, 1.0f); 

		int m = glGetUniformLocation(shaderProgram, "transform");

		float viewmatrix[] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 
		};

		glUniformMatrix4fv(m, 1, GL_FALSE, viewmatrix);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
		glBindVertexArray(0);



		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
*/