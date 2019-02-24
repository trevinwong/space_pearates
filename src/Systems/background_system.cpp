#include "background_system.hpp"

void BackgroundSystem::update(EntityManager & entityManager)
{
  vector<shared_ptr<Entity>> playerEntities = 
    entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player}));
  vector<shared_ptr<Entity>> bgEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::background_sprite}));
  if(playerEntities.size() == 0 || bgEntities.size() == 0) return;

  TransformComponent* playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();
  TransformComponent* bgTransformComponent = bgEntities[0]->getComponent<TransformComponent>();
  BackgroundSpriteComponent* bgSpriteComponent = bgEntities[0]->getComponent<BackgroundSpriteComponent>();
  if(playerTransformComponent == nullptr || bgTransformComponent == nullptr || bgSpriteComponent == nullptr) return;

  vec2 positionOffset = bgSpriteComponent->positionOffset;
  vec2 playerPosition = playerTransformComponent->position;

  bgTransformComponent->position = positionOffset - playerPosition * 0.2f;

}

void BackgroundSystem::render(EntityManager & entityManager, glm::mat4 projection)
{
  vector<shared_ptr<Entity>> entities = 
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::background_sprite}));

  for (shared_ptr<Entity> e : entities) {
    BackgroundSpriteComponent *spriteComponent = e->getComponent<BackgroundSpriteComponent>();
    TransformComponent *transformComponent = e->getComponent<TransformComponent>();
    ColorComponent *colorComponent = e->getComponent<ColorComponent>();
    if(spriteComponent == nullptr || transformComponent == nullptr || colorComponent == nullptr) continue;

    // Use the program attached with the spriteComponent.
    spriteComponent->program->use();

    // Make sure to initialize glm::mat4 to the identity matrix, otherwise matrix transformations will not work.
    glm::mat4 model = glm::mat4(1.0);

    // We want to scale, rotate, then translate.
    // But since matrix operations happen from right to left, we want to code these operations in reverse order.
    model = glm::translate(model, vec3(transformComponent->position, 0.0f));

    // We want to move the origin of rotation to the center of the quad, rotate, then move the origin back.
    //model = glm::translate(model, vec3(0.5f * transformComponent->size.x, 0.5f * transformComponent->size.y, 0.0f));
    //model = glm::rotate(model, transformComponent->rotation, vec3(0.0f, 0.0f, 1.0f));
    //model = glm::translate(model, vec3(-0.5f * transformComponent->size.x, -0.5f * transformComponent->size.y, 0.0f));

    model = glm::scale(model, vec3(transformComponent->size, 1.0f));

    spriteComponent->program->setMat4("model", model);
    spriteComponent->program->setMat4("projection", projection);
    spriteComponent->program->setVec4("spriteColor", colorComponent->RGBA);

    // Activate texture unit 0.
    // We can have multiple texture units to use as uniforms in our shader, but we only need 1.
    glActiveTexture(GL_TEXTURE0);
    // Bind our texture so we can render it over the quad of our sprite.
    spriteComponent->texture->bind();

    // Bind our VAO which contains the quad VBO we defined and our definitions for its coordinates and texture coordinates.
    glBindVertexArray(spriteComponent->quadVAO);
    // Draw our sprite.
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Rebind the current VAO to 0 to avoid accidentally modifying our current VAO.
    glBindVertexArray(0);
  }
}
