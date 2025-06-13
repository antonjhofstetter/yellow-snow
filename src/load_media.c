#include "load_media.h"

bool game_load_media(struct Game *g)
{
  g->background_image = IMG_LoadTexture(g->renderer, "assets/images/background.png");
  if (!g->background_image)
  {
    fprintf(stderr, "Error loading Texture: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  if (SDL_QueryTexture(g->background_image, NULL, NULL, &g->background_rect.w, &g->background_rect.h))
  {
    fprintf(stderr, "Error querying Te:xture %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  g->player_image = IMG_LoadTexture(g->renderer, "assets/images/player.png");
  if (!g->player_image)
  {
    fprintf(stderr, "Error loading Texture: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  g->yellow_image = IMG_LoadTexture(g->renderer, "assets/images/yellow.png");
  if (!g->yellow_image)
  {
    fprintf(stderr, "Error loading Texture: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  g->white_image = IMG_LoadTexture(g->renderer, "assets/images/white.png");
  if (!g->white_image)
  {
    fprintf(stderr, "Error loading Texture: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  g->hit_sound = Mix_LoadWAV("assets/sounds/hit.ogg");
  if (!g->hit_sound)
  {
    fprintf(stderr, "Error loading Chunk: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  g->collect_sound = Mix_LoadWAV("assets/sounds/collect.ogg");
  if (!g->collect_sound)
  {
    fprintf(stderr, "Error loading Chunk: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  g->music = Mix_LoadMUS("assets/music/winter_loop.ogg");
  if (!g->music)
  {
    fprintf(stderr, "Error loading Music: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
