#include "game.h"
#include "initialize.h"
#include "load_media.h"

void check_collision(struct Game *g);
void handle_collision(struct Game *g, struct Flake *f);
void game_reset(struct Game *g);

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

  if (score_new(&g->score, g->renderer))
  {
    return EXIT_FAILURE;
  }

  if (fps_new(&g->fps))
  {
    return EXIT_FAILURE;
  }

  game_reset(g);

  return EXIT_SUCCESS;
}

void game_free(struct Game **game)
{
  if (*game)
  {
    struct Game *g = *game;

    fps_free(&g->fps);
    score_free(&g->score);
    flakes_free(&g->flakes);
    player_free(&g->player);

    Mix_HaltChannel(-1);
    Mix_HaltMusic();

    Mix_FreeMusic(g->music);
    g->music = NULL;

    Mix_FreeChunk(g->hit_sound);
    g->hit_sound = NULL;

    Mix_FreeChunk(g->collect_sound);
    g->collect_sound = NULL;

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

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_Quit();

    free(g);
    g = NULL;
    *game = NULL;
  }
}

void check_collision(struct Game *g)
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
          handle_collision(g, f);
        }
      }
    }

    f = f->next;
  }
}

void handle_collision(struct Game *g, struct Flake *f)
{
  (void)g;

  if (f->is_white)
  {
    score_increment(g->score);
    Mix_PlayChannel(-1, g->collect_sound, 0);
    flake_reset(f, false);
  }
  else
  {
    Mix_PlayChannel(-1, g->hit_sound, 0);
    Mix_PauseMusic();
    g->playing = false;
  }
}

void game_reset(struct Game *g)
{
  flakes_reset(g->flakes);
  score_reset(g->score);

  g->playing = true;
  g->game_paused = false;

  if (!g->music_paused)
  {
    Mix_ResumeMusic();
  }
}

bool game_run(struct Game *g)
{
  game_reset(g);
  player_reset(g->player);

  if (Mix_PlayMusic(g->music, -1))
  {
    fprintf(stderr, "Error playing Music: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // 1: game can be paused/unpaused with p key while game is running
  // 2: music can be toggled
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
          game_reset(g);
          break;

        case SDLK_f:
          fps_toggle_display(g->fps);
          break;

        case SDLK_p:
          if (g->playing)
          {
            g->game_paused = !g->game_paused;
          }
          break;

        case SDLK_m:
          g->music_paused = !g->music_paused;
          if (g->music_paused)
          {
            Mix_PauseMusic();
          }
          break;

        default:
          break;
        }
        break;

      default:
        break;
      }
    }

    if (g->playing && !g->game_paused)
    {
      player_update(g->player, g->delta_time);
      flakes_update(g->flakes, g->delta_time);
      check_collision(g);
    }

    SDL_RenderClear(g->renderer);

    SDL_RenderCopy(g->renderer, g->background_image, NULL, &g->background_rect);
    player_draw(g->player);
    flakes_draw(g->flakes);
    score_draw(g->score);

    SDL_RenderPresent(g->renderer);

    g->delta_time = fps_update(g->fps);
  }

  return EXIT_SUCCESS;
}
