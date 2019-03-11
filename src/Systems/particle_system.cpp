#include "particle_system.hpp"    

const int MAX_PARTICLES = 250;
const float DELAY_PERIOD = 0.15f;
const vec2 DEFAULT_PARTICLE_SCALE = vec2(50.0f, 50.0f);
static float nextActionTime = DELAY_PERIOD;
static int lastUsedIndex = 0;
vector<shared_ptr<Entity>> ParticleSystem::particleClusters;

const float F_g = 9.8;  // force of gravity

void ParticleSystem::initParticleSystem(EntityManager & manager) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    Entity particle = ParticleFactory::build(vec2(0.0f, 0.0f));
    manager.addEntity(particle); // Particles are on default "inactive" and won't be rendered
  }
  particleClusters = manager.getEntities(manager.getComponentChecker(vector<int>{ComponentType::particle}));
}

void ParticleSystem::emitParticleCluster(EntityManager & manager, vec2 clusterOrigin) {
  for (int i = 0; i < 20; i++) {
    shared_ptr<Entity> particle = particleClusters[findUnusedParticle()];
    ParticleComponent * pComponent = particle->getComponent<ParticleComponent>();
    TransformComponent * tComponent = particle->getComponent<TransformComponent>();
    SpriteComponent *sComponent = particle->getComponent<SpriteComponent>();
    tComponent->position = clusterOrigin;
    sComponent->texture = pComponent->bloodTexture;
    pComponent->type = ParticleType::blood;
    pComponent->active = true; // Now particle will get rendered
  }
}

int ParticleSystem::findUnusedParticle() {
  for (int i = lastUsedIndex; i < (MAX_PARTICLES); i++) {
    ParticleComponent * pComponent = particleClusters[i]->getComponent<ParticleComponent>();
    if (pComponent->active == false) {
      lastUsedIndex = i;
      return i;
    }
  }
  for (int i = 0; i < lastUsedIndex; i++) {
    ParticleComponent * pComponent = particleClusters[i]->getComponent<ParticleComponent>();
    if (pComponent->active == false) {
      lastUsedIndex = i;
      return i;
    }
  }
  lastUsedIndex = 0;
  return 0;
}

void ParticleSystem::emitSmoke(EntityManager & manager, vec2 clusterOrigin) {
  for (int i = 0; i < 5; i++) {
    shared_ptr<Entity> particle = particleClusters[findUnusedParticle()];
    ParticleComponent * pComponent = particle->getComponent<ParticleComponent>();
    TransformComponent * tComponent = particle->getComponent<TransformComponent>();
    SpriteComponent *sComponent = particle->getComponent<SpriteComponent>();
    ColorComponent *cComponent = particle->getComponent<ColorComponent>();
    tComponent->position = clusterOrigin;
    tComponent->size = vec2(110.0f, 120.0f);
    sComponent->texture = pComponent->smokeTexture;
    pComponent->type = ParticleType::smoke;
    pComponent->active = true; // Now, particle will get rendered
  }

}


void ParticleSystem::updateParticles(EntityManager & manager, float dt) {
  vector<shared_ptr<Entity>> particles = manager.getEntities(manager.getComponentChecker(vector<int> {ComponentType::particle}));
  shared_ptr<Entity> home = manager.getEntities(manager.getComponentChecker(vector<int> {ComponentType::home}))[0];
  HealthComponent * hComponent = home->getComponent<HealthComponent>();
  ColorComponent * hcComponent = home->getComponent<ColorComponent>();

  if (nextActionTime < 0 && (hComponent->curHP < (0.5 * hComponent->maxHP))) {
    emitSmoke(manager, vec2(560.f, 710.f));
    hcComponent->RGBA.a = 1.0f;
    nextActionTime = DELAY_PERIOD;
  }
  else {
    nextActionTime -= dt;
  }

  // Handle particles emitted when enemy dies
  for (shared_ptr<Entity> particle : particles) {
    ParticleComponent *pComponent = particle->getComponent<ParticleComponent>();
    ColorComponent *cComponent = particle->getComponent<ColorComponent>();
    TransformComponent *tComponent = particle->getComponent<TransformComponent>();

    if (pComponent->active != true || pComponent->type == ParticleType::nothing) {
      continue;
    }

    pComponent->timer.update(dt);

    float xVelocity, yVelocity = 0.0f;

    if (pComponent->type == ParticleType::blood) {
      xVelocity = cos(pComponent->angle) * pComponent->speed;
      yVelocity = (sin(pComponent->angle) * pComponent->speed) + F_g;
      pComponent->angle += dt;
      cComponent->RGBA.w -= dt / 1.5f;
    }
    else if (pComponent->type == ParticleType::smoke) {
      xVelocity = 25.f * sin(pComponent->timer.elapsedTime * 1.75f * M_PI);
      //xVelocity = cos(pComponent->angle) * (pComponent->speed + (rand() % (20 - 5) + 5));
      yVelocity = sin(pComponent->angle) * (pComponent->speed - (rand() % (41 - 15) + 15)) * (pComponent->timer.getTimeLeft() / pComponent->lifetime);
      cComponent->RGBA.w -= dt * 0.5;
      tComponent->size -= dt * 0.85f;
    }

    tComponent->position += vec2(xVelocity, yVelocity) * (dt * 5.f);

    // Reset particle parameters
    if (pComponent->timer.getTimeLeft() <= 0) {
      resetParticle(cComponent, tComponent, pComponent);
    }
  }
}

void ParticleSystem::resetParticles(EntityManager & manager)
{
  vector<shared_ptr<Entity>> particles = manager.getEntities(manager.getComponentChecker(vector<int> {ComponentType::particle}));
  for (shared_ptr<Entity> particle : particles) {
    ParticleComponent *pComponent = particle->getComponent<ParticleComponent>();
    ColorComponent *cComponent = particle->getComponent<ColorComponent>();
    TransformComponent *tComponent = particle->getComponent<TransformComponent>();
    resetParticle(cComponent, tComponent, pComponent);
  }
}

void ParticleSystem::resetParticle(ColorComponent * cComponent, TransformComponent * tComponent, ParticleComponent * pComponent)
{
  cComponent->RGBA.w = 1.0f; // reset alpha to 1         
  tComponent->size = pComponent->particleScale;
  tComponent->size = DEFAULT_PARTICLE_SCALE;
  pComponent->timer.reset();
  pComponent->type = ParticleType::nothing;
  pComponent->active = false;
}

