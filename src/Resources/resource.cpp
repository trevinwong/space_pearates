#include "resource.hpp"

Resource::Resource()
{
  factory = ResourceFactory();
}

Resource::~Resource()
{
}

void Resource::loadResource(glm::vec2 screen, EntityManager& entities) {
  entities.addEntity(factory.build(glm::vec2(screen.x / 2, 50), glm::vec2(20,25)));
}
