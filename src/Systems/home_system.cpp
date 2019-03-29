#include "home_system.hpp"

void HomeSystem::handleCriticalState(shared_ptr<Entity> home) {
    shared_ptr<SpriteComponent> sprite_component = home->getComponent<SpriteComponent>();
    shared_ptr<HomeComponent> home_component = home->getComponent<HomeComponent>();
    if (alert_played == false) {
        Mix_PlayChannel(-1, AudioLoader::getInstance().alert, 0);
        alert_played = true;
    }
    shared_ptr<Texture> new_texture = home_component->alt_texture;
    sprite_component->texture = new_texture;
}

void HomeSystem::checkState(EntityManager &entityManager) {
    shared_ptr<Entity> home = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::home}))[0];
	shared_ptr<HealthComponent> health_component = home->getComponent<HealthComponent>();

    if (health_component->curHP <= (health_component->maxHP * 0.5)) {
        handleCriticalState(home);     
    } 
}

  void HomeSystem::reset(EntityManager &entityManager) {
    shared_ptr<Entity> home = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::home}))[0];
    shared_ptr<SpriteComponent> sprite_component = home->getComponent<SpriteComponent>();
    shared_ptr<HomeComponent> home_component = home->getComponent<HomeComponent>();
    shared_ptr<Texture> default_texture = home_component->default_texture;
    sprite_component->texture = default_texture;
    alert_played = false;
  }