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

#ifndef HAZENG_H
#define HAZENG_H

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <limits.h>
#include <unistd.h>
#include <getopt.h>

#include <SDL.h>

#define MAPW 16
#define MAPH 16

typedef struct hazard_engine {
	//char *error;
	SDL_Window *w;
	SDL_Renderer *r;
	char *t;
	int p;
	SDL_Rect g;
	char wf;
	char rf;
	int live;
} hazard_engine;

int haz_init();
int haz_live();
void haz_eng();
//char *haz_getError();

int haz_loadLevel(const char *filename);

void haz_pollEv(SDL_Event *_ev);
void haz_render();
void haz_renderLevel();

void haz_quit();

#endif //HAZENG_H
