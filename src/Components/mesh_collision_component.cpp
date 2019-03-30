#include "mesh_collision_component.hpp"

MeshCollisionComponent::MeshCollisionComponent(vec2 _position, vec2 _size, GLfloat _rotation, shared_ptr<MeshComponent> _mesh) :
	CollisionComponent(_position, _size, _rotation), mesh(_mesh)
{
}

MeshCollisionComponent::MeshCollisionComponent(vec2 _position, float _scale, GLfloat _rotation, shared_ptr<MeshComponent> _mesh) :
  CollisionComponent(_position, _scale, _rotation), mesh(_mesh)
{
}


bool MeshCollisionComponent::isCollidingWith(CollisionComponent &other)
{
	bool overlapX = aabb_position.x + aabb_size.x >= other.position.x
		&& other.position.x + other.size.x >= aabb_position.x;

	bool overlapY = aabb_position.y + aabb_size.y >= other.position.y
	&& other.position.y + other.size.y >= aabb_position.y;

	if (overlapX && overlapY) {
		for (Triangle triangle : mesh->triangles) {

			glm::mat4 model = glm::mat4(1.0);

			model = glm::translate(model, vec3(position, 0.0f));

			model = glm::translate(model, vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
			model = glm::rotate(model, rotation, vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

			model = glm::scale(model, vec3(size, 1.0f));

			// Transform triangle by model matrix.
			triangle.pt1 = (model * vec4(triangle.pt1.x, triangle.pt1.y, 0.0, 1.0));
			triangle.pt2 = (model * vec4(triangle.pt2.x, triangle.pt2.y, 0.0, 1.0));
			triangle.pt3 = (model * vec4(triangle.pt3.x, triangle.pt3.y, 0.0, 1.0));
	
			vec2 top_left_pt = {other.position.x, other.position.y};
      vec2 top_right_pt = {other.position.x + other.size.x, other.position.y};
      vec2 bottom_left_pt = {other.position.x, other.position.y + other.size.y};
      vec2 bottom_right_pt = {other.position.x + other.size.x, other.position.y + other.size.y};

      Line top_edge(top_left_pt, top_right_pt);
      Line bottom_edge(bottom_left_pt, bottom_right_pt);
      Line left_edge(top_left_pt, bottom_left_pt);
      Line right_edge(top_right_pt, bottom_right_pt);
			
			if (triangle.isIntersectingWithLine(top_edge) ||
					triangle.isIntersectingWithLine(bottom_edge) ||
					triangle.isIntersectingWithLine(left_edge) ||
					triangle.isIntersectingWithLine(right_edge)) {
					return true;
			}
		}
	}

	return false;
}
