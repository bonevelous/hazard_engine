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

#ifndef HAZ_ENTITY_H
#define HAZ_ENTITY_H

#include <stdio.h>
#include <SDL.h>

#define MAX_COMPS 128

typedef struct speed {
	int entity_id;
	int x;
	int y;
} speed;

typedef struct veloc {
	int entity_id;
	int x;
	int y;
} veloc;

/*typedef struct accel {
	int entity_id;
	int x;
	int y;
} accel;*/

typedef struct component_lists {
	speed speed_comps[MAX_COMPS];
	veloc veloc_comps[MAX_COMPS];
	//accel accel_comps[MAX_COMPS];
	int total_speed_comps;
	int total_veloc_comps;
} component_lists;

typedef struct entity {
	bool active;

} entity;

#endif //HAZ_ENTITY_H
