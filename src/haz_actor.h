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

typedef struct haz_actor {
	SDL_Point acc; //Acceleration Rate
	SDL_Point vel; //Velocity
	SDL_Point spd; //Target Speed
} haz_actor;

void haz_eightDirMov(haz_actor *act, int xspd, int yspd);
void haz_physics(haz_actor *act);
void haz_containInRect(haz_actor *act, SDL_Rect host);

bool haz_collision(haz_actor *act, SDL_Rect host);

#endif //HAZ_ACTOR_H
