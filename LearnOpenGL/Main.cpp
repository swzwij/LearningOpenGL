#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "Object.h"
#include "ColoredObject.h"
#include "Scene.h"

float deltaTime = 0.;
float lastFrame = 0.;

Shader texturedShaders;
Shader lightShaders;

const int WIDTH = 1000;
const int HEIGHT = 800;

Camera camera = Camera(WIDTH, HEIGHT);

void FramebufferSizeCallBack(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Learning OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -1;

	glViewport(0, 0, WIDTH, HEIGHT);
	
	texturedShaders = Shader("shaders/texturedVertex.vert", "shaders/texturedFragment.frag");
	lightShaders = Shader("shaders/light.vert", "shaders/light.frag");

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallBack);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float lightVertices[] =
	{
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	unsigned int lightVBO, lightVAO;
	glGenBuffers(1, &lightVBO);
	glGenVertexArrays(1, &lightVAO);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);*/

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("images/rancor_pit.png", &width, &height, &nrChannels, 0);
	if (!data) 
	{
		std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
		return -1;
	}
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*GLenum internalFormat = (nrChannels == 4) ? GL_RGBA : GL_RGB;
	GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;*/

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	data = stbi_load("images/rancor_pit.png", &width, &height, &nrChannels, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	glm::vec3 lightPos(0.0f, 0.0f, -5.0f);

	texturedShaders.Use();
	texturedShaders.SetMat4("model", model);
	texturedShaders.SetMat4("view", view);
	texturedShaders.SetMat4("projection", projection);
	texturedShaders.SetVec3("viewPos", camera.position);
	texturedShaders.SetInt("texture3", 2);

	texturedShaders.SetInt("material.diffuse", 0);
	texturedShaders.SetInt("material.specular", 1);
	texturedShaders.SetFloat("material.shininess", 32.0f);

	texturedShaders.SetVec3("light.direction", -0.2f, -1.0f, -0.3f);
	texturedShaders.SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	texturedShaders.SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	texturedShaders.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);
	texturedShaders.SetFloat("light.constant", 1.0f);
	texturedShaders.SetFloat("light.linear", 0.0014f);
	texturedShaders.SetFloat("light.quadratic", 0.0007f);

	lightShaders.Use();
	lightShaders.SetMat4("model", model);
	lightShaders.SetMat4("view", view);
	lightShaders.SetMat4("projection", projection);

	glm::vec3 cubePositions[] = 
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	OBJLoader loader;
	loader.Load("models/rancor_pit.obj");
	int cubeVAO = loader.ToBuffer();

	float fpsTimer = 0.;
	int fpsCount = 0;

	Scene scene;

	ColoredObject* coloredObject = new ColoredObject(glm::vec3(0.35, 0.1, 0.5));
	ColoredObject* coloredObject2 = new ColoredObject(glm::vec3(0.75, 0.35, 0.2));
	coloredObject2->Position(glm::vec3(5.0f, 0.0f, 0.0f));

	scene.Add(coloredObject);
	scene.Add(coloredObject2);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);
	
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		fpsTimer += deltaTime;
		fpsCount++;

		if (fpsTimer >= 1.0f)
		{
			//std::cout << "FPS: " << fpsCount << std::endl;
			fpsCount = 0;
			fpsTimer = 0.0f;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.Update(deltaTime);
		scene.Render(&camera);

		texturedShaders.Use();

		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);
		texturedShaders.SetMat4("view", view);

		const float lightRad = 3.;

		lightPos.x = sin(glfwGetTime()) * lightRad;
		lightPos.z = cos(glfwGetTime()) * lightRad;
        lightPos.y = sin(glfwGetTime()) * lightRad;

		lightPos = camera.position;

		texturedShaders.Use();
		texturedShaders.SetVec3("light.position", lightPos);
		texturedShaders.SetVec3("viewPos", camera.position);

		//glBindVertexArray(lightVAO);
		//lightShaders.Use();
		//lightShaders.SetMat4("view", view);
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//lightShaders.SetMat4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(cubeVAO);

		//texturedShaders.Use();
		//for (unsigned int i = 0; i < 10; i++)
		//{
		//	glm::mat4 model = glm::mat4(1.0f);
		//	model = glm::translate(model, cubePositions[i]);
		//	float angle = 20.0f * i;
		//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	texturedShaders.SetMat4("model", model);

		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		//model = glm::mat4(1.);
		//texturedShaders.SetMat4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, loader.VertexCount());

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void FramebufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	texturedShaders.Use();
	texturedShaders.SetMat4("projection", projection);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	camera.Update(window, deltaTime);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	camera.HandleMouse(window, xpos, ypos);
}