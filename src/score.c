#include "score.h"

bool score_update(struct Score *s);

bool score_new(struct Score **score, SDL_Renderer *renderer)
{
  *score = calloc(1, sizeof(struct Score));
  if (*score == NULL)
  {
    fprintf(stderr, "Error in calloc of new Score.\n");
    return EXIT_FAILURE;
  }

  struct Score *s = *score;
  s->renderer = renderer;
  s->color = (SDL_Color){255, 255, 255, 255};

  s->font = TTF_OpenFont("assets/fonts/freesansbold.ttf", FONT_SIZE);
  if (!s->font)
  {
    fprintf(stderr, "Error opening Font: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  s->rect.x = 10;
  s->rect.y = 10;

  if (score_reset(s))
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void score_free(struct Score **score)
{
  if (*score)
  {
    struct Score *s = *score;

    TTF_CloseFont(s->font);
    s->font = NULL;

    SDL_DestroyTexture(s->image);
    s->image = NULL;
    s->renderer = NULL;

    free(s);
    s = NULL;
    *score = NULL;
  }
}

bool score_reset(struct Score *s)
{
  s->score = 0;
  return score_update(s);
}

bool score_increment(struct Score *s)
{
  s->score++;
  return score_update(s);
}

bool score_update(struct Score *s)
{
  (void)s;

  return EXIT_SUCCESS;
}

void score_draw(struct Score *s)
{
  SDL_RenderCopy(s->renderer, s->image, NULL, &s->rect);
}
