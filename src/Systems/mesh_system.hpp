#ifndef MESH_SYSTEM_H
#define MESH_SYSTEM_H

#include "Utility/utility.hpp"
#include "Utility/texture.hpp"
#include "Utility/program.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Components/base_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/mesh_component.hpp"
#include "Components/mesh_collision_component.hpp"

class MeshSystem
{
public:
	void updateMeshCollision(EntityManager &entityManager);
	void drawMeshes(EntityManager &entityManager, glm::mat4 projection);	
};

#endif
