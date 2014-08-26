/*
   This file is part of ledbanner.

    ledbanner is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ledbanner is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ledbanner.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ledbanner.h"
#include "banner.h"
#include "max7219.h"
#include "led_matrix_array.h"
#include "banner.h"


void init(void) {
  if (led_matrix_array_init(SPI_CHANNEL, SPI_SPEED)<0) {
    printf("Error while initializing.\n");
    exit(1);
  }
  max7219_set_intensity_all(BRIGHTNESS);
}

void scroll(char *str) {
  int char_pos;
  int l;
  int pix_pos;
  int mat;
  uint8_t **str_bitmap;
  uint8_t *char_bitmaps[4];
  int x;

  mat=4;
  while(mat--) {
    char_bitmaps[mat] = malloc(8*sizeof(uint8_t *));
  }
  l = strlen(str);
  str_bitmap = mk_str_bitmap(str);
  while(1) {
    char_pos = 0;
    while(char_pos < l) {
      pix_pos = 0;
      while(pix_pos<8) {
      	mat=0;
      	while(mat<4) {
	  x = (char_pos+mat)%l;
      	  get_window(str_bitmap, l, char_bitmaps[mat], x, pix_pos, 1);
      	  led_matrix_array_set_bitmap(3-mat, char_bitmaps[mat]);
	  mat++;
      	}
	led_matrix_array_refresh_all();
      	usleep(SLEEP_DELAY);
      	pix_pos++;
      }
      char_pos++;
    }
  }
}

int main(int argc, char** argv) {

  if(argc<2) {
    printf("Usage: %s <message>\n", argv[0]);
    return 1;
  }
  init();
  scroll(argv[1]);
  return 0;
}
