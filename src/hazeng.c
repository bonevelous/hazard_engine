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
	"Harvey Hazard",
	SDL_WINDOWPOS_UNDEFINED,
	{0, 0, 800, 600},
	SDL_WINDOW_RESIZABLE,
	SDL_RENDERER_ACCELERATED,
	1
};

int level[8][8];
SDL_Point tsize = {16, 16};

int haz_init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error in SDL_Init(): %s\n", SDL_GetError());
		return 1;
	}

	haz.w = SDL_CreateWindow(haz.t, haz.p, haz.p, haz.g.w, haz.g.h, haz.wf);
	if (haz.w == NULL) {
		printf("Error in SDL_CreateWindow(): %s\n", SDL_GetError());
		return 1;
	}

	haz.r = SDL_CreateRenderer(haz.w, -1, haz.rf);
	if (haz.r == NULL) {
		printf("Error in SDL_CreateRenderer(): %s\n", SDL_GetError());
		return 1;
	}

	if (haz_loadLevel("../src/levels/e1m1.txt") == 1) {
		printf("Error in haz_loadLevel().\n");
		return 1;
	}

	return 0;
}

int haz_loadLevel(const char *filename) {
	FILE *_file = NULL;

	_file = fopen (filename, "r");
	if (_file == NULL) {
		printf("Error in fopen(): %s is corrupt or absent.\n", filename);
		return 1;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int ch = '\n';
			while (ch == '\n') ch = fgetc(_file);

			level[i][j] = ch - 48;
			printf("%i", level[i][j]);
		}
		printf("\n");
	}

	fclose(_file);
	_file = NULL;

	return 0;
}

int haz_live() { return haz.live; }

void haz_eng() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) haz_pollEv(&event);

	haz_render();
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

void haz_renderLevel() {
	SDL_Rect _out = {0, 0, tsize.x, tsize.y};

	for (int i = 0; i < 8; i++) {
		_out.x = (tsize.x * i);
		for (int j = 0; j < 8; j++) {
			_out.y = (tsize.y * j);
			SDL_SetRenderDrawColor(haz.r, 0xFF, 0xFF, 0xFF, 0xFF);

			if (level[i][j] == 1) SDL_RenderFillRect(haz.r, &_out);
		}
	}
}

void haz_render() {
	SDL_SetRenderDrawColor(haz.r, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(haz.r);

	haz_renderLevel();

	SDL_RenderPresent(haz.r);
}

void haz_quit() {
	haz.live = 0;

	SDL_DestroyRenderer(haz.r);
	haz.r = NULL;

	SDL_DestroyWindow(haz.w);
	haz.w = NULL;

	SDL_Quit();
}
