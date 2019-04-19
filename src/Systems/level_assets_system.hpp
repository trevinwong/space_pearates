#ifndef LEVEL_ASSETS_SYSTEM_H
#define LEVEL_ASSETS_SYSTEM_H

#include "../Utility/utility.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../Utility/texture.hpp"
#include "../Utility/waveset_structs.hpp"
#include "../Components/background_component.hpp"
#include "../Components/sprite_component.hpp"
#include "../Components/tile_component.hpp"

class LevelAssetsSystem
{
public:
// Singleton design pattern
  LevelAssetsSystem(LevelAssetsSystem const&) = delete;
  void operator=(LevelAssetsSystem const&) = delete;
  static LevelAssetsSystem& getInstance()
  {
    static LevelAssetsSystem instance;
    return instance;
  }

  int curr_level = 1; 
  
  void set_level(int level);
  void set_resources(EntityManager & manager);
  string getBgImageFileName(int level);

private:
    LevelAssetsSystem();
    shared_ptr<Texture> tile_level_2; 
    shared_ptr<Texture> tile_level_1;
    shared_ptr<Texture> tile_level_3;
    shared_ptr<Texture> tile_level_4;
    shared_ptr<Texture> tile_level_5;
};

#endif
