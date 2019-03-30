#include "player_data_loader.hpp"

PlayerData PlayerDataLoader::playerData;

void PlayerDataLoader::loadPlayerData()
{
  std::ifstream ifs(player_path("player_data.txt"));
  checkValidFilename(ifs, player_path("player_data.txt"));

  float sizeX, sizeY;
  float maxVelocityX, maxVelocityY;
  float maxAccelX, maxAccelY;
  float health;
  int maxJumps;
  float jumpVelocity;
  
  fillVariable(ifs, sizeX, "sizeX");
  fillVariable(ifs, sizeY, "sizeY");
  moveToNextLine(ifs);
  fillVariable(ifs, maxVelocityX, "maxVelocityX");
  fillVariable(ifs, maxVelocityY, "maxVelocityY");
  moveToNextLine(ifs);
  fillVariable(ifs, maxAccelX, "maxAccelX");
  fillVariable(ifs, maxAccelY, "maxAccelY");
  moveToNextLine(ifs);
  fillVariable(ifs, health, "health");
  moveToNextLine(ifs);
  fillVariable(ifs, maxJumps, "maxJumps");
  moveToNextLine(ifs);
  fillVariable(ifs, jumpVelocity, "jumpVelocity");
  
  ifs.close();
  playerData = PlayerData(vec2(sizeX, sizeY), vec2(maxVelocityX, maxVelocityY), vec2(maxAccelX, maxAccelY), health, maxJumps, jumpVelocity);
}
