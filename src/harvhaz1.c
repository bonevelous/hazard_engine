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

haz_actor harv = {
	{0, 0, 16, 32},
	{false, false, false, false},
	{0, 0},
	{0, 0},
	{4, 4},
	{0, 0},
	NULL,
	SDL_FLIP_NONE
};

SDL_Point tsize = {16, 16};
SDL_Rect harvClip = {16, 0, 16, 32};
SDL_Rect testRect = {80, 96, 64, 64};

const int REN_SCALE_X = 2;
const int REN_SCALE_Y = 2;

SDL_Texture *renTex = NULL;
SDL_Rect renRect = {0, 0, 800, 600};

int haz_loadLevel(const char *filename) {
	FILE *_file = NULL;

	_file = fopen (filename, "r");
	if (_file == NULL) {
		printf("\x1b[1;31mError in fopen():\x1b[0m "
		       "\x1b[0;31m%s is corrupt or absent.\x1b[0m\n", filename);
		return 1;
	}

	tsize = get_tsize();

	for (int i = 0; i < MAP_W; i++) {
		for (int j = 0; j < MAP_H; j++) {
			int ch = '\n';
			while (ch == '\n') ch = fgetc(_file);
			if (ch == 'O') {
				harv.rect.x = tsize.x * j;
				harv.rect.y = tsize.y * i - (harvClip.h / 2);
				ch = ' ';
			}

			haz_setTile(ch, i, j);
		}
	}

	fclose(_file);
	_file = NULL;

	return 0;
}

int haz_loadTextures(SDL_Renderer *ren) {
	SDL_Rect tmpRect = haz_getWinRect();
	renRect.w = tmpRect.w / REN_SCALE_X;
	renRect.h = tmpRect.h / REN_SCALE_Y;

	renTex = SDL_CreateTexture(
	         ren,
                 SDL_PIXELFORMAT_RGBA4444,
	         SDL_TEXTUREACCESS_TARGET,
	         renRect.w,
	         renRect.h);

	if (renTex == NULL) {
		printf("\x1b[0;31mError in "
			"SDL_CreateTexture():\x1b[0m "
			"\x1b[0;31m%s\x1b[0m\n", SDL_GetError());
		return 1;
	}

	harv.tex = IMG_LoadTexture(ren, "../src/img/harv.png");
	if (harv.tex == NULL) {
		printf("\x1b[0;31mError in "
			"IMG_LoadTexture():\x1b[0m "
			"\x1b[0;31m%s\x1b[0m\n", IMG_GetError());
		return 1;
	}

	return 0;
}

void haz_cleanTextures() {
	SDL_DestroyTexture(harv.tex);
	harv.tex = NULL;

	SDL_DestroyTexture(renTex);
	renTex = NULL;
}

void haz_renderLevel(SDL_Renderer *ren) {
	SDL_SetRenderTarget(ren, renTex);

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(ren);

	SDL_Rect _out = {0, 0, tsize.x, tsize.y};

	for (int i = 0; i < MAP_W; i++) {
		_out.x = (tsize.x * i);
		for (int j = 0; j < MAP_H; j++) {
			_out.y = (tsize.y * j);
			SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

			if (haz_getTile(j, i) == '#') SDL_RenderFillRect(ren, &_out);
		}
	}

	haz_update(&harv);
	haz_collision(&harv, testRect);
	haz_eightDirMov(&harv);

	SDL_Rect winrect = haz_getWinRect();
	haz_containInRect(&harv, renRect);

	SDL_RenderCopyEx(ren, harv.tex, &harvClip, &harv.rect, 0, NULL, harv.flip);

	SDL_SetRenderDrawColor(ren, 0x55, 0x55, 0xff, 0xff);
	SDL_RenderFillRect(ren, &testRect);

	SDL_SetRenderTarget(ren, NULL);

	SDL_RenderCopy(ren, renTex, NULL, NULL);
}
