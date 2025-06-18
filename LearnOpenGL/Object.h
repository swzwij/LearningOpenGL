#ifndef Object_H
#define Object_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"

class Object
{
public:
	virtual void Update(float deltaTime) { }
	virtual void Render(Camera* camera) { }
	virtual void LoadGeometry() { }

	virtual glm::vec3 Position() const { return position; }
	virtual void Position(const glm::vec3& pos) { position = pos; UpdateModelMatrix(); }

	virtual glm::vec3 Rotation() const { return rotation; }
	virtual void Rotation(const glm::vec3& rot) { rotation = rot; UpdateModelMatrix(); }

	virtual glm::vec3 Scale() const { return scale; }
	virtual void Scale(const glm::vec3& scl) { scale = scl; UpdateModelMatrix(); }

protected:
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	Shader* shader = nullptr;
	bool isVisible = true;
	unsigned int vao = 0;
	unsigned int vbo = 0;

private:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

	void UpdateModelMatrix()
	{
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::scale(modelMatrix, scale);
	}
};

#endif