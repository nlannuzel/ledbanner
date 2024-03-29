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
#include "bit_hacks.h"

//From http://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith64BitsDiv
uint8_t reverse_char(uint8_t c) {
  return (c * 0x0202020202ULL & 0x010884422010ULL) % 1023;
}
