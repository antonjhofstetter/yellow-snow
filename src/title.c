#include "title.h"

bool title_new(struct Title **title, SDL_Renderer *renderer)
{
  *title = calloc(1, sizeof(struct Title));
  if (*title == NULL)
  {
    fprintf(stderr, "Error in calloc of new Title.\n");
    return EXIT_FAILURE;
  }

  struct Title *t = *title;
  t->renderer = renderer;
  int text_size = 100;
  SDL_Color outer_color = {255, 255, 0, 255};

  t->font = TTF_OpenFont("assets/fonts/freesansbold.ttf", text_size);
  if (!t->font)
  {
    fprintf(stderr, "Error opening Font: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  t->surface = TTF_RenderText_Blended(t->font, WIN_TITLE, outer_color);
  if (!t->surface)
  {
    fprintf(stderr, "Error creating title text Surface: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  t->rect.w = t->surface->w;
  t->rect.h = t->surface->h;
  t->rect.x = (WIN_W - t->rect.w) / 2;
  t->target_y = (WIN_H - t->rect.h) / 2.0;
  t->speed = 120.0;

  t->image = SDL_CreateTextureFromSurface(t->renderer, t->surface);
  if (!t->image)
  {
    fprintf(stderr, "Error creating title text Texture: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  title_reset(t);

  return EXIT_SUCCESS;
}

void title_free(struct Title **title)
{
  if (*title)
  {
    struct Title *t = *title;

    TTF_CloseFont(t->font);
    t->font = NULL;
    SDL_DestroyTexture(t->image);
    t->image = NULL;
    SDL_FreeSurface(t->surface);
    t->surface = NULL;
    t->renderer = NULL;

    free(t);
    t = NULL;
    *title = NULL;
  }
}

void title_update(struct Title *t, double dt)
{
  if (t->show_intro)
  {
    t->pos_y += t->speed * dt;
    if (t->pos_y < t->target_y)
    {
      t->rect.y = (int)t->pos_y;
    }
    else
    {
      t->show_intro = false;
    }
  }
}

void title_reset(struct Title *t)
{
  t->rect.y = -t->rect.h;
  t->pos_y = t->rect.y;
  t->show_intro = true;
  t->show_title = true;
}

void title_disable(struct Title *t)
{
  t->show_intro = false;
  t->show_title = false;
}

void title_draw(struct Title *t)
{
  if (t->show_title)
  {
    SDL_RenderCopy(t->renderer, t->image, NULL, &t->rect);
  }
}
