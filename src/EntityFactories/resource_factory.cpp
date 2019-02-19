#include "resource_factory.hpp"

ResourceFactory::ResourceFactory()
{
}

ResourceFactory::~ResourceFactory()
{
}

Entity ResourceFactory::build(glm::vec2 position, glm::vec2 scale)
{
    Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
    Texture *texture = new Texture(texture_path("coin.png"), true);
    SpriteComponent *sprite = new SpriteComponent(program, texture);
    TransformComponent *transform = new TransformComponent(position, scale, 0.0f);
    ColorComponent *colour = new ColorComponent(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    ResourceComponent *resource = new ResourceComponent(10.0);
    Entity e;
    e.setComponent<SpriteComponent>(sprite);
    e.setComponent<TransformComponent>(transform);
    e.setComponent<ColorComponent>(colour);
    e.setComponent<ResourceComponent>(resource);
    return e;
}
