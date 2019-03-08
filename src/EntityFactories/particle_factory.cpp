#include "particle_factory.hpp"

static const glm::vec2 DEFAULT_SCALE = glm::vec2(50.0f,50.0f);
const glm::vec4 DEFAULT_COLOR = glm::vec4(1.0f,1.0f,1.0f,1.0f);
const float DEFAULT_LIFETIME = 2.0f;

Entity ParticleFactory::build(glm::vec2 originPosition) {
    Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
    Texture *texture = new Texture();  
    SpriteComponent *sprite = new SpriteComponent(program, texture);
    ColorComponent *color = new ColorComponent(DEFAULT_COLOR); 
    TransformComponent *transform = new TransformComponent(originPosition, DEFAULT_SCALE, 0.0f);
    ParticleComponent *particle = new ParticleComponent(DEFAULT_LIFETIME);

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