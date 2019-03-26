#include "render_to_texture_system.hpp"

RenderToTextureSystem::~RenderToTextureSystem() {
  glDeleteVertexArrays(1, &quadVAO);
  glDeleteBuffers(1, &VBO);
  if (renderedTexture) glDeleteTextures(1, &renderedTexture);
  if (FramebufferName) glDeleteFramebuffers(1, &FramebufferName);
  if (depthrenderbuffer) glDeleteRenderbuffers(1, &depthrenderbuffer);
}

bool RenderToTextureSystem::initWaterEffect()
{
  waterProgram = make_shared<Program>(shader_path("water_tower_range_effect.vert"), shader_path("water_tower_range_effect.frag"));

	static const GLfloat vertices[] = {
    // Pos        // Tex
    1.0f, 1.0f,   1.5f, -0.5f,
    -1.0f, -1.0f, -0.5f, 1.5f,
    -1.0f, 1.0f,  -0.5f, -0.5f,

    1.0f, 1.0f,   1.5f, -0.5f,
    -1.0f, -1.0f, -0.5f, 1.5f,
    1.0f, -1.0f,  1.5f, 1.5f
	};

  // Generate a VAO.
  glGenVertexArrays(1, &this->quadVAO);
  // Generate a VBO.
  glGenBuffers(1, &VBO);
  // Bind our current VBO.
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Move the vertices we defined above into our VBO.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // Bind our current VAO, which will remember any vertex attribute related calls.
  glBindVertexArray(this->quadVAO);
  // Enable the first "in" variable in our vertex shader - make sure that this corresponds to the right variable!
  // layout (location = 0) in shaders
  glEnableVertexAttribArray(0);
  //                   (index, size, type, isNormalized, stride, pointer to offset)
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  // layout (location = 1)
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

  // Re-bind the current VBO and VAO to 0 to avoid accidentally modifying the ones we just configured here.
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return prepareWaterEffect();
}

bool RenderToTextureSystem::prepareWaterEffect() {
  // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
  glGenFramebuffers(1, &FramebufferName);
  // "Bind" the newly created texture : all future texture functions will modify this texture
  glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

  // The texture we're going to render to
  glGenTextures(1, &renderedTexture); 
  glBindTexture(GL_TEXTURE_2D, renderedTexture);

  // Give an empty image to OpenGL ( the last "0" )
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
  // Poor filtering. Needed !
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // Unbind texture (for safety).
  glBindTexture(GL_TEXTURE_2D, 0);

  // The depth buffer - optional
  glGenRenderbuffers(1, &depthrenderbuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

  // Set "renderedTexture" as our colour attachement #0
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

  // Set the list of draw buffers.
  GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
  glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    return false;
  }

  return true;
}

bool RenderToTextureSystem::beforeRenderWaterEffect() {

  glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

  const float clear_color[3] = { 0.3f, 0.3f, 0.8f };
  glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0);
  glClearDepth(1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    return false;
  }

  return true;
}

void RenderToTextureSystem::drawWaterEffect(EntityManager entityManager, glm::mat3 projection) {
  // Render to the screen
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // Render on the whole framebuffer, complete from the lower left corner to the upper right

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, renderedTexture);

  // Use the program attached with the spriteComponent.
  waterProgram->use();

  // Make sure to initialize glm::mat4 to the identity matrix, otherwise matrix transformations will not work.
  glm::mat4 model = glm::mat4(1.0);

  // We want to scale, rotate, then translate.
  // But since matrix operations happen from right to left, we want to code these operations in reverse order.
  model = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));
  // size
  vec2 size = vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
  model = glm::scale(model, vec3(size, 1.0f));

  // Uniform values
  waterProgram->setMat4("model", model);
  waterProgram->setMat4("projection", projection);
  waterProgram->setVec4("spriteColor", glm::vec4(1.0, 1.0, 1.0, 1.0));
  waterProgram->setFloat("time", (float)(glfwGetTime() * 10.0f));

  vector<glm::vec3> towerRangeDataArray = getWaterTowerPosAndRange(entityManager);
  //vector<glm::vec3> towerRangeDataArray = {vec3(800, 100, 200)};
  waterProgram->setVec3Array("towerRangeData", towerRangeDataArray);
  waterProgram->setInt("towerRangeDataSize", towerRangeDataArray.size());

  waterProgram->setInt("image", 0);

  // bind VAO to the texture
  glBindVertexArray(quadVAO);
  // Draw our sprite.
  glDrawArrays(GL_TRIANGLES, 0, 6);
  // Rebind the current VAO to 0 to avoid accidentally modifying our current VAO.
  glBindVertexArray(0);
}

vector<vec3> RenderToTextureSystem::getWaterTowerPosAndRange(EntityManager entityManager)
{
  vector<vec3> result;

  vector<shared_ptr<Entity>> towerEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::attack_tower}));

  if (towerEntities.size() == 0) return result;

  for (shared_ptr<Entity> towerEntity : towerEntities) {
    shared_ptr<TowerAttackComponent> towerAttackComponent = towerEntity->getComponent<TowerAttackComponent>();
    shared_ptr<TransformComponent> transformComponent = towerEntity->getComponent<TransformComponent>();

    if (transformComponent == nullptr || towerAttackComponent == nullptr) continue;

    // only water tower has this effect
    if(towerAttackComponent->getTowerType() != TowerTypeID::water_tower) continue;

    // compute firePoint pos
    vec2 towerLeftTopPosition = transformComponent->position;
    vec2 towerSize = transformComponent->size;
    vec2 towerCenterPosition = towerLeftTopPosition + towerSize * 0.5f;
    vec2 relativeFirePosition = towerAttackComponent->relativeFirePosition;
    vec2 firePointPosition(towerCenterPosition + towerSize * relativeFirePosition);
    // get fire range
    float fireRange = towerAttackComponent->getAttackRange();

    result.push_back(vec3(firePointPosition, fireRange));
  }

  return result;
}