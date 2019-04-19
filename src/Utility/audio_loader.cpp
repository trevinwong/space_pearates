#include "Utility/audio_loader.hpp"

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
  player_hurt = Mix_LoadWAV(audio_path("player_hurt.mp3"));
  collect_coin_sound = Mix_LoadWAV(audio_path("collect_coin.wav"));
  jump = Mix_LoadWAV(audio_path("jump.wav"));
  build_tower = Mix_LoadWAV(audio_path("build.wav"));
  sell_tower = Mix_LoadWAV(audio_path("sell.wav"));
  upgrade_tower = Mix_LoadWAV(audio_path("upgrade.wav"));
  enemy_dead = Mix_LoadWAV(audio_path("dead.wav"));
  pause = Mix_LoadWAV(audio_path("pause.wav"));
  base_hit = Mix_LoadWAV(audio_path("base_damage.wav"));
  start = Mix_LoadWAV(audio_path("start.wav"));
  invalid = Mix_LoadWAV(audio_path("invalid.wav"));
  alert = Mix_LoadWAV(audio_path("alert.wav"));
  next = Mix_LoadWAV(audio_path("next.wav"));
  game_over = Mix_LoadWAV(audio_path("game_over.wav"));

  // Load music
  eurobeat_full = Mix_LoadMUS(audio_path("eurobeat_full.wav"));
  hip_shop = Mix_LoadMUS(audio_path("hip_shop.wav"));

  mainmenu_bgm = Mix_LoadMUS(audio_path("arcade_space.ogg"));
  music_list.push_back(make_pair("Back to Basics", Mix_LoadMUS(audio_path("back_to_basics.ogg"))));
  music_list.push_back(make_pair("Electrozap", Mix_LoadMUS(audio_path("electrozap.ogg"))));
  music_list.push_back(make_pair("Surface Tension", Mix_LoadMUS(audio_path("surface_tension.ogg"))));
  music_list.push_back(make_pair("Chaoz Fantasy", Mix_LoadMUS(audio_path("chaoz_fantasy.ogg"))));
  music_list.push_back(make_pair("Galactic Journey", Mix_LoadMUS(audio_path("galactic_journey.ogg"))));
  music_list.push_back(make_pair("Paradise on E", Mix_LoadMUS(audio_path("paradise_on_e.ogg"))));

}

void AudioLoader::playMainMenuBGM()
{
  if (Mix_PlayMusic(mainmenu_bgm, -1) == -1) {
    cout << "Mix_PlayMusic: " << Mix_GetError() << endl;
  } 
}

void AudioLoader::playGameMusic()
{
  string music_name = music_list[currentBGMIndex].first; 
  HUD::getInstance().setMusicName(music_name);
  Mix_Music *music_chunk = music_list[currentBGMIndex].second;
  Mix_RewindMusic();
  if (Mix_PlayMusic(music_chunk, -1) == -1) {
    cout << "Mix_PlayMusic: " << Mix_GetError() << endl;
  } 
}

void AudioLoader::reset()
{
  playGameMusic();
}

void AudioLoader::changeBgm() {
  currentBGMIndex = (currentBGMIndex + 1) % music_list.size();
  playGameMusic();
}

void AudioLoader::endgameBgm() { // TODO: cue on GAMEOVER
  // play music forever, fading in over 5 seconds
  if (Mix_FadeInMusic(hip_shop, -1, 5000) == -1) {
    cout << "Mix_FadeInMusic: " << Mix_GetError() << endl;
  }
}

void AudioLoader::destroy()
{
  Mix_CloseAudio();

  Mix_FreeChunk(collect_coin_sound);
  Mix_FreeChunk(jump);
  Mix_FreeChunk(build_tower);
  Mix_FreeChunk(enemy_dead);
  Mix_FreeChunk(pause);
  Mix_FreeChunk(base_hit);
  Mix_FreeChunk(start);
  Mix_FreeChunk(alert);
  Mix_FreeChunk(next);
  Mix_FreeChunk(game_over);
  Mix_FreeMusic(eurobeat_full);
  Mix_FreeMusic(hip_shop);
  
  for (pair<string, Mix_Music*> music : music_list) {
    Mix_FreeMusic(music.second);
  }
}
