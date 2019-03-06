#include "particle_factory.hpp"

const glm::vec2 DEFAULT_SCALE = glm::vec2(50.0f,50.0f);
const glm::vec4 DEFAULT_COLOR = glm::vec4(1.0f,1.0f,1.0f,1.0f);
const float DEFAULT_LIFETIME = 2.0f;
const GLfloat DEFAULT_ROTATION = 0.0f;

Entity ParticleFactory::build(glm::vec2 originPosition) {
    Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
    Texture *texture = new Texture(texture_path("blood.png"), true);  
    SpriteComponent *sprite = new SpriteComponent(program, texture);
    ColorComponent *color = new ColorComponent(DEFAULT_COLOR); 
    TransformComponent *transform = new TransformComponent(originPosition, DEFAULT_SCALE, DEFAULT_ROTATION);
    ParticleComponent *particle = new ParticleComponent(DEFAULT_LIFETIME);

    particle->particleScale = DEFAULT_SCALE;
    particle->angle = randomAngle();
    particle->speed = ((2 * M_PI * rand()) / RAND_MAX) + 0.05;
    
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

// inline float Random()
// {
//     return rand() / (float)RAND_MAX;
// }

// inline float RandRange( float fMin, float fMax )
// {
//     if ( fMin > fMax ) std::swap( fMin, fMax );
//     return ( Random() * ( fMax - fMin ) ) + fMin;
// }

// inline glm::vec3 RandUnitVec()
// {
//     float x = ( Random() * 2.0f ) - 1.0f;
//     float y = ( Random() * 2.0f ) - 1.0f;
//     float z = ( Random() * 2.0f ) - 1.0f;

//     return glm::normalize( glm::vec3(x,y,z) );
// }
