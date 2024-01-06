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
	(SDL_INIT_VIDEO || SDL_INIT_GAMECONTROLLER || SDL_INIT_TIMER),
	NULL,
	NULL,
	"Hazard Engine",
	SDL_WINDOWPOS_UNDEFINED,
	{0, 0, 800, 600},
	SDL_WINDOW_RESIZABLE,
	SDL_RENDERER_ACCELERATED,
	{16, 16},
	true,
	false
};

char level[MAPW][MAPH];
SDL_Event e;
SDL_GameController *main_gc = NULL;

int haz_init(int argc, char **argv) {
	if (haz.debug) {
		char cwd[PATH_MAX];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("%s ran from \x1b[1;34m%s\x1b[0m\n", argv[0], cwd);
		} else {
			printf("\x1b[1;31mgetcwd() error\x1b[0m\n");
			return 1;
		}
	}

	if (SDL_Init(haz.initf) != 0) {
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

	main_gc = haz_findController();

	if (haz_loadLevel("../src/lvl/test.txt") != 0) {
		printf("\x1b[0;31mError in haz_loadLevel().\x1b[0m\n");
		return 1;
	}

	return 0;
}

void haz_setTile(char _ch, int x, int y) { level[x][y] = _ch; }
void haz_setDebug() { haz.debug = !haz.debug; }
char haz_getTile(int x, int y) { return level[x][y]; }
bool haz_live() { return haz.live; }
bool haz_getDebug() { return haz.debug; }
SDL_Rect haz_getWinGeom() { return haz.g; }
SDL_Point get_tsize() { return haz.tsize; }

SDL_GameController *haz_findController() {
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			printf("Found controller %i\n", i);
			return SDL_GameControllerOpen(i);
		}
	}

	return NULL;
}

void haz_eng() {
	if (SDL_PollEvent(&e)) haz_pollEv();

	haz_render(30);
}

void haz_pollEv() {
	int _key = 0;
	int _condir = -1;

	switch (e.type) {
		case SDL_QUIT:
			haz_quit();
			break;
		case SDL_KEYDOWN:
			_key = e.key.keysym.sym;
			break;
		case SDL_CONTROLLERDEVICEADDED:
			if (main_gc == NULL)
				main_gc = SDL_GameControllerOpen(e.cdevice.which);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			if (main_gc != NULL &&
			    e.cdevice.which == SDL_JoystickInstanceID(
			    SDL_GameControllerGetJoystick(main_gc))) {
				SDL_GameControllerClose(main_gc);
				main_gc = haz_findController();
			}
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
	for (int i = 0; i < (fps * 1000000); i++) {
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

	SDL_GameControllerClose(main_gc);
	main_gc = NULL;

	SDL_DestroyRenderer(haz.r);
	haz.r = NULL;

	SDL_DestroyWindow(haz.w);
	haz.w = NULL;

	SDL_Quit();
}
