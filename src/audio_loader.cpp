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

  collect_coin_sound = Mix_LoadWAV(audio_path("collect_coin.wav"));
  //battle_theme1 = Mix_LoadWAV(audio_path("battle_theme1.ogg"));
  eurobeat_full = Mix_LoadMUS(audio_path("eurobeat_full.wav"));
  hip_shop = Mix_LoadMUS(audio_path("hip_shop.wav"));
  cout << "Loaded audio" << endl;

  // Now play bgm forever
  if (Mix_PlayMusic(eurobeat_full, -1) == -1) {
    cout << "Mix_PlayMusic: " << Mix_GetError() << endl;
    // well, there's no music, but most games don't break without music...
  }
}

void AudioLoader::changeBgm() {
  // play music forever, fading in over 5 seconds
  if (Mix_FadeInMusic(hip_shop, -1, 5000) == -1) {
    cout << "Mix_FadeInMusic: " << Mix_GetError() << endl;
  }
  cout << "changeBgm()" << endl;
}