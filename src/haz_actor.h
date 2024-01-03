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

#ifndef HAZ_ACTOR_H
#define HAZ_ACTOR_H

#include <stdbool.h>
#include <SDL.h>

#include "hazeng.h"

#define MAPW 32
#define MAPH 32

/*typedef struct haz_geometry {
	int xmin;
	int ymin;
	int xmax;
	int ymax;
} haz_geometry;*/

typedef struct haz_collider {
	bool lcol;
	bool tcol;
	bool rcol;
	bool bcol;
} haz_collider;

typedef struct haz_actor {
	SDL_Rect g;
	SDL_Point acc;
	SDL_Point vel;
	SDL_Point spd;
	haz_collider col;
} haz_actor;

void haz_eightDirMov(haz_actor *_act);
void haz_physics(haz_actor *_act);
void haz_collision(haz_actor *guest, SDL_Rect host);
void haz_containInRect(haz_actor *guest, SDL_Rect host);

#endif //HAZ_ACTOR_H
