#ifndef ENEMY_PATH_COMPONENT_H
#define ENEMY_PATH_COMPONENT_H

#include "base_component.hpp"
#include "entity_manager.hpp"
#include "EntityFactories/enemy_factory.hpp"
#include "../Systems/tile_map_system.hpp"
#include "hud.hpp"
#include "../Systems/waveset_system.hpp"

class EnemyPathComponent : public BaseComponent
{
public:
  EnemyPathComponent(int _type);

  enum moveType {
    basic,
    turtle_shell,
    random
  };

  bool ground;
  int type;
  void move(float dt, EntityManager& entityManager);
  void moveBasic (float dt, EntityManager& entityManager);
  void moveRandom (float dt, EntityManager& entityManager);
  void moveShell (float dt, EntityManager& entityManager);
  void setMap (EntityManager& entityManager);

  static const int typeID = ComponentType::enemy_path;
  inline virtual int getTypeID() const { return typeID; };
  vector<vector<char>> map;
  vector<shared_ptr<Entity>> tiles;
};

#endif