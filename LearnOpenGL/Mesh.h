#ifndef MESH_H
#define MESH_H

#include "Material.h"

class Mesh
{
public:
	unsigned int vao = 0;
	unsigned int vbo = 0;
	
	Material material;
};

#endif