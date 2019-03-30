#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"
#include "Utility/program.hpp"
#include "Utility/texture.hpp"
#include "triangle.hpp"

class MeshComponent : public BaseComponent
{
public:
	MeshComponent(string meshPath);
	~MeshComponent();
	static const int typeID = ComponentType::mesh;
	inline virtual int getTypeID() const { return typeID; };
	Program *program;
	GLuint  VAO; 
	GLuint 	VBO;
	GLuint  IBO;
  size_t numIndices; // passed to glDrawElements
	vector<Triangle> triangles;
};

#endif
