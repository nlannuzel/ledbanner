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

#define SPI_CHANNEL		0
#define SPI_SPEED		500000
#define SLEEP_DELAY		1000*30
#define BRIGHTNESS		0x03

uint8_t smile[8] = {
  0b00000000,
  0b01100110,
  0b00000000,
  0b00011000,
  0b00011000,
  0b11000011,
  0b01000010,
  0b00111100
};

uint8_t off[8]={0,0,0,0,0,0,0,0};

void init(void);
void scroll(char *str);
int main(int argc, char** argv);
