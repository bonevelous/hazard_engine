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

void haz_eightDirMov(haz_actor *act, int *input, int *refFrame, int animspeed) {
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	bool hmov = (keystate[SDL_SCANCODE_LEFT] ^ keystate[SDL_SCANCODE_RIGHT]);
	bool vmov = (keystate[SDL_SCANCODE_UP] ^ keystate[SDL_SCANCODE_DOWN]);

	int anim_d[4] = {1, 0, 1, 2};
	int anim_u[4] = {7, 6, 7, 8};
	int anim_h[4] = {4, 3, 4, 5};

	if (!hmov) act->spd.x = 0;
	else {
		if (!vmov) haz_animate(anim_h, input, refFrame, animspeed);
		if (keystate[SDL_SCANCODE_LEFT]) {
			act->spd.x = -act->mvel.x;
			act->flip = SDL_FLIP_HORIZONTAL;
		}

		if (keystate[SDL_SCANCODE_RIGHT]) {
			act->spd.x = act->mvel.x;
			act->flip = SDL_FLIP_NONE;
		}
	}

	if (!vmov) act->spd.y = 0;
	else {
		if (keystate[SDL_SCANCODE_UP]) {
			haz_animate(anim_u, input, refFrame, animspeed);
			act->spd.y = -act->mvel.y;
		}

		if (keystate[SDL_SCANCODE_DOWN]) {
			haz_animate(anim_d, input, refFrame, animspeed);
			act->spd.y = act->mvel.y;
		}
	}
}

void haz_update(haz_actor *act) {
	if ((!act->col.l ^ act->spd.x >= 0) || (!act->col.r ^ act->spd.x <= 0)) {
		act->vel.x = act->spd.x;
	} else act->vel.x = 0;

	if ((!act->col.t ^ act->spd.y >= 0) || (!act->col.b ^ act->spd.y <= 0)) {
		act->vel.y = act->spd.y;
	} else act->vel.y = 0;

	act->rect.x += act->vel.x;
	act->rect.y += act->vel.y;
}

void haz_containInRect(haz_actor *act, SDL_Rect host) {
	int max_x = (host.x + host.w) - act->rect.w;
	int max_y = (host.y + host.h) - act->rect.h;

	if (act->rect.x < host.x) {
		act->rect.x = host.x;
		act->spd.x = 0;
		act->vel.x = 0;
	}

	if (act->rect.x > max_x) {
		act->rect.x = max_x;
		act->spd.x = 0;
		act->vel.x = 0;
	}

	if (act->rect.y < host.y) {
		act->rect.y = host.y;
		act->spd.y = 0;
		act->vel.y = 0;
	}

	if (act->rect.y > max_y) {
		act->rect.y = max_y;
		act->spd.y = 0;
		act->vel.y = 0;
	}
}

void haz_collision(haz_actor *act, SDL_Rect host) {
	if (!haz_hrange(act->rect, host)) {
		act->col.l = false;
		act->col.r = false;
	}
	else {
		if (act->rect.x == host.x + host.w) {
			act->col.l = true;
		}
		else act->col.l = false;

		if (act->rect.x == host.x - act->rect.w) {
			act->col.r = true;
		}
		else act->col.r = false;
	}

	if (!haz_vrange(act->rect, host)) {
		act->col.t = false;
		act->col.b = false;
	}
	else {
		if (act->rect.y == host.y + host.h) {
			act->col.t = true;
		}
		else act->col.t = false;

		if (act->rect.y == host.y - act->rect.h) {
			act->col.b = true;
		}
		else act->col.b = false;
	}

	haz_fixCorners(act, host);
}

void haz_fixCorners(haz_actor *act, SDL_Rect host) {
	bool corn1 = false;
	bool corn2 = false;
	bool corn3 = false;
	bool corn4 = false;

	int min_act_x = host.x - act->rect.w;
	int min_act_y = host.y - act->rect.h;
	int max_act_x = host.x + host.w;
	int max_act_y = host.y + host.h;

	corn1 = (act->rect.x == min_act_x && act->rect.y == min_act_y);
	corn2 = (act->rect.x == max_act_x && act->rect.y == min_act_y);
	corn3 = (act->rect.x == min_act_x && act->rect.y == max_act_y);
	corn4 = (act->rect.x == max_act_x && act->rect.y == max_act_y);

	if (corn1 && (act->spd.x > 0 ^ act->spd.y > 0)) {
		if (act->spd.x > 0) act->col.r = false;
		if (act->spd.y > 0) act->col.b = false;
	}

	if (corn2 && (act->spd.x < 0 ^ act->spd.y > 0)) {
		if (act->spd.x < 0) act->col.l = false;
		if (act->spd.y > 0) act->col.b = false;
	}

	if (corn3 && (act->spd.x > 0 ^ act->spd.y < 0)) {
		if (act->spd.x > 0) act->col.r = false;
		if (act->spd.y < 0) act->col.t = false;
	}

	if (corn4 && (act->spd.x < 0 ^ act->spd.y < 0)) {
		if (act->spd.x < 0) act->col.l = false;
		if (act->spd.y < 0) act->col.t = false;
	}
}

