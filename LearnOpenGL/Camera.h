#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
private:
	const glm::vec3* START_POSITION = new glm::vec3(0., 0., 3.);
	const glm::vec3* START_TARGET = new glm::vec3(0.);

	const float SPEED = 2.;
	const float SENSITIVITY = 0.1f;

	const float FOV = 45.;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 100.0f;

public:
	glm::vec3 position = glm::vec3(0.);
	glm::vec3 front = glm::vec3(0., 0., -1.);
	glm::vec3 up = glm::vec3(0., 1., 0.);

	float yaw = -90.;
	float pitch = 0.;

	Camera(float width, float height)
	{
		WindowWidth = width;
		WindowHeight = height;

		position = *START_POSITION;

		glm::vec3 direction = glm::normalize(position - *START_TARGET);
		glm::vec3 up = glm::vec3(0., 1., 0.);
		glm::vec3 right = glm::normalize(glm::cross(up, direction));

		up = glm::cross(direction, right);
		front = glm::normalize(*START_TARGET - position);
	}

	void Update(GLFWwindow* window, float deltaTime)
	{
		Move(window, deltaTime);
		HandleMouseLock(window);
	}

	void HandleMouse(GLFWwindow* window, double xpos, double ypos)
	{
		if (!_isMouseLocked)
			return;

		HandleMouseLook(window, xpos, ypos);
	}

	glm::mat4 ViewMatrix() const
	{
		return glm::lookAt(position, position + front, up);
	}

	glm::mat4 ProjectionMatrix() const
	{
		return glm::perspective(glm::radians(FOV), WindowWidth / WindowHeight, NEAR_PLANE, FAR_PLANE);
	}

private:
	float WindowWidth = 0;
	float WindowHeight = 0;

	float lastX = WindowWidth / 2.0f;
	float lastY = WindowHeight / 2.0f;

	bool _isMouseInitialized = false;
	bool _isMouseLocked = true;

	void Move(GLFWwindow* window, float deltaTime)
	{
		float speed = SPEED * deltaTime;

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			speed *= 10;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position += speed * front;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position -= speed * front;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position -= glm::normalize(glm::cross(front, up)) * speed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position += glm::normalize(glm::cross(front, up)) * speed;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			position += speed * up;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			position -= speed * up;
	}

	void HandleMouseLock(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			_isMouseLocked = true;
		}

		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			_isMouseLocked = false;
		}
	}

	void HandleMouseLook(GLFWwindow* window, double xpos, double ypos)
	{
		if (!_isMouseInitialized)
		{
			lastX = xpos;
			lastY = ypos;
			_isMouseInitialized = true;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		xoffset *= SENSITIVITY;
		yoffset *= SENSITIVITY;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;

		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(direction);
	}
};

#endif