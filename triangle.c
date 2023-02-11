#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>

#define MAX_SHADER_SZ 1024

void handleResize(GLFWwindow *win, int newW, int newH)
{
	glViewport(0, 0, newW, newH);
}

//Read contents of file into src
//Assume that src is a pointer to a
//string of at least length MAX_SHADER_SZ + 1
//(extra byte for null terminator)
void readShaderCode(const char *path, char *src)
{
	FILE* file = fopen(path, "r");

	if(!file)
	{
		fprintf(stderr, "Failed to open: %s\n", path);
		return;
	}

	int ch, ind = 0;
	while((ch = fgetc(file)) != EOF && ind < MAX_SHADER_SZ) src[ind++] = ch;
	src[ind] = '\0';

	fclose(file);
}

int main(void)
{
	//Attempt to initialize glfw
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to init GLFW!\n");
		return -1;
	}

	//Create window
	GLFWwindow* win = glfwCreateWindow(640, 480, "Triangle Test", NULL, NULL);
	if(!win)
	{
		fprintf(stderr, "Failed to init window!\n");
		glfwTerminate();
		return -1;	
	}
	glfwMakeContextCurrent(win);
	glfwSetWindowSizeCallback(win, handleResize);

	//Load glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to load glad!\n");
		glfwTerminate();
		return -1;
	}

	//Triangle
	float triangle[] = 
	{
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	unsigned int triBuffer;
	glGenBuffers(1, &triBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, triBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);
	glEnableVertexAttribArray(0);

	//Set up shaders
	unsigned int program = glCreateProgram();

	char vert[MAX_SHADER_SZ + 1],
		 frag[MAX_SHADER_SZ + 1];
	readShaderCode("triangle.vert", vert);
	readShaderCode("triangle.frag", frag);

	unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER),
				 fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* vertbegin = &vert[0];
	glShaderSource(vertShader, 1, &vertbegin, NULL); 
	const char* fragbegin = &frag[0];
	glShaderSource(fragShader, 1, &fragbegin, NULL);
	glCompileShader(vertShader);
	glCompileShader(fragShader);
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	glUseProgram(program);

	//Main loop
	while(!glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	
	//Clean up
	glfwTerminate();
}
