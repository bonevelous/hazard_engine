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

hazard_engine haz = {
	NULL,
	NULL,
	"Hazard Engine",
	SDL_WINDOWPOS_UNDEFINED,
	{0, 0, 800, 600},
	SDL_WINDOW_RESIZABLE,
	SDL_RENDERER_ACCELERATED,
	true
};

bool debug = false;

int haz_init(int argc, char **argv) {
	if (haz_getDebug()) {
		char cwd[PATH_MAX];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("%s ran from \x1b[1;34m%s\x1b[0m\n", argv[0], cwd);
		} else {
			printf("\x1b[1;31mgetcwd() error\x1b[0m\n");
			return 1;
		}
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("\x1b[1;31mError in SDL_Init():\x1b[0m "
			"\x1b[0;31m%s\x1b[0m\n", SDL_GetError());
		return 1;
	}

	haz.w = SDL_CreateWindow(haz.t, haz.p, haz.p, haz.g.w, haz.g.h, haz.wf);
	if (haz.w == NULL) {
		printf("\x1b[1;31mError in "
			"SDL_CreateWindow():\x1b[0m "
			"\x1b[0;31m%s\x1b[0m\n", SDL_GetError());
		return 1;
	}

	haz.r = SDL_CreateRenderer(haz.w, -1, haz.rf);
	if (haz.r == NULL) {
		printf("\x1b[0;31mError in "
			"SDL_CreateRenderer():\x1b[0m "
			"\x1b[0;31m%s\x1b[0m\n", SDL_GetError());
		return 1;
	}

	if (haz_loadLevel("../src/lvl/test.txt") != 0) {
		printf("\x1b[0;31mError in haz_loadLevel().\x1b[0m\n");
		return 1;
	}

	return 0;
}

bool haz_live() { return haz.live; }

void haz_setDebug() { debug = !debug; }
bool haz_getDebug() { return debug; }

void haz_eng() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) haz_pollEv(&event);

	haz_render(30000000);
}

void haz_pollEv(SDL_Event *_ev) {
	int _key;

	switch (_ev->type) {
		case SDL_QUIT:
			haz_quit();
			break;
		case SDL_KEYDOWN:
			_key = _ev->key.keysym.sym;
			break;
		default:
			break;
	}

	switch (_key) {
		case SDLK_ESCAPE:
			haz_quit();
			break;
		default:
			break;
	}
}

void haz_activeActor(haz_actor *_act) {
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	bool movl = (keystate[SDL_SCANCODE_LEFT]) ? true : false;
	bool movr = (keystate[SDL_SCANCODE_RIGHT]) ? true : false;
	bool movu = (keystate[SDL_SCANCODE_UP]) ? true : false;
	bool movd = (keystate[SDL_SCANCODE_DOWN]) ? true : false;

	if (movl) _act->vel.x = -_act->spd.x;
	if (movr) _act->vel.x = _act->spd.x;
	if (!movl && !movr) _act->vel.x = 0;
	if (movu) _act->vel.y = -_act->spd.y;
	if (movd) _act->vel.y = _act->spd.y;
	if (!movu && !movd) _act->vel.y = 0;

	_act->g.x += _act->vel.x;
	if (_act->col) _act->g.x -= _act->vel.x;
	_act->g.y += _act->vel.y;
	if (_act->col) _act->g.y -= _act->vel.y;

	if (_act->g.x < 0) _act->g.x = 0;
	if (_act->g.x > haz.g.w - _act->g.w) _act->g.x = haz.g.w - _act->g.w;
	if (_act->g.y < 0) _act->g.y = 0;
	if (_act->g.y > haz.g.h - _act->g.h) _act->g.y = haz.g.h - _act->g.h;
}

void haz_collision(haz_actor *guest, SDL_Rect host) {
	int g_l = guest->g.x;// + guest->vel.x;
	int g_t = guest->g.y;// + guest->vel.y;
	int g_r = g_l + guest->g.w;
	int g_b = g_t + guest->g.h;

	int h_l = host.x;
	int h_t = host.y;
	int h_r = host.x + host.w;
	int h_b = host.y + host.h;

	guest->col = (g_l > h_r || g_r < h_l || g_t > h_b || g_b < h_t) ? false : true;
}

void haz_render(int fps) {
	for (int i = 0; i < fps; i++) {
		if (i == 0) {
			SDL_SetRenderDrawColor(haz.r, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(haz.r);

			haz_renderLevel(haz.r);

			SDL_RenderPresent(haz.r);
		}
	}
}

void haz_quit() {
	haz.live = false;

	SDL_DestroyRenderer(haz.r);
	haz.r = NULL;

	SDL_DestroyWindow(haz.w);
	haz.w = NULL;

	SDL_Quit();
}
