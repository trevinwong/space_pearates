#include "level_assets_system.hpp"

LevelAssetsSystem::LevelAssetsSystem() {
  tile_level_1 = make_shared<Texture>(texture_path("level_assets/tile_block.png"), true);
  tile_level_2 = make_shared<Texture>(texture_path("level_assets/tile_block2.png"), true);
  tile_level_3 = make_shared<Texture>(texture_path("level_assets/tile_block3.png"), true);
  tile_level_4 = make_shared<Texture>(texture_path("level_assets/tile_block4.png"), true);
  tile_level_5 = make_shared<Texture>(texture_path("level_assets/tile_block5.png"), true);
}

void LevelAssetsSystem::set_level(int level) {
  curr_level = level;
}

string LevelAssetsSystem::getBgImageFileName(int level) {
  string imgName = "level_assets/bg" + std::to_string(level) + ".png";
  return imgName;
}

void LevelAssetsSystem::set_resources(EntityManager & manager) {
  vector<shared_ptr<Entity>> tiles = manager.getEntities(manager.getComponentChecker(vector<int> {ComponentType::tile}));
  for (shared_ptr<Entity> tile : tiles) {
    shared_ptr<TileComponent> tComponent = tile->getComponent<TileComponent>();
    if (tComponent != nullptr) {
      if (tComponent->isPhysical) {
        switch(curr_level) {
          case 1: 
            tile->getComponent<SpriteComponent>()->texture = tile_level_1;
            break;
          case 2:
            tile->getComponent<SpriteComponent>()->texture = tile_level_2;
            break;
          case 3:
            tile->getComponent<SpriteComponent>()->texture = tile_level_3;
            break;
          case 4: 
            tile->getComponent<SpriteComponent>()->texture = tile_level_4;
            break;
          case 5: 
            tile->getComponent<SpriteComponent>()->texture = tile_level_5;
            break;
          default:
            tile->getComponent<SpriteComponent>()->texture = tile_level_1;
        }
      }
    }
  }
}

