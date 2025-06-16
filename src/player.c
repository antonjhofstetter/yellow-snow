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
  p->speed = 300;
  p->top_offset = 20;
  p->left_offset = 45;
  p->right_offset = 45;

  if (SDL_QueryTexture(p->image, NULL, NULL, &p->rect.w, &p->rect.h))
  {
    fprintf(stderr, "Error querying Texture: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  player_reset(p);

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

void player_reset(struct Player *p)
{
  p->flip = SDL_FLIP_NONE;
  p->rect.x = (WIN_W - p->rect.w) / 2;
  p->pos_x = (double)p->rect.x;
  p->rect.y = 377;
}

void player_update(struct Player *p, double dt)
{
  if (p->keystate[SDL_SCANCODE_A])
  {
    if (player_left(p) >= 0)
    {
      p->pos_x -= p->speed * dt;
    }

    p->flip = SDL_FLIP_HORIZONTAL;
  }

  if (p->keystate[SDL_SCANCODE_D])
  {
    if (player_right(p) <= WIN_W)
    {
      p->pos_x += p->speed * dt;
    }

    p->flip = SDL_FLIP_NONE;
  }

  p->rect.x = (int)p->pos_x;
}

void player_draw(struct Player *p)
{
  SDL_RenderCopyEx(p->renderer, p->image, NULL, &p->rect, 0, NULL, p->flip);
}

int player_top(struct Player *p)
{
  return p->rect.y + p->top_offset;
}

int player_left(struct Player *p)
{
  return p->rect.x + p->left_offset;
}

int player_right(struct Player *p)
{
  return p->rect.x + p->rect.w - p->right_offset;
}
