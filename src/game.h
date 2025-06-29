#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "player.h"
#include "flakes.h"
#include "score.h"
#include "fps.h"
#include "title.h"

struct Game
{
  SDL_Event event;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *background_image;
  SDL_Rect background_rect;
  SDL_Texture *player_image;
  SDL_Texture *yellow_image;
  SDL_Texture *white_image;
  Mix_Chunk *collect_sound;
  Mix_Chunk *hit_sound;
  Mix_Music *music;
  bool music_paused;
  bool game_paused;
  bool playing;
  double delta_time;

  struct Player *player;
  struct Flake *flakes;
  struct Score *score;
  struct Fps *fps;
  struct Title *title;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
bool game_run(struct Game *g);

#endif
