#include "billboard_system.hpp"

BillboardSystem::BillboardSystem()
{
}

BillboardSystem::~BillboardSystem()
{
}

void BillboardSystem::drawBillboards(EntityManager & entityManager, glm::mat4 projection)
{
  vector<shared_ptr<Entity>> filtered_entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {
    ComponentType::transform, ComponentType::health
  }));

  for (shared_ptr<Entity> e : filtered_entities) {
    TransformComponent *transform = e->getComponent<TransformComponent>();
    HealthComponent *health = e->getComponent<HealthComponent>();

    // Use the program attached with the spriteComponent.
    health->program->use();

    // Make sure to initialize glm::mat4 to the identity matrix, otherwise matrix transformations will not work.
    glm::mat4 model = glm::mat4(1.0);

    // Calculate health bar parameters: if sprite is large use its width, else the default width
    float defaultWidth = 50.0f;
    bool useDefaultWidth = transform->size.x < defaultWidth;

    float barWidth = useDefaultWidth ? defaultWidth : transform->size.x;
    float barHeight = 3.5f;
    float xOffset = useDefaultWidth ? -defaultWidth/2 + transform->size.x/2 : 0.0f;
    float yOffset = -10.0f;
    glm::vec2 barOffset = glm::vec2(xOffset, yOffset);

    // We want to scale, rotate, then translate.
    // But since matrix operations happen from right to left, we want to code these operations in reverse order.
    model = glm::translate(model, glm::vec3(transform->position + barOffset, 0.0f));

    // We want to move the origin of rotation to the center of the quad, rotate, then move the origin back.
    model = glm::translate(model, glm::vec3(0.5f * transform->size.x, 0.5f * transform->size.y, 0.0f));
    model = glm::rotate(model, transform->rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * transform->size.x, -0.5f * transform->size.y, 0.0f));

    model = glm::scale(model, glm::vec3(barWidth, barHeight, 1.0f));

    health->program->setMat4("model", model);
    health->program->setMat4("projection", projection);
    health->program->setVec4("healthBarColor", glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));

    // Bind our VAO which contains the quad VBO we defined and our definitions for its coordinates.
    glBindVertexArray(health->quadVAO);
    // Draw health bar.
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Rebind the current VAO to 0 to avoid accidentally modifying our current VAO.
    glBindVertexArray(0);
  }
}
