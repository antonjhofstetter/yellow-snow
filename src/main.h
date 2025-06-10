#ifndef MAIN_H
#define MAIN_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define WIN_TITLE "Don't Eat the Yellow Snow!"
#define WIN_X SDL_WINDOWPOS_CENTERED
#define WIN_Y SDL_WINDOWPOS_CENTERED
#define WIN_W 800
#define WIN_H 600

#define SDL_FLAGS SDL_INIT_EVERYTHING
#define WINDOW_FLAGS SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_BORDERLESS
#define RENDER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
#define IMAGE_FLAGS IMG_INIT_PNG
#define MIXER_FLAGS MIX_INIT_OGG

int main(void);

#endif
