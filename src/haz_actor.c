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

void haz_collision(haz_actor *guest, SDL_Rect host) {
	int g_l = guest->g.x;
	int g_t = guest->g.y;
	int g_r = guest->g.x + guest->g.w - 1;
	int g_b = guest->g.y + guest->g.h - 1;

	int h_l = host.x;
	int h_t = host.y;
	int h_r = host.x + host.w - 1;
	int h_b = host.y + host.h - 1;
}

void haz_eightDirMov(haz_actor *_act) {
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	int hdir = 0;
	int vdir = 0;

	if (keystate[SDL_SCANCODE_LEFT]) hdir = -1;
	if (keystate[SDL_SCANCODE_RIGHT]) hdir = 1;
	if (!keystate[SDL_SCANCODE_LEFT] && !keystate[SDL_SCANCODE_RIGHT]) hdir = 0;

	if (keystate[SDL_SCANCODE_UP]) vdir = -1;
	if (keystate[SDL_SCANCODE_DOWN]) vdir = 1;
	if (!keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_DOWN]) vdir = 0;

	switch (hdir) {
		case -1:
			if (_act->vel.x > -_act->spd.x) _act->vel.x -= _act->acc.x;
			else _act->vel.x = -_act->spd.x;
			break;
		case 0:
			if (_act->vel.x < 0) _act->vel.x += _act->acc.x;
			else if (_act->vel.x > 0) _act->vel.x -= _act->acc.x;
			else _act->vel.x = 0;
			break;
		case 1:
			if (_act->vel.x < _act->spd.x) _act->vel.x += _act->acc.x;
			else _act->vel.x = _act->spd.x;
			break;
		default:
			break;
	}

	switch (vdir) {
		case -1:
			if (_act->vel.y > -_act->spd.y) _act->vel.y -= _act->acc.y;
			else _act->vel.y = -_act->spd.y;
			break;
		case 0:
			if (_act->vel.y < 0) _act->vel.y += _act->acc.y;
			else if (_act->vel.y > 0) _act->vel.y -= _act->acc.y;
			else _act->vel.y = 0;
			break;
		case 1:
			if (_act->vel.y < _act->spd.y) _act->vel.y += _act->acc.y;
			else _act->vel.y = _act->spd.y;
			break;
		default:
			break;
	}

	haz_physics(_act);
}

void haz_physics(haz_actor *_act) {
	_act->g.x += _act->vel.x;
	_act->g.y += _act->vel.y;
}

void haz_containInRect(haz_actor *guest, SDL_Rect host) {
	int max_x = (host.x + host.w) - guest->g.w;
	int max_y = (host.y + host.h) - guest->g.h;

	if (guest->g.x < host.x) guest->g.x = host.x;
	if (guest->g.x > max_x) guest->g.x = max_x;
	if (guest->g.y < host.y) guest->g.y = host.y;
	if (guest->g.y > max_y) guest->g.y = max_y;
}
