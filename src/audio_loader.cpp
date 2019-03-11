#include "audio_loader.hpp"

AudioLoader::AudioLoader() {
  // Loading music and sounds
  if (SDL_Init(SDL_INIT_AUDIO) < 0)
  {
    fprintf(stderr, "Failed to initialize SDL Audio");
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
  {
    fprintf(stderr, "Failed to open audio device");
  }

  // Load sound effects
  collect_coin_sound = Mix_LoadWAV(audio_path("collect_coin.wav"));
  jump = Mix_LoadWAV(audio_path("jump.wav"));
  build_tower = Mix_LoadWAV(audio_path("build.wav"));
  enemy_dead = Mix_LoadWAV(audio_path("dead.wav"));

  // Load music
  eurobeat_full = Mix_LoadMUS(audio_path("eurobeat_full.wav"));
  hip_shop = Mix_LoadMUS(audio_path("hip_shop.wav"));
  
  reset();
}

void AudioLoader::reset()
{
  if (Mix_PlayMusic(eurobeat_full, -1) == -1) {
    cout << "Mix_PlayMusic: " << Mix_GetError() << endl;
  }
  isHipOn = false;
}

void AudioLoader::changeBgm() {
  if (!isHipOn) {
    // play music forever, fading in over 5 seconds
    if (Mix_FadeInMusic(hip_shop, -1, 5000) == -1) {
      cout << "Mix_FadeInMusic: " << Mix_GetError() << endl;
    }
    isHipOn = true;
  }
}

void AudioLoader::destroy()
{
  Mix_CloseAudio();

  Mix_FreeChunk(collect_coin_sound);
  Mix_FreeChunk(jump);
  Mix_FreeChunk(build_tower);
  Mix_FreeChunk(enemy_dead);
  Mix_FreeMusic(eurobeat_full);
  Mix_FreeMusic(hip_shop);
}
