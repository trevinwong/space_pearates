#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "Utility/utility.hpp"
#include "hud.hpp"
#include <time.h> 

// Singleton https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class AudioLoader
{
public:
  AudioLoader(AudioLoader const&) = delete;
  void operator=(AudioLoader const&) = delete;
  static AudioLoader& getInstance()
  {
    static AudioLoader instance;
    return instance;
  }

  Mix_Chunk *player_hurt;
  Mix_Chunk *collect_coin_sound;
  Mix_Chunk *jump;
  Mix_Chunk *build_tower;
  Mix_Chunk *sell_tower;
  Mix_Chunk *upgrade_tower;
  Mix_Chunk *max_upgrade_tower;
  Mix_Chunk *enemy_dead;
  Mix_Chunk *pause;
  Mix_Chunk *base_hit;
  Mix_Chunk *heal;
  Mix_Chunk *defense_phase;
  Mix_Chunk *start;
  Mix_Chunk *invalid;
  Mix_Chunk *alert;
  Mix_Chunk *next;
  Mix_Chunk *game_over;
  Mix_Chunk *win_game;

  //Mix_Chunk *battle_theme1;
  Mix_Music *eurobeat_full;
  Mix_Music *hip_shop;

  Mix_Music *mainmenu_bgm;
  vector<pair<string, Mix_Music*>> music_list;
  int currentBGMIndex = 0;

  void playMainMenuBGM();
  void playGameMusic();
  void reset();
  void randomizeBgm();
  void changeBgm();
  void endgameBgm();
  void destroy();

private:
  AudioLoader();
};

#endif
