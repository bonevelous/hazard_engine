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
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <limits.h>
#include <unistd.h>
#include <getopt.h>

#include <SDL.h>

#define MAPW 16
#define MAPH 16

typedef struct hazard_engine {
	SDL_Window *w;
	SDL_Renderer *r;
	char *t;
	int p;
	SDL_Rect g;
	char wf;
	char rf;
	bool live;
} hazard_engine;

typedef struct haz_actor {
	SDL_Rect g;
	//SDL_Point acc;
	SDL_Point vel;
	SDL_Point spd;
	bool col;
} haz_actor;

int haz_init(int argc, char **argv);
bool haz_live();
void haz_eng();

void haz_setDebug();
bool haz_getDebug();

int haz_loadLevel(const char *filename);

void haz_activeActor(haz_actor *_act);
void haz_collision(haz_actor *guest, SDL_Rect host);

void haz_pollEv(SDL_Event *_ev);
void haz_render(int fps);
void haz_renderLevel(SDL_Renderer *ren);

void haz_quit();

#endif //HAZENG_H
