#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "utility.hpp"

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

  Mix_Chunk *collect_coin_sound;
  //Mix_Chunk *battle_theme1;
  Mix_Music *eurobeat_full;
  Mix_Music *hip_shop;

  void changeBgm();
  //TODO: destroy method, leaking pointers for now...

private:
  AudioLoader();
};

#endif
