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

#include "haz_engine.h"
#include "haz_actor.h"

void haz_eightDirMov(haz_actor *act) {
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	if (!keystate[SDL_SCANCODE_LEFT] &&
	    !keystate[SDL_SCANCODE_RIGHT]) act->tspd.x = 0;

	if (keystate[SDL_SCANCODE_LEFT] &&
	    keystate[SDL_SCANCODE_RIGHT]) act->tspd.x = 0;

	if (keystate[SDL_SCANCODE_LEFT]) {
		if (!act->col.l) act->tspd.x = -act->mspd.x;
		else act->tspd.x = 0;

		act->flip = SDL_FLIP_HORIZONTAL;
	}

	if (keystate[SDL_SCANCODE_RIGHT]) {
		if (!act->col.r) act->tspd.x = act->mspd.x;
		else act->tspd.x = 0;
		act->flip = SDL_FLIP_NONE;
	}

	if (!keystate[SDL_SCANCODE_UP] &&
	    !keystate[SDL_SCANCODE_DOWN]) act->tspd.y = 0;

	if (keystate[SDL_SCANCODE_UP] &&
	    keystate[SDL_SCANCODE_DOWN]) act->tspd.y = 0;

	if (keystate[SDL_SCANCODE_UP]) {
		if (!act->col.t) act->tspd.y = -act->mspd.y;
		else act->tspd.y = 0;
	}

	if (keystate[SDL_SCANCODE_DOWN]) {
		if (!act->col.b) act->tspd.y = act->mspd.y;
		else act->tspd.y = 0;
	}

	haz_physics(act);
}

void haz_blockEntry(haz_actor *act, SDL_Rect host) {
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	haz_geometry ag = {
		act->g.x,
		act->g.y,
		act->g.x + act->g.w - 1,
		act->g.y + act->g.h - 1
	};

	haz_geometry hg = {
		host.x,
		host.y,
		host.x + host.w - 1,
		host.y + host.h - 1
	};

	bool hrange = (ag.y1 > hg.y2 || ag.y2 < hg.y1) ? false : true;
	bool vrange = (ag.x1 > hg.x2 || ag.x2 < hg.x1) ? false : true;

	int nxp = 0;
	int nyp = 0;
	
	if (keystate[SDL_SCANCODE_LEFT]) {
		nxp = (-act->mspd.x / 2);

		act->col.l = (ag.x1 + nxp <= hg.x2 &&
		              ag.x1 >= hg.x2 &&
		              hrange) ? true : false;

		if (act->col.l) act->g.x = host.x + host.w;
	}

	if (keystate[SDL_SCANCODE_RIGHT]) {
		nxp = (act->mspd.x / 2);

		act->col.r = (ag.x2 + nxp >= hg.x1 &&
		              ag.x2 <= hg.x1 &&
		              hrange) ? true : false;

		if (act->col.r) act->g.x = host.x - act->g.w;
	}
	
	if (keystate[SDL_SCANCODE_UP] ^ keystate[SDL_SCANCODE_DOWN]) {
		if (keystate[SDL_SCANCODE_UP]) {
			nyp = (-act->mspd.y / 2);

			act->col.t = (ag.y1 + nyp <= hg.y2 &&
			              ag.y1 >= hg.y2 &&
			              vrange) ? true : false;

			if (act->col.t) act->g.y = host.y + host.h;
		}

		if (keystate[SDL_SCANCODE_DOWN]) {
			nyp = (act->mspd.y / 2);

			act->col.b = (ag.y2 + nyp >= hg.y1 &&
			              ag.y2 <= hg.y1 &&
			              vrange) ? true : false;

			if (act->col.b) act->g.y = host.y - act->g.h;
		}
	}
}

void haz_physics(haz_actor *act) {
	act->vel.x = act->tspd.x;
	act->vel.y = act->tspd.y;

	act->g.x += act->vel.x;
	act->g.y += act->vel.y;
}

void haz_containInRect(haz_actor *act, SDL_Rect host) {
	int max_x = (host.x + host.w) - act->g.w;
	int max_y = (host.y + host.h) - act->g.h;

	if (act->g.x < host.x) {
		act->g.x = host.x;
		act->tspd.x = 0;
		act->vel.x = 0;
	}

	if (act->g.x > max_x) {
		act->g.x = max_x;
		act->tspd.x = 0;
		act->vel.x = 0;
	}

	if (act->g.y < host.y) {
		act->g.y = host.y;
		act->tspd.y = 0;
		act->vel.y = 0;
	}

	if (act->g.y > max_y) {
		act->g.y = max_y;
		act->tspd.y = 0;
		act->vel.y = 0;
	}
}
