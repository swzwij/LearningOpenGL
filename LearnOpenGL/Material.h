#ifndef MATERIAL_H
#define MATERIAL_H

#include "Numerics.h"

class Material
{
public:
	Vec3 ambient;
	Vec3 diffuse;
	Vec3 specular;
	float shininess;

	Material(Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
	}
};

#endif