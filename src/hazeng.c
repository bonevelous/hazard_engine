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
	1
};

int haz_init() {
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("hazbuild ran from \x1b[1;34m%s\x1b[0m\n", cwd);
	} else {
		printf("\x1b[1;31mgetcwd() error\x1b[0m\n");
		return 1;
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

int haz_live() { return haz.live; }

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
	haz.live = 0;

	SDL_DestroyRenderer(haz.r);
	haz.r = NULL;

	SDL_DestroyWindow(haz.w);
	haz.w = NULL;

	SDL_Quit();
}
