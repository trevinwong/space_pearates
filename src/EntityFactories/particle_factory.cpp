#include "particle_factory.hpp"

static const glm::vec2 DEFAULT_SCALE = glm::vec2(50.0f,50.0f);
const glm::vec4 DEFAULT_COLOR = glm::vec4(1.0f,1.0f,1.0f,1.0f);
const float DEFAULT_LIFETIME = 1.5f;

Entity ParticleFactory::build(glm::vec2 originPosition) {
    shared_ptr<Program> program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
    shared_ptr<Texture> texture = make_shared<Texture>();
    shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(program, texture);
    shared_ptr<ColorComponent> color = make_shared<ColorComponent>(DEFAULT_COLOR);
    shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(originPosition, DEFAULT_SCALE, 0.0f);
    shared_ptr<ParticleComponent> particle = make_shared<ParticleComponent>(DEFAULT_LIFETIME);

    particle->active = false;
    particle->particleScale = DEFAULT_SCALE;
    particle->angle = randomAngle();
    particle->speed = ((2 * M_PI * rand()) / RAND_MAX) + 0.05;
    particle->type = ParticleType::nothing;
    
    Entity e;
    e.setComponent<SpriteComponent>(sprite);
    e.setComponent<ColorComponent>(color);
    e.setComponent<TransformComponent>(transform);
    e.setComponent<ParticleComponent>(particle);

    return e;
}

float ParticleFactory::randomAngle() 
{
    float angle = (2 * M_PI * rand()) / RAND_MAX;
    return angle;
}