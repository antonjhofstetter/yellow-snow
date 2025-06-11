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

  return EXIT_SUCCESS;
}
