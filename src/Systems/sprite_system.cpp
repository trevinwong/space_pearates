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
		SpriteComponent *spriteComponent = e->getComponent<SpriteComponent>();
		TransformComponent *transformComponent = e->getComponent<TransformComponent>();
		ColorComponent *colorComponent = e->getComponent<ColorComponent>();

		// Use the program attached with the spriteComponent.
		spriteComponent->program->use();

		// Make sure to initialize glm::mat4 to the identity matrix, otherwise matrix transformations will not work.
		glm::mat4 model = glm::mat4(1.0);

		// We want to scale, rotate, then translate.
		// But since matrix operations happen from right to left, we want to code these operations in reverse order.
		model = glm::translate(model, glm::vec3(transformComponent->position, 0.0f));

		// We want to move the origin of rotation to the center of the quad, rotate, then move the origin back.
		model = glm::translate(model, glm::vec3(0.5f * transformComponent->size.x, 0.5f * transformComponent->size.y, 0.0f));
		model = glm::rotate(model, transformComponent->rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * transformComponent->size.x, -0.5f * transformComponent->size.y, 0.0f));

		model = glm::scale(model, glm::vec3(transformComponent->size, 1.0f));

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
		AnimatedComponent *animatedComponent = e->getComponent<AnimatedComponent>();
		PlayerComponent *playerComponent = e->getComponent<PlayerComponent>();

		if (animatedComponent != nullptr) {
			
			if (elapsedTime >= animatedComponent->frameRate) {
				frame = (animatedComponent->currFrame + 1) % animatedComponent->numFrames;
				animatedComponent->updateCurrFrame();
				elapsedTime = 0;
			} 

			// Modify VBO data for animated sprites 
			float spriteWidth = animatedComponent->spriteDims.x;
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

			// get pointer
			void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			// Copy data into memory
			memcpy(ptr, vertices, sizeof(vertices));
			// Tell OpenGL we're done with the pointer
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}
	
		glBindVertexArray(spriteComponent->quadVAO);
		// Draw our sprite.
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Rebind the current VAO to 0 to avoid accidentally modifying our current VAO.
		glBindVertexArray(0);
	}
}
