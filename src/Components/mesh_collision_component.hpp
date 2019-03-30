#ifndef MESH_COLLISION_COMPONENT_H
#define MESH_COLLISION_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"
#include "collision_component.hpp"
#include "mesh_component.hpp"
#include "entity.hpp"
#include "triangle.hpp"
#include "hud.hpp"

class MeshCollisionComponent : public CollisionComponent
{
public:
	shared_ptr<MeshComponent> mesh;
  MeshCollisionComponent(vec2 _position, vec2 _size, GLfloat _rotation, shared_ptr<MeshComponent> _mesh);
  MeshCollisionComponent(vec2 _position, float _scale, GLfloat _rotation, shared_ptr<MeshComponent> _mesh);
	glm::mat4 projection;
	vec2 aabb_position;
	vec2 aabb_size;
	virtual bool isCollidingWith(CollisionComponent &other);
	virtual int getCollisionType() { return CollisionTypeID::mesh_collision; };
};

#endif
