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
#include "hazbuild.h"

SDL_Point tsize;

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

			haz_setTile(ch, i, j);
		}
	}

	fclose(_file);
	_file = NULL;

	return 0;
}

int haz_loadTextures(SDL_Renderer *ren) {
	/*harv.tex = IMG_LoadTexture(ren, "../src/img/harv.png");
	if (harv.tex == NULL) {
		printf("\x1b[0;31mError in "
			"IMG_LoadTexture():\x1b[0m "
			"\x1b[0;31m%s\x1b[0m\n", IMG_GetError());
		return 1;
	}*/

	return 0;
}

void hb_renderMap(SDL_Renderer *ren, char _ch, SDL_Rect *pos) {
	switch (_ch) {
		case '#':
			SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderFillRect(ren, pos);
			break;
		case 'O':
			SDL_SetRenderDrawColor(ren, 0x00, 0xAA, 0x00, 0xFF);
			SDL_RenderFillRect(ren, pos);
			break;
		default:
			break;
	}
}

void haz_renderLevel(SDL_Renderer *ren) {
	SDL_Rect _out = {0, 0, tsize.x, tsize.y};

	for (int i = 0; i < MAP_W; i++) {
		_out.x = (tsize.x * i);
		for (int j = 0; j < MAP_H; j++) {
			_out.y = (tsize.y * j);

			hb_renderMap(ren, haz_getTile(j, i), &_out);
		}
	}
}

