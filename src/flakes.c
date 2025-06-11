#include "flakes.h"

bool flake_new(struct Flake **flake, SDL_Renderer *renderer, SDL_Texture *image)
{
  struct Flake *new_flake = calloc(1, sizeof(struct Flake));
  if (!new_flake)
  {
    fprintf(stderr, "Error in calloc of new Flake.\n");
    return EXIT_FAILURE;
  }
  new_flake->renderer = renderer;
  new_flake->image = image;
  new_flake->rect.x = (rand() % WIN_W - 100) + 50;
  new_flake->rect.y = -50;

  if (SDL_QueryTexture(new_flake->image, NULL, NULL, &new_flake->rect.w, &new_flake->rect.h))
  {
    fprintf(stderr, "Error querying Texture: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  new_flake->next = *flake;
  *flake = new_flake;

  return EXIT_SUCCESS;
}

void flakes_free(struct Flake **flakes)
{
  struct Flake *f = *flakes;
  while (f)
  {
    struct Flake *next = f->next;
    f->image = NULL;
    f->renderer = NULL;
    f->next = NULL;
    free(f);

    f = next;
  }

  *flakes = NULL;
}

void flakes_update(struct Flake *f)
{
  while (f)
  {
    if (f->rect.y > WIN_H + 50)
    {
      f->rect.x = (rand() % WIN_W - 25) + 25;
      f->rect.y = -50;
    }
    else
    {
      f->rect.y += 2;
    }

    f = f->next;
  }
}

void flakes_draw(struct Flake *f)
{
  while (f)
  {
    SDL_RenderCopy(f->renderer, f->image, NULL, &f->rect);
    f = f->next;
  }
}
