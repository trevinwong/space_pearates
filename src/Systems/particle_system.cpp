#include "particle_system.hpp"    

const int MAX_PARTICLES = 275;
const float DELAY_PERIOD = 0.175f;
const float F_g = 9.8;  // force of gravity
const vec2 DEFAULT_PARTICLE_SCALE = vec2(57.0f, 57.0f);
static float nextActionTime = DELAY_PERIOD;
static int lastUsedIndex = 0;
vector<shared_ptr<Entity>> ParticleSystem::particleClusters;

void ParticleSystem::initParticleSystem(EntityManager & manager) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    Entity particle = ParticleFactory::build(vec2(0.0f, 0.0f));
    manager.addEntity(particle); // Particles are on default "inactive" and won't be rendered
  }
  particleClusters = manager.getEntities(manager.getComponentChecker(vector<int>{ComponentType::particle}));
}

void ParticleSystem::emitParticleCluster(EntityManager & manager, vec2 clusterOrigin) {
  for (int i = 0; i < 10; i++) {
    shared_ptr<Entity> particle = particleClusters[findUnusedParticle()];
    shared_ptr<ParticleComponent> pComponent = particle->getComponent<ParticleComponent>();
    shared_ptr<TransformComponent> tComponent = particle->getComponent<TransformComponent>();
    shared_ptr<SpriteComponent> sComponent = particle->getComponent<SpriteComponent>();
    tComponent->position = clusterOrigin;
    sComponent->texture = pComponent->bloodTexture;
    pComponent->type = ParticleType::blood;
    pComponent->active = true; // Now particle will get rendered
  }
}

int ParticleSystem::findUnusedParticle() {
  for (int i = lastUsedIndex; i < (MAX_PARTICLES); i++) {
    shared_ptr<ParticleComponent> pComponent = particleClusters[i]->getComponent<ParticleComponent>();
    if (pComponent->active == false) {
      lastUsedIndex = i;
      return i;
    }
  }
  for (int i = 0; i < lastUsedIndex; i++) {
    shared_ptr<ParticleComponent> pComponent = particleClusters[i]->getComponent<ParticleComponent>();
    if (pComponent->active == false) {
      lastUsedIndex = i;
      return i;
    }
  }
  lastUsedIndex = 0;
  return 0;
}

void ParticleSystem::emitSmoke(EntityManager & manager, vec2 clusterOrigin) {
  for (int i = 0; i < 15; i++) {
    shared_ptr<Entity> particle = particleClusters[findUnusedParticle()];
    shared_ptr<ParticleComponent> pComponent = particle->getComponent<ParticleComponent>();
    shared_ptr<TransformComponent> tComponent = particle->getComponent<TransformComponent>();
    shared_ptr<SpriteComponent> sComponent = particle->getComponent<SpriteComponent>();
    shared_ptr<ColorComponent> cComponent = particle->getComponent<ColorComponent>();
    tComponent->position = clusterOrigin;
    tComponent->size = vec2(16.f, 16.f);
    sComponent->texture = pComponent->smokeTexture;
    pComponent->type = ParticleType::smoke;
    pComponent->active = true; // Now, particle will get rendered
  }
}

void ParticleSystem::emitSparkle(EntityManager & manager, vec2 clusterOrigin) {
	for (int i = 0; i < 15; i++) {
		shared_ptr<Entity> particle = particleClusters[findUnusedParticle()];
		shared_ptr<ParticleComponent> pComponent = particle->getComponent<ParticleComponent>();
		shared_ptr<TransformComponent> tComponent = particle->getComponent<TransformComponent>();
		shared_ptr<SpriteComponent> sComponent = particle->getComponent<SpriteComponent>();
		shared_ptr<ColorComponent> cComponent = particle->getComponent<ColorComponent>();
		//shared_ptr<AnimatedComponent> aComponent = make_shared<AnimatedComponent>(5, 0.2);
		tComponent->position = clusterOrigin;
		tComponent->size = vec2(16.f, 16.f);
		sComponent->texture = pComponent->healTexture;
		pComponent->type = ParticleType::heal;
		pComponent->active = true; // Now, particle will get rendered
	}
}


void ParticleSystem::updateParticles(EntityManager & manager, float dt) {
  vector<shared_ptr<Entity>> particles = manager.getEntities(manager.getComponentChecker(vector<int> {ComponentType::particle}));
  shared_ptr<Entity> home = manager.getEntities(manager.getComponentChecker(vector<int> {ComponentType::home}))[0];
  shared_ptr<HealthComponent> hComponent = home->getComponent<HealthComponent>();
  shared_ptr<ColorComponent> hcComponent = home->getComponent<ColorComponent>();

  // Emit smoke when base reaches 1/2 health
  if (nextActionTime < 0 && (hComponent->curHP < (0.5 * hComponent->maxHP))) {
    emitSmoke(manager, vec2(643.f, 597.f));
    nextActionTime = DELAY_PERIOD;
  } else {
    nextActionTime -= dt;
  }

  // Handle particles emitted when enemy dies
  for (shared_ptr<Entity> particle : particles) {
    shared_ptr<ParticleComponent> pComponent = particle->getComponent<ParticleComponent>();
    shared_ptr<ColorComponent> cComponent = particle->getComponent<ColorComponent>();
    shared_ptr<TransformComponent> tComponent = particle->getComponent<TransformComponent>();

    if (pComponent->active != true || pComponent->type == ParticleType::nothing) {
      continue;
    }

    pComponent->timer.update(dt);

    float xVelocity, yVelocity = 0.0f;

    if (pComponent->type == ParticleType::blood) {
      xVelocity = (cos(pComponent->angle) * pComponent->speed) * 0.9f;
      yVelocity = (sin(pComponent->angle) * pComponent->speed) + F_g;
      pComponent->angle += dt;
      cComponent->RGBA.w -= dt / 1.5f;
    }
    else if (pComponent->type == ParticleType::smoke) {
      xVelocity = 1.4 * cos(pComponent->angle) * pComponent->speed;
      yVelocity = -1.f * ((sin(pComponent->angle) * pComponent->speed) + F_g);
      pComponent->angle += (dt * 2);
      cComponent->RGBA.w -= dt / 1.5f;
	}
	else if (pComponent->type == ParticleType::heal) {
		xVelocity = 1.4 * cos(pComponent->angle) * pComponent->speed;
		yVelocity = -1.f * ((sin(pComponent->angle) * pComponent->speed) + F_g);
		pComponent->angle += (dt * 2);
		cComponent->RGBA.w -= dt / 1.5f;
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
    shared_ptr<ParticleComponent> pComponent = particle->getComponent<ParticleComponent>();
    shared_ptr<ColorComponent> cComponent = particle->getComponent<ColorComponent>();
    shared_ptr<TransformComponent> tComponent = particle->getComponent<TransformComponent>();
    resetParticle(cComponent, tComponent, pComponent);
  }
}

void ParticleSystem::resetParticle(shared_ptr<ColorComponent> cComponent, shared_ptr<TransformComponent> tComponent, shared_ptr<ParticleComponent> pComponent)
{
  cComponent->RGBA.w = 1.0f; // reset alpha to 1         
  tComponent->size = pComponent->particleScale;
  tComponent->size = DEFAULT_PARTICLE_SCALE;
  pComponent->timer.reset();
  pComponent->type = ParticleType::nothing;
  pComponent->active = false;
}

