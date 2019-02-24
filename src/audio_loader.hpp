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

private:
  AudioLoader()
  {
    collect_coin_sound = Mix_LoadWAV(audio_path("collect_coin.wav"));
  }
};

#endif
