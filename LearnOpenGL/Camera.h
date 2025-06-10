#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	glm::vec3 position = glm::vec3(0.);
	glm::vec3 front = glm::vec3(0., 0., -1.);
	glm::vec3 up = glm::vec3(0., 1., 0.);

	float yaw = -90.;
	float pitch = 0.;

	Camera() { }

	Camera(const glm::vec3* newPosition, const glm::vec3* target)
	{
		position = *newPosition;

		glm::vec3 direction = glm::normalize(position - *target);
		glm::vec3 up = glm::vec3(0., 1., 0.);
		glm::vec3 right = glm::normalize(glm::cross(up, direction));

		up = glm::cross(direction, right);
		front = glm::normalize(*target - position);
	}

	void Update(GLFWwindow* window, float deltaTime)
	{
		Move(window, deltaTime);
	}

	void Look(GLFWwindow* window, double xpos, double ypos)
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

private:
	const float SPEED = 2.;
	const float SENSITIVITY = 0.1f;

	float lastX = 1000. / 2.0f;
	float lastY = 800. / 2.0f;

	bool _isMouseInitialized = false;

	void Move(GLFWwindow* window, float deltaTime)
	{
		float speed = SPEED * deltaTime;

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
};

#endif