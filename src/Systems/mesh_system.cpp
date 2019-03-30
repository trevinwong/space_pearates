#include "mesh_system.hpp"

void replace(vec2 &orig, vec2 &neu)
{
  if (neu.x > orig.x) {
    orig.x = neu.x;
  }
  if (neu.y > orig.y) {
    orig.y = neu.y;
  }
}

void replace2(vec2 &orig, vec2 &neu)
{
  if (neu.x < orig.x) {
    orig.x = neu.x;
  }
  if (neu.y < orig.y) {
    orig.y = neu.y;
  }
}

void MeshSystem::updateMeshCollision(EntityManager &entityManager)
{
  vector<shared_ptr<Entity>> filtered_entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::mesh, ComponentType::transform, ComponentType::color}));

  for (shared_ptr<Entity> e : filtered_entities) {
    shared_ptr<MeshComponent> meshComponent = e->getComponent<MeshComponent>();
    shared_ptr<TransformComponent> transformComponent = e->getComponent<TransformComponent>();
    shared_ptr<ColorComponent> colorComponent = e->getComponent<ColorComponent>();

    glm::mat4 model = glm::mat4(1.0);

    model = glm::translate(model, vec3(transformComponent->position, 0.0f));

    model = glm::translate(model, vec3(0.5f * transformComponent->size.x, 0.5f * transformComponent->size.y, 0.0f));
    model = glm::rotate(model, transformComponent->rotation, vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, vec3(-0.5f * transformComponent->size.x, -0.5f * transformComponent->size.y, 0.0f));

    model = glm::scale(model, vec3(transformComponent->size, 1.0f));

		vec2 bottom_right = vec2(0, 0);
		vec2 top_left = vec2(1e10, 1e10);

		for (Triangle triangle : meshComponent->triangles) {
			triangle.pt1 = (model * vec4(triangle.pt1.x, triangle.pt1.y, 0.0, 1.0));
			triangle.pt2 = (model * vec4(triangle.pt2.x, triangle.pt2.y, 0.0, 1.0));
			triangle.pt3 = (model * vec4(triangle.pt3.x, triangle.pt3.y, 0.0, 1.0));

			replace(bottom_right, triangle.pt1);
			replace(bottom_right, triangle.pt2);
			replace(bottom_right, triangle.pt3);
		}

		for (Triangle triangle : meshComponent->triangles) {
			triangle.pt1 = (model * vec4(triangle.pt1.x, triangle.pt1.y, 0.0, 1.0));
			triangle.pt2 = (model * vec4(triangle.pt2.x, triangle.pt2.y, 0.0, 1.0));
			triangle.pt3 = (model * vec4(triangle.pt3.x, triangle.pt3.y, 0.0, 1.0));

			replace2(top_left, triangle.pt1);
			replace2(top_left, triangle.pt2);
			replace2(top_left, triangle.pt3);
		}

		shared_ptr<MeshCollisionComponent> meshCollision = e->getComponent<MeshCollisionComponent>();
		meshCollision->aabb_position = top_left;
		meshCollision->aabb_size = bottom_right - top_left;
	}

}

void MeshSystem::drawMeshes(EntityManager &entityManager, glm::mat4 projection)
{
  vector<shared_ptr<Entity>> filtered_entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::mesh, ComponentType::transform, ComponentType::color}));

  for (shared_ptr<Entity> e : filtered_entities) {
    shared_ptr<MeshComponent> meshComponent = e->getComponent<MeshComponent>();
    shared_ptr<TransformComponent> transformComponent = e->getComponent<TransformComponent>();
    shared_ptr<ColorComponent> colorComponent = e->getComponent<ColorComponent>();

    meshComponent->program->use();
    glm::mat4 model = glm::mat4(1.0);

    model = glm::translate(model, vec3(transformComponent->position, 0.0f));

    model = glm::translate(model, vec3(0.5f * transformComponent->size.x, 0.5f * transformComponent->size.y, 0.0f));
    model = glm::rotate(model, transformComponent->rotation, vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, vec3(-0.5f * transformComponent->size.x, -0.5f * transformComponent->size.y, 0.0f));

    model = glm::scale(model, vec3(transformComponent->size, 1.0f));


    meshComponent->program->setMat4("model", model);
    meshComponent->program->setMat4("projection", projection);
    meshComponent->program->setVec4("meshColor", colorComponent->RGBA);

    glBindVertexArray(meshComponent->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, meshComponent->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshComponent->IBO);
    // Draw our mesh.
		glDrawElements(GL_TRIANGLES,(GLsizei)meshComponent->numIndices, GL_UNSIGNED_SHORT, nullptr);
    // Rebind the current VAO to 0 to avoid accidentally modifying our current VAO.
    glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		/*
		vector<vec2> triangle_points;
    for (Triangle triangle : meshComponent->triangles) {
      glm::mat4 model = glm::mat4(1.0);
      model = glm::translate(model, vec3(transformComponent->position, 0.0f));

      model = glm::translate(model, vec3(0.5f * transformComponent->size.x, 0.5f * transformComponent->size.y, 0.0f));
      model = glm::rotate(model, transformComponent->rotation, vec3(0.0f, 0.0f, 1.0f));
      model = glm::translate(model, vec3(-0.5f * transformComponent->size.x, -0.5f * transformComponent->size.y, 0.0f));

      model = glm::scale(model, vec3(transformComponent->size, 1.0f));

      // Transform triangle by model matrix.
			triangle.pt1 = (model * vec4(triangle.pt1.x, triangle.pt1.y, 0.0, 1.0));
      triangle.pt2 = (model * vec4(triangle.pt2.x, triangle.pt2.y, 0.0, 1.0));
      triangle.pt3 = (model * vec4(triangle.pt3.x, triangle.pt3.y, 0.0, 1.0));

      triangle_points.push_back(triangle.pt1);
      triangle_points.push_back(triangle.pt2);
      triangle_points.push_back(triangle.pt3);
    }
      HUD::getInstance().intersections = triangle_points;

			*/
  }
}
