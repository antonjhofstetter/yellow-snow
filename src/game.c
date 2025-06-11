#include "game.h"
#include "initialize.h"
#include "load_media.h"
#include "flakes.h"
#include "player.h"

bool check_collision(struct Game *g);
bool handle_collision(struct Game *g, struct Flake *f);

bool game_new(struct Game **game)
{
  *game = calloc(1, sizeof(struct Game));
  if (*game == NULL)
  {
    fprintf(stderr, "Error in calloc of new game.\n");
    return EXIT_FAILURE;
  }

  struct Game *g = *game;

  if (game_initialize(g))
  {
    return EXIT_FAILURE;
  }

  if (game_load_media(g))
  {
    return EXIT_FAILURE;
  }

  if (player_new(&g->player, g->renderer, g->player_image))
  {
    return EXIT_FAILURE;
  }

  player_reset(g->player);

  for (int i = 0; i < 5; i++)
  {
    if (flake_new(&g->flakes, g->renderer, g->yellow_image, false))
    {
      return EXIT_FAILURE;
    }
  }

  for (int i = 0; i < 10; i++)
  {
    if (flake_new(&g->flakes, g->renderer, g->white_image, true))
    {
      return EXIT_FAILURE;
    }
  }

  flakes_reset(g->flakes);

  return EXIT_SUCCESS;
}

void game_free(struct Game **game)
{
  if (*game)
  {
    struct Game *g = *game;

    flakes_free(&g->flakes);
    player_free(&g->player);

    SDL_DestroyTexture(g->white_image);
    g->white_image = NULL;

    SDL_DestroyTexture(g->yellow_image);
    g->yellow_image = NULL;

    SDL_DestroyTexture(g->player_image);
    g->player_image = NULL;

    SDL_DestroyTexture(g->background_image);
    g->background_image = NULL;

    SDL_DestroyRenderer(g->renderer);
    g->renderer = NULL;

    SDL_DestroyWindow(g->window);
    g->window = NULL;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    free(g);
    g = NULL;
    *game = NULL;
  }
}

bool check_collision(struct Game *g)
{
  struct Flake *f = g->flakes;
  int top = player_top(g->player);
  int left = player_left(g->player);
  int right = player_right(g->player);

  while (f)
  {
    if (flake_bottom(f) > top)
    {
      if (flake_right(f) > left)
      {
        if (flake_left(f) < right)
        {
          if (handle_collision(g, f))
          {
            return true;
          }
        }
      }
    }

    f = f->next;
  }

  return false;
}

bool handle_collision(struct Game *g, struct Flake *f)
{
  (void)g;

  if (f->is_white)
  {
    //
  }
  else
  {
    //
  }

  flake_reset(f, false);

  return EXIT_SUCCESS;
}

bool game_run(struct Game *g)
{
  while (true)
  {
    while (SDL_PollEvent(&g->event))
    {
      switch (g->event.type)
      {
      case SDL_QUIT:
        return EXIT_SUCCESS;
        break;

      case SDL_KEYDOWN:
        switch (g->event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          return EXIT_SUCCESS;
          break;

        case SDLK_SPACE:
          player_reset(g->player);
          flakes_reset(g->flakes);
          break;

        default:
          break;
        }
        break;

      default:
        break;
      }
    }

    player_update(g->player);
    flakes_update(g->flakes);

    if (check_collision(g))
    {
      return true;
    }

    SDL_RenderClear(g->renderer);
    SDL_RenderCopy(g->renderer, g->background_image, NULL, &g->background_rect);

    player_draw(g->player);
    flakes_draw(g->flakes);

    SDL_RenderPresent(g->renderer);

    SDL_Delay(16);
  }

  return EXIT_SUCCESS;
}
