/*  Harvey Hazard 1 - A simple platformer
 *  Copyright (C) 2023	Matthew Gobbi
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HAZ_ENGINE_H
#define HAZ_ENGINE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <limits.h>
#include <unistd.h>
#include <getopt.h>

#include <SDL.h>
#include <SDL_image.h>

#define MAP_W 16
#define MAP_H 16
#define TILE_H 16
#define TILE_W 16

#define CLS "\x1b[1;1H\x1b[2J"

typedef struct hazard_engine {
	int initf;
	SDL_Window *w;
	SDL_Renderer *r;
	char *t;
	int p;
	SDL_Rect g;
	char wf;
	char rf;
	int imgf;
	SDL_Point tsize;
	bool live;
	bool debug;
} hazard_engine;

int haz_init(int argc, char **argv);
bool haz_live(void);
void haz_eng(void);

void haz_setDebug(void);
bool haz_getDebug(void);

SDL_Rect haz_getWinRect(void);
SDL_GameController *haz_findController(void);

int haz_loadTextures(SDL_Renderer *ren);
void haz_cleanTextures(void);

int haz_loadLevel(const char *filename);
void haz_setTile(char _ch, int x, int y);
char haz_getTile(int x, int y);

void haz_pollEv(void);
void haz_render(int fps);

void haz_renderLevel(SDL_Renderer *ren);

bool haz_hrange(SDL_Rect guest, SDL_Rect host);
bool haz_vrange(SDL_Rect guest, SDL_Rect host);

SDL_Point get_tsize(void);

void haz_quit(void);

#endif //HAZ_ENGINE_H
