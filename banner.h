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

#include <stdint.h>

uint8_t **mk_str_bitmap(char *s);
uint8_t scroll_char_left(uint8_t c1, uint8_t c2, int bits);
uint8_t scroll_char_right(uint8_t c1, uint8_t c2, int bits);
void get_window(uint8_t **str_bitmap, int length, uint8_t *char_bitmap, int char_pos, int bits, int circular);
void show_char_bitmap(const uint8_t *char_bitmap);
void show_bits(uint8_t c);
