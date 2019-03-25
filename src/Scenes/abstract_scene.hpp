#ifndef ABSTRACT_WORLD_H
#define ABSTRACT_WORLD_H

#include "Utility/utility.hpp"
#include "entity_manager.hpp"

class SceneManager;

class AbstractScene {
public:
  AbstractScene(std::weak_ptr<SceneManager> _sceneManager) : sceneManager(_sceneManager){};

  virtual void processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]) = 0;

  virtual void update(float dt) = 0;

  virtual void draw() = 0;
protected:
  glm::mat4 projection;
  EntityManager entityManager;

  // sceneManager has one world, world has one sceneManager, use weak_ptr to avoid circular ref
  std::weak_ptr<SceneManager> sceneManager;
};

#endif