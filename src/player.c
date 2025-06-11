#include "player.h"

bool player_new(struct Player **player, SDL_Renderer *renderer, SDL_Texture *image)
{
  *player = calloc(1, sizeof(struct Player));
  if (*player == NULL)
  {
    fprintf(stderr, "Error allocating new Player.\n");
    return EXIT_FAILURE;
  }

  struct Player *p = *player;
  p->renderer = renderer;
  p->image = image;
  p->keystate = SDL_GetKeyboardState(NULL);

  if (SDL_QueryTexture(p->image, NULL, NULL, &p->rect.w, &p->rect.h))
  {
    fprintf(stderr, "Error querying Texture: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  p->flip = SDL_FLIP_NONE;
  p->rect.x = (WIN_W - p->rect.w) / 2;
  p->rect.y = 377;

  return EXIT_SUCCESS;
}

void player_free(struct Player **player)
{
  if (*player)
  {
    (*player)->image = NULL;
    (*player)->renderer = NULL;
    (*player)->keystate = NULL;
    free(*player);
    *player = NULL;
  }
}

void player_update(struct Player *p)
{
  if (p->keystate[SDL_SCANCODE_A])
  {
    if (p->rect.x > (p->rect.w / -4))
    {
      p->rect.x -= 5;
    }
    p->flip = SDL_FLIP_HORIZONTAL;
  }

  if (p->keystate[SDL_SCANCODE_D])
  {
    if (p->rect.x < WIN_W - p->rect.w * 3 / 4)
    {
      p->rect.x += 5;
    }
    p->flip = SDL_FLIP_NONE;
  }
}

void player_draw(struct Player *p)
{
  SDL_RenderCopyEx(p->renderer, p->image, NULL, &p->rect, 0, NULL, p->flip);
}