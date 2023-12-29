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
#include "cmake_macros.h"

static struct option longopt[] = {
	{"help", 0, 0, 'h'},
	{"version", 0, 0, 'v'},
	{"debug", 0, 0, 'd'},
	{0, 0, 0, 0}
};

char *progname = NULL;

int main (int argc, char **argv) {
	int c = 0;
	int getind = 0;

	c = getopt_long(argc, argv, "dhv", longopt, &getind);

	switch (c) {
		case 'h':
			printf("Usage: %s [OPTIONS] [FILE]...\n"
				"\t-h | --help\tDisplay this help message.\n"
				"\t-v | --version\tDisplay version info.\n"
				"\t-d | --debug\tSet to debug mode.\n",
				argv[0]);
				return 0;
			break;
		case 'v':
			printf("hazard engine version %i.%i, copyright 2023.\n"
				"This program is free software: See COPYING for"
				"more info.\n", hazard_engine_VERSION_MAJOR,
				hazard_engine_VERSION_MINOR);
				return 0;
			break;
		case 'd':
			haz_setDebug();
			break;
		case '?':
			printf("Invalid cli args, booting as normal...\n");
			break;
		default:
			break;
	}

	if (haz_init(argc, argv)) {
		printf("\x1b[0;31mFailed to start Harvey Hazard.\x1b[0m\n");
		return 1;
	}

	while (haz_live()) {
		haz_eng();
	}

	return 0;
}
