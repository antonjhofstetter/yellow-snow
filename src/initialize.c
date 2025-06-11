#include "initialize.h"

bool game_initialize(struct Game *g)
{
  // srand((unsigned)time(NULL));

  if (SDL_Init(SDL_FLAGS))
  {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  IMG_Init(IMAGE_FLAGS);

  g->window = SDL_CreateWindow(WIN_TITLE, WIN_X, WIN_Y, WIN_W, WIN_H, WINDOW_FLAGS);
  if (!g->window)
  {
    fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  g->renderer = SDL_CreateRenderer(g->window, -1, RENDER_FLAGS);
  if (!g->renderer)
  {
    fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Surface *icon = IMG_Load(WIN_ICON);
  if (!icon)
  {
    fprintf(stderr, "Error loading icon Surface: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  else
  {
    SDL_SetWindowIcon(g->window, icon);
    SDL_FreeSurface(icon);
    icon = NULL;
  }

  return EXIT_SUCCESS;
}
