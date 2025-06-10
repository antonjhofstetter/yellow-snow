#include "load_media.h"

bool game_load_media(struct Game *g)
{
  g->background_image = IMG_LoadTexture(g->renderer, "assets/images/background.png");
  if (!g->background_image)
  {
    fprintf(stderr, "Error loading image: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  if (SDL_QueryTexture(g->background_image, NULL, NULL, &g->background_rect.w, &g->background_rect.h))
  {
    fprintf(stderr, "Error querying image dimensions: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
