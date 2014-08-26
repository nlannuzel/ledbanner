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

#include <stdint.h>
#include <stdlib.h>
#include <max7219.h>
#include "bit_hacks.h"
#include "led_matrix_array.h"

static uint8_t *g_led_matrices[MATRIX_COUNT];

static uint8_t g_row_to_addr[] = {
  REG_ADDR_DIGIT0,
  REG_ADDR_DIGIT1,
  REG_ADDR_DIGIT2,
  REG_ADDR_DIGIT3,
  REG_ADDR_DIGIT4,
  REG_ADDR_DIGIT5,
  REG_ADDR_DIGIT6,
  REG_ADDR_DIGIT7,
};

int led_matrix_array_init(int spi_channel, int spi_speed) {
  int i;
  int mat;

  //allocate matrix
  mat=4;
  while(mat--) {
    g_led_matrices[mat] = malloc(8*sizeof(uint8_t));
  }
  if ( (max7219_init(spi_channel, spi_speed, MATRIX_COUNT)) < 0) {
    return -1;
  }

  // Exit shutdown mode
  max7219_set_shutdown_all(NORMAL_MODE);

  // enable all 8 rows
  max7219_send_data_all(REG_ADDR_SCAN_LIMIT, DISPLAY_0_TO_7);

  // Disable 7 segments mode
  max7219_set_decode_all(NO_DECODE);

  // set intensity to the max
  max7219_send_data_all(REG_ADDR_INTENSITY, 0x0F);

  // OFF the matrix
  mat=4;
  while(mat--) {
    i=8;
    while(i--) {
      led_matrix_array_set_row(mat, i, 0);
    }
  }
  return 0;
}

uint8_t led_matrix_array_get_row(int mat, int row) {
  return g_led_matrices[mat][row];
}

void led_matrix_array_set_row(int mat, int row, uint8_t value) {
  g_led_matrices[mat][row] = value;
}

void led_matrix_array_set_row_col_on(int mat, int row, int col) {
  uint8_t new_value;

  new_value = led_matrix_array_get_row(mat, row) | (1 << col);
  led_matrix_array_set_row(mat, row, new_value);
}

void led_matrix_array_set_row_col_off(int mat, int row, int col) {
  uint8_t new_value;

  new_value = led_matrix_array_get_row(mat, row) & (!(1 << col));
  led_matrix_array_set_row(mat, row, new_value);
}

void led_matrix_array_refresh_row_all(int row) {
  int mat;

  mat=4;
  while(mat--) {
    max7219_send_data(mat, g_row_to_addr[row], led_matrix_array_get_row(mat, row));
  }
}

void led_matrix_array_refresh_row(int mat, int row) {
  max7219_send_data(mat, g_row_to_addr[row], led_matrix_array_get_row(mat, row));
}

void led_matrix_array_refresh_all() {
  int row;
  int mat;
  uint8_t addresses[MATRIX_COUNT];
  uint8_t data[MATRIX_COUNT];

  row=8;
  while(row--) {
    mat = MATRIX_COUNT;
    while(mat--) {
      addresses[mat] = g_row_to_addr[row];
      data[mat] = led_matrix_array_get_row(mat, row);
      max7219_send_data_cascade(addresses, data, MATRIX_COUNT);
    }
  }
}

void led_matrix_array_set_bitmap(int mat, uint8_t *bitmap) {
  int i;

  i=0;
  while(i<8) {
    led_matrix_array_set_row(mat, i, bitmap[i]);
    i++;
  }
}
