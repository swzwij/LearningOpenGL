#ifndef SCENE_H
#define SCENE_H

#include "Object.h"

class Scene
{
private:
	std::vector<Object*> objects;
public:
	Scene() { };

	void Add(Object* object)
	{
		objects.push_back(object);
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
	}
};

#endif