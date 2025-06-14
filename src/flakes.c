#include "flakes.h"

bool flake_new(struct Flake **flake, SDL_Renderer *renderer, SDL_Texture *image, bool is_white)
{
  struct Flake *new_flake = calloc(1, sizeof(struct Flake));
  if (!new_flake)
  {
    fprintf(stderr, "Error in calloc of new Flake.\n");
    return EXIT_FAILURE;
  }

  new_flake->renderer = renderer;
  new_flake->image = image;
  new_flake->speed = 300;
  // new_flake->pos_y =
  new_flake->is_white = is_white;

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

void flakes_update(struct Flake *f, double dt)
{
  while (f)
  {
    if (f->pos_y > 514.0)
    {
      flake_reset(f, false);
    }
    else
    {
      f->pos_y += f->speed * dt;
      f->rect.y = (int)f->pos_y;
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

void flakes_reset(struct Flake *f)
{
  while (f)
  {
    flake_reset(f, true);
    f = f->next;
  }
}

void flake_reset(struct Flake *f, bool full)
{
  f->rect.x = rand() % WIN_W - f->rect.w;

  int height = full ? WIN_H * 2 : WIN_H;
  f->rect.y = -(rand() % height) - f->rect.h;
  f->pos_y = (double)f->rect.y;
}

int flake_left(struct Flake *f)
{
  return f->rect.x;
}

int flake_right(struct Flake *f)
{
  return f->rect.x + f->rect.w;
}

int flake_bottom(struct Flake *f)
{
  return f->rect.y + f->rect.h;
}
