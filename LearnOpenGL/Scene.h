#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "lighting/Light.h"

class Scene
{
private:
	std::vector<Object*> objects;
	std::vector<Light*> lights;

public:
	Scene() { };

	void Add(Object* object)
	{
		objects.push_back(object);
	}

	void Add(Light* light)
	{
		lights.push_back(light);
	}

	void Update(float deltaTime)
	{
		for (Object* object : objects)
			object->Update(deltaTime);
	}

	void Render(Camera* camera)
	{
		for (Object* object : objects)
			object->Render(camera);
	}

	void Clear()
	{
		for (Object* object : objects)
			delete object;
		objects.clear();

		for (Light* light : lights)
			delete light;
		lights.clear();
	}
};

#endif