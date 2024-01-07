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

#include "hazeng.h"
#include "haz_actor.h"

bool haz_collision(haz_actor *act, SDL_Rect host) {
	haz_geom ag = {act->g.x, act->g.y, act->g.x + act->g.w, act->g.y + act->g.h};
	haz_geom hg = {host.x, host.y, host.x + host.w, host.y + host.h};

	if (ag.x1 > hg.x2 || ag.x2 < hg.x1 || ag.y1 > hg.y2 || ag.y2 < hg.y1) return false;
	return true;
}

void haz_eightDirMov(haz_actor *act, int xspd, int yspd) {
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	if (!keystate[SDL_SCANCODE_LEFT] &&
	    !keystate[SDL_SCANCODE_RIGHT]) act->spd.x = 0;

	if (keystate[SDL_SCANCODE_LEFT]) {
		if (act->mov.l) act->spd.x = -xspd;
		else {
			act->spd.x = 0;
			act->vel.x = 0;
		}
	}

	if (keystate[SDL_SCANCODE_RIGHT]) {
		if (act->mov.r) act->spd.x = xspd;
		else {
			act->spd.x = 0;
			act->vel.x = 0;
		}
	}

	if (!keystate[SDL_SCANCODE_UP] &&
	    !keystate[SDL_SCANCODE_DOWN]) act->spd.y = 0;

	if (keystate[SDL_SCANCODE_UP]) {
		if (act->mov.u) act->spd.y = -yspd;
		else {
			act->spd.y = 0;
			act->vel.y = 0;
		}
	}

	if (keystate[SDL_SCANCODE_DOWN]) {
		if (act->mov.d) act->spd.y = yspd;
		else {
			act->spd.y = 0;
			act->vel.y = 0;
		}
	} 

	haz_physics(act);
}

void haz_physics(haz_actor *act) {
	if (act->vel.x < act->spd.x) act->vel.x += act->acc.x;
	else if (act->vel.x > act->spd.x) act->vel.x -= act->acc.x;
	else act->vel.x = act->spd.x;

	if (act->vel.y < act->spd.y) act->vel.y += act->acc.y;
	else if (act->vel.y > act->spd.y) act->vel.y -= act->acc.y;
	else act->vel.y = act->spd.y;

	act->g.x += act->vel.x;
	act->g.y += act->vel.y;
}

void haz_containInRect(haz_actor *act, SDL_Rect host) {
	int max_x = (host.x + host.w) - act->g.w;
	int max_y = (host.y + host.h) - act->g.h;

	if (act->g.x < host.x) act->g.x = host.x;
	if (act->g.x > max_x) act->g.x = max_x;
	if (act->g.y < host.y) act->g.y = host.y;
	if (act->g.y > max_y) act->g.y = max_y;
}
