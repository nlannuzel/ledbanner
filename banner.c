/*
   This file is part of ledbanner.

   Ledbanner is free software: you can redistribute it and/or modify
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

#include "banner.h"
#include "led_matrix_array.h"
#include "max7219.h"
#include "bit_hacks.h"
#include "font8x8/font8x8_basic.h"

uint8_t **mk_str_bitmap(char *s) {
  uint8_t **bitmap;
  uint8_t *one_char;
  int i;
  uint8_t line;
  int l;

  l = strlen(s);
  bitmap = malloc(8 * sizeof(uint8_t*));
  line=8;
  while(line--) {
    bitmap[line] = malloc( l * sizeof(uint8_t));
  }

  i=l;
  while(i--) {
    one_char = (uint8_t *)font8x8_basic[(uint8_t)s[i]];
    line=8;
    while(line--) {
      bitmap[line][i] = reverse_char(one_char[line]);
    }    
  }
  return bitmap;
}

uint8_t scroll_char_left(uint8_t c1, uint8_t c2, int bits) {
  uint8_t c;
  uint32_t i;

  i = ( (c1<<8) + c2) << bits;
  c = i>>8;
  return c;
}

uint8_t scroll_char_right(uint8_t c1, uint8_t c2, int bits) {
  uint8_t c;
  uint32_t i;

  i = ( (c1<<8) + (c2<<16)) >> bits;
  c = i>>8;
  return c;
}

void get_window(uint8_t **str_bitmap, int length, uint8_t *char_bitmap, int char_pos, int bits, int circular) {
  int line;
  uint8_t c1;
  uint8_t c2;
  uint8_t c;

  line = 8;
  while(line--) {
    c1 = str_bitmap[line][char_pos];
    c2 = (char_pos + 1 < length) ? str_bitmap[line][char_pos+1] : circular ? str_bitmap[line][0] : 0x00;
    c = scroll_char_left(c1, c2, bits);
    char_bitmap[line] = c;
  }
}

void show_char_bitmap(const uint8_t *char_bitmap) {
  int line;

  line = 0;
  while(line<8) {
    printf("    | ");
    show_bits(char_bitmap[line]);
    printf("    |\n");
    line++;
  }
}

void show_bits(uint8_t c) {
  int i;

  i=8;
  printf("|");
  while(i--) {
    printf("%s", (c & (1<<i)) ? "X" : " ");
  }
  printf("|");
}
