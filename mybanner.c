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

#include "smile.h"
#include "banner.h"
#include "max7219.h"
#include "led_matrix_array.h"
#include "banner.h"

char smile[8] = {
  0b00000000,
  0b01100110,
  0b00000000,
  0b00011000,
  0b00011000,
  0b11000011,
  0b01000010,
  0b00111100
};

char off[8]={0,0,0,0,0,0,0,0};

void init(void) {
  if (led_matrix_array_init(SPI_CHANNEL, SPI_SPEED)<0) {
    printf("Error while initializing.\n");
    exit(1);
  }
  max7219_set_intensity_all(0x05);
}

void scroll(char *str) {
  int char_pos;
  int l;
  int pix_pos;
  int i;
  char **str_bitmap;
  char *chars[4];

  i=4;
  while(i--) {
    chars[i] = malloc(sizeof(char*));
  }
  str_bitmap = mk_str_bitmap(str);
  l = strlen(str);
  while(1) {
    char_pos = 0;
    while(char_pos < (l-0)) {
      pix_pos = 0;
      while(pix_pos<8) {
      	i=4;
      	while(i--) {
      	  get_window(str_bitmap, l, chars[3-i], (char_pos+i)%l, pix_pos, 1);
      	  led_matrix_array_set_bitmap(i, chars[i], 1);
      	}
      	usleep(1000*30);
      	pix_pos++;
      }
      char_pos++;
    }
  }
}


void main(int argc, char** argv) {

  printf("initializing...\n");
  init();
  scroll(argv[1]);
}
