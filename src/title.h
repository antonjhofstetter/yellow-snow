#ifndef TITLE_H
#define TITLE_H

#include "main.h"

struct Title
{
  SDL_Renderer *renderer;
  SDL_Texture *image;
  SDL_Surface *surface;
  TTF_Font *font;
  SDL_Rect rect;
  double pos_y;
  double target_y;
  double speed;
  bool show_intro;
  bool show_title;
};

bool title_new(struct Title **title, SDL_Renderer *renderer);
void title_free(struct Title **title);
void title_update(struct Title *t, double dt);
void title_reset(struct Title *t);
void title_disable(struct Title *t);
void title_draw(struct Title *t);

#endif
