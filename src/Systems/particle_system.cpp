#include "particle_system.hpp"    

const int MAX_PARTICLES = 10;
const int MAX_ENEMIES = 30;
const float DELAY_PERIOD =0.1f;
static float nextActionTime = DELAY_PERIOD;
static int lastUsedIndex = 0;
std::vector<shared_ptr<Entity>> ParticleSystem::particleClusters;

const float F_g = 9.8;  // force of gravity


void ParticleSystem::initParticleSystem(EntityManager & manager) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        for (int j = 0; j < MAX_PARTICLES; j++) {
            Entity particle = ParticleFactory::build(glm::vec2(0.0f,0.0f));
            manager.addEntity(particle); // Particles are on default "inactive" and won't be rendered
        }
    }
    particleClusters = manager.getEntities(manager.getComponentChecker(vector<int> {ComponentType::particle}));
}


void ParticleSystem::emitParticleCluster(EntityManager & manager, glm::vec2 clusterOrigin) {
        for (int i = 0; i < 20; i++) {
            std::shared_ptr<Entity> particle = particleClusters[findUnusedParticle()];
            ParticleComponent * pComponent = particle->getComponent<ParticleComponent>();
            TransformComponent * tComponent = particle->getComponent<TransformComponent>();
            tComponent->position = clusterOrigin;
            pComponent->active = true; // Now particle will get rendered
        }
}


int ParticleSystem::findUnusedParticle() {
    for (int i = lastUsedIndex; i < (MAX_PARTICLES * MAX_ENEMIES); i++) {
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

void ParticleSystem::emitSmoke(EntityManager & manager, glm::vec2 clusterOrigin) {
        for (int i = 0; i < 10; i++) {
            std::shared_ptr<Entity> particle = particleClusters[findUnusedParticle()];
            ParticleComponent * pComponent = particle->getComponent<ParticleComponent>();
            TransformComponent * tComponent = particle->getComponent<TransformComponent>();
            ColorComponent * cComponent = particle->getComponent<ColorComponent>();

            // mComponent->maxAccel.y = -40.f;
            // mComponent->maxAccel.x /= 3.0f;
            // mComponent->velocity.y *= -0.1f;
            // mComponent->velocity.x /= 1.25f;
            tComponent->position = clusterOrigin;          
            // tComponent->size = glm::vec2(45.0,55.0);
            // cComponent->RGBA = glm::vec4(0.6,0.6,0.6, 1.0);
          
            pComponent->active = true; // Now, particle will get rendered
        }
    
    }


void ParticleSystem::updateParticles(EntityManager & manager, float dt) {
    vector<shared_ptr<Entity>> particles = manager.getEntities(manager.getComponentChecker(vector<int> {ComponentType::particle}));
    shared_ptr<Entity> home = manager.getEntities(manager.getComponentChecker(vector<int> {ComponentType::home}))[0];
    //HealthComponent * hComponent = home->getComponent<HealthComponent>();


    //if (nextActionTime < 0 && (hComponent->curHP < (0.5 * hComponent->maxHP))) {
        if (nextActionTime < 0) {
        //emitSmoke(manager, glm::vec2(625.f,595.f));
        nextActionTime = DELAY_PERIOD;
    } else {
        nextActionTime -= dt;
    }
 
   
    // Handle particles emitted when enemy dies
	for (shared_ptr<Entity> particle : particles) {
		ParticleComponent *pComponent = particle->getComponent<ParticleComponent>();
        ColorComponent *cComponent = particle->getComponent<ColorComponent>();
        TransformComponent *tComponent = particle->getComponent<TransformComponent>();
    
        if (pComponent->active == true) {
            pComponent->timer.update(dt);
            cComponent->RGBA.w -= dt / 1.5f;
        }

        float xVelocity = cos(pComponent->angle) * pComponent->speed;
        float yVelocity = (sin(pComponent->angle) * pComponent->speed) + F_g;

        // glm::vec2 newVelocity = glm::vec2(xVelocity)

        // Handle acceleration
        // pComponent->currAccel += (-0.98 * dt);
        // pComponent->currAccel = glm::clamp(pComponent->currAccel, -pComponent->maxAccel, pComponent->maxAccel);


        // Compute new velocity
        // glm::vec2 newVelocity = {
        //     pComponent->currVelocity.x * pComponent->currAccel.x, 
        //     pComponent->currVelocity.y * 1.0
        // };

        // pComponent->currVelocity = newVelocity;
    
        tComponent->position += glm::vec2(xVelocity, yVelocity) * (dt * 5.f);
    
        pComponent->angle += dt;


        // Reset particle parameters
		if (pComponent->timer.getTimeLeft() <= 0) {
            pComponent->timer.reset();    
            cComponent->RGBA.w = 1.0f; // reset alpha to 1         
            tComponent->size = pComponent->particleScale;
            pComponent->active = false;
		}
	}
}

