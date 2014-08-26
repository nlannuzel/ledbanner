/*   This file is part of ledbanner.

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
#include <stdbool.h>
#include <max7219.h>

#define MATRIX_COUNT	4

int led_matrix_array_init(int spi_channel, int spi_speed);
uint8_t led_matrix_array_get_row(int mat, int row);
void led_matrix_array_set_row(int mat, int row, uint8_t value);
void led_matrix_array_set_row_col_on(int mat, int row, int col);
void led_matrix_array_set_row_col_off(int mat, int row, int col);
void led_matrix_array_refresh_row(int mat, int row);
void led_matrix_array_set_bitmap(int mat, uint8_t *bitmap);
