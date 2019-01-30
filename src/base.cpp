#include "base.hpp"

const glm::vec2 BASE_SIZE = glm::vec2(50.f,50.f);
const glm::vec4 BASE_COLOUR = glm::vec4(0.75f,0.75f,0.75f,1.0f);


Base::Base(glm::vec2 posn)
{
    this->position = posn;
    Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
    SpriteComponent *spriteComponent = new SpriteComponent(program, new Texture());
    TransformComponent *transformComponent = new TransformComponent(this->position, BASE_SIZE, 0.0f);
    ColorComponent *colorComponent = new ColorComponent(BASE_COLOUR); 
    this->setComponent<SpriteComponent>(spriteComponent);
    this->setComponent<TransformComponent>(transformComponent);
    this->setComponent<ColorComponent>(colorComponent);
}

Base::~Base()
{
}

glm::vec2 Base::getPosition() const
{
  return this->position;
}

bool Base::isAlive() const
{
    return (this->health > 0);
}
