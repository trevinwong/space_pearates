#include "sprite_system.hpp"

void SpriteSystem::updateElapsedTime(float dt) {
  elapsedTime += dt;
}

float SpriteSystem::getElapsedTime() {
  return elapsedTime;
}

void SpriteSystem::drawSprites(EntityManager &entityManager, glm::mat4 projection)
{
  vector<shared_ptr<Entity>> filtered_entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::sprite, ComponentType::transform, ComponentType::color}));

  for (shared_ptr<Entity> e : filtered_entities) {
    shared_ptr<SpriteComponent> spriteComponent = e->getComponent<SpriteComponent>();
    shared_ptr<TransformComponent> transformComponent = e->getComponent<TransformComponent>();
    shared_ptr<ColorComponent> colorComponent = e->getComponent<ColorComponent>();
    shared_ptr<ParticleComponent> particleComponent = e->getComponent<ParticleComponent>();

    if (particleComponent != nullptr) {
      if (particleComponent->active == false) {
        continue;
      }
    }

    // Use the program attached with the spriteComponent.
    spriteComponent->program->use();

    // Make sure to initialize glm::mat4 to the identity matrix, otherwise matrix transformations will not work.
    glm::mat4 model = glm::mat4(1.0);

    // We want to scale, rotate, then translate.
    // But since matrix operations happen from right to left, we want to code these operations in reverse order.
    model = glm::translate(model, vec3(transformComponent->position, 0.0f));

    // We want to move the origin of rotation to the center of the quad, rotate, then move the origin back.
    model = glm::translate(model, vec3(0.5f * transformComponent->size.x, 0.5f * transformComponent->size.y, 0.0f));
    model = glm::rotate(model, transformComponent->rotation, vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, vec3(-0.5f * transformComponent->size.x, -0.5f * transformComponent->size.y, 0.0f));

    model = glm::scale(model, vec3(transformComponent->size, 1.0f));

    spriteComponent->program->setMat4("model", model);
    spriteComponent->program->setMat4("projection", projection);
    spriteComponent->program->setVec4("spriteColor", colorComponent->RGBA);

    glBindBuffer(GL_ARRAY_BUFFER, spriteComponent->quadVAO);

    // Activate texture unit 0.
    // We can have multiple texture units to use as uniforms in our shader, but we only need 1.
    glActiveTexture(GL_TEXTURE0);

    // Bind our texture so we can render it over the quad of our sprite.
    spriteComponent->texture->bind();

    // Check if sprite is animated
    shared_ptr<AnimatedComponent> animatedComponent = e->getComponent<AnimatedComponent>();

    if (animatedComponent != nullptr) {

      if (elapsedTime >= animatedComponent->frameRate) {
        frame = (animatedComponent->currFrame + 1) % animatedComponent->numFrames;
        animatedComponent->updateCurrFrame();
        elapsedTime = 0;
      }

      // Modify VBO data for animated sprites
      float spriteWidth = (transformComponent->size.x / animatedComponent->numFrames) / transformComponent->size.x;
      float spriteEndX = spriteWidth * frame;
      float spriteStartX = spriteEndX - spriteWidth;

      GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, spriteStartX, 1.0f,
        1.0f, 0.0f, spriteEndX, 0.0f,
        0.0f, 0.0f, spriteStartX, 0.0f,

        0.0f, 1.0f, spriteStartX, 1.0f,
        1.0f, 1.0f, spriteEndX, 1.0f,
        1.0f, 0.0f, spriteEndX, 0.0f
      };
      // change exists vertices by use spriteComponent->quadVAO
      glBindBuffer(GL_ARRAY_BUFFER, spriteComponent->VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      glBindVertexArray(spriteComponent->quadVAO);
      // Enable the first "in" variable in our vertex shader - make sure that this corresponds to the right variable!
      // i.e. layout (location = 0) in shaders
      glEnableVertexAttribArray(0);
      //                   (index, size, type, isNormalized, stride, pointer to offset)
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
      // layout (location = 1)
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

      // Re-bind the current VBO and VAO to 0 to avoid accidentally modifying the ones we just configured here.
      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(spriteComponent->quadVAO);
    // Draw our sprite.
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Rebind the current VAO to 0 to avoid accidentally modifying our current VAO.
    glBindVertexArray(0);
  }
}
