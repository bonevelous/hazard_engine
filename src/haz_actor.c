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

void haz_collision(haz_actor *act, SDL_Rect host) {
	haz_geometry a_g = {
		act->g.x,
		act->g.y,
		act->g.x + act->g.w - 1,
		act->g.y + act->g.h - 1
	};

	haz_geometry h_g = {
		host.x,
		host.y,
		host.x + host.w - 1,
		host.y + host.h - 1
	};

	bool hrange = (a_g.y1 > h_g.y2 || a_g.y2 < h_g.y1) ? false : true;
	bool vrange = (a_g.x1 > h_g.x2 || a_g.x2 < h_g.x1) ? false : true;

	haz_geometry a_t = {
		a_g.x1,
		a_g.y1,
		a_g.x2,
		act->g.y + (act->g.h / 2) - 1
	};

	haz_geometry a_b = {
		a_g.x1,
		act->g.y + (act->g.h / 2),
		a_g.x2,
		act->g.y + act->g.h - 1
	};

	haz_geometry a_l = {
		a_g.x1,
		a_g.y1,
		act->g.x + (act->g.w / 2) - 1,
		a_g.y2
	};

	haz_geometry a_r = {
		act->g.x + (act->g.w / 2),
		a_g.y1,
		act->g.x + act->g.w - 1,
		a_g.y2
	};

	haz_geometry h_t = {
		h_g.x1,
		h_g.y1,
		h_g.x2,
		host.y + (host.h / 2) - 1
	};

	haz_geometry h_b = {
		h_g.x1,
		host.y + (host.h / 2),
		h_g.x2,
		host.y + host.h - 1
	};

	haz_geometry h_l = {
		h_g.x1,
		h_g.y1,
		host.x + (host.w / 2) - 1,
		h_g.y2
	};

	haz_geometry h_r = {
		host.x + (host.w / 2),
		h_g.y1,
		host.x + host.w - 1,
		h_g.y2
	};

	act->col.l = (hrange && (a_l.x1 < h_r.x2) && (a_l.x1 > h_r.x1)) ? true : false;
	act->col.r = (hrange && (a_r.x2 > h_l.x1) && (a_r.x2 < h_l.x2)) ? true : false;
	act->col.t = (vrange && (a_t.y1 < h_b.y2) && (a_t.y1 > h_b.y1)) ? true : false;
	act->col.b = (vrange && (a_b.y2 > h_t.y1) && (a_b.y2 < h_t.y2)) ? true : false;

	if (act->col.l) {
		act->g.x += h_r.x2 - a_l.x1;
	}

	if (act->col.t) {
		int isect = h_r.y2 - a_l.y1;
	}

	if (act->col.r) {
		int isect = a_r.x2 - h_l.x1;
	}

	if (act->col.b) {
		int isect = a_r.y2 - h_l.y1;
	}
}

/*void haz_gameConMov(haz_actor *act) {
	
}*/

void haz_eightDirMov(haz_actor *act) {
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	int hdir = 0;
	int vdir = 0;

	if (keystate[SDL_SCANCODE_LEFT]) hdir = -1;
	if (keystate[SDL_SCANCODE_RIGHT]) hdir = 1;

	if (keystate[SDL_SCANCODE_UP]) vdir = -1;
	if (keystate[SDL_SCANCODE_DOWN]) vdir = 1;

	switch (hdir) {
		case -1:
			if (act->vel.x > -act->spd.x) act->vel.x -= act->acc.x;
			else act->vel.x = -act->spd.x;
			if (act->col.l) act->vel.x = 0;
			break;
		case 0:
			if (act->vel.x < 0) act->vel.x += act->acc.x;
			else if (act->vel.x > 0) act->vel.x -= act->acc.x;
			else act->vel.x = 0;
			break;
		case 1:
			if (act->vel.x < act->spd.x) act->vel.x += act->acc.x;
			else act->vel.x = act->spd.x;
			if (act->col.r) act->vel.x = 0;
			break;
		default:
			break;
	}

	switch (vdir) {
		case -1:
			if (act->vel.y > -act->spd.y) act->vel.y -= act->acc.y;
			else act->vel.y = -act->spd.y;
			if (act->col.t) act->vel.y = 0;
			break;
		case 0:
			if (act->vel.y < 0) act->vel.y += act->acc.y;
			else if (act->vel.y > 0) act->vel.y -= act->acc.y;
			else act->vel.y = 0;
			break;
		case 1:
			if (act->vel.y < act->spd.y) act->vel.y += act->acc.y;
			else act->vel.y = act->spd.y;
			if (act->col.b) act->vel.y = 0;
			break;
		default:
			break;
	}

	haz_physics(act);
}

void haz_physics(haz_actor *act) {
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
