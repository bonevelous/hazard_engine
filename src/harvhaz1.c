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
#include "harvhaz1.h"

SDL_Rect playpos = {0, 0, 16, 16};

SDL_Point tsize = {16, 16};
char level[MAPW][MAPH];

int haz_loadLevel(const char *filename) {
	FILE *_file = NULL;

	_file = fopen (filename, "r");
	if (_file == NULL) {
		printf("\x1b[1;31mError in fopen():\x1b[0m "
			"\x1b[0;31m%s is corrupt or absent.\x1b[0m\n", filename);
		return 1;
	}

	for (int i = 0; i < MAPW; i++) {
		for (int j = 0; j < MAPH; j++) {
			int ch = '\n';
			while (ch == '\n') ch = fgetc(_file);
			if (ch == 'O') {
				playpos.x = tsize.x * j;
				playpos.y = tsize.y * i;
				ch = ' ';
			}

			level[i][j] = ch;
		}
	}

	fclose(_file);
	_file = NULL;

	return 0;
}

void movePlayer() {
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	SDL_Point trupos = {playpos.x / tsize.x, playpos.y / tsize.y};

	if (trupos.x < 0) playpos.x = (MAPW * tsize.x);
	if (trupos.x >= MAPW) playpos.x = -tsize.x;

	if (keystate[SDL_SCANCODE_LEFT]) playpos.x -= HSPEED;
	if (keystate[SDL_SCANCODE_RIGHT]) playpos.x += HSPEED;
	if (keystate[SDL_SCANCODE_UP]) playpos.y -= VSPEED;
	if (keystate[SDL_SCANCODE_DOWN]) playpos.y += VSPEED;
}

void haz_renderLevel(SDL_Renderer *ren) {
	SDL_Rect _out = {0, 0, tsize.x, tsize.y};

	for (int i = 0; i < MAPW; i++) {
		_out.x = (tsize.x * i);
		for (int j = 0; j < MAPH; j++) {
			_out.y = (tsize.y * j);
			SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

			if (level[j][i] == '#') SDL_RenderFillRect(ren, &_out);
		}
	}

	movePlayer();

	SDL_SetRenderDrawColor(ren, 0x00, 0xAA, 0x00, 0xFF);
	SDL_RenderFillRect(ren, &playpos);
}