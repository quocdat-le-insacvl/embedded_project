// Plays polyphonic music using 3 interrupts
// Playtune library is   required: https://github.com/LenShustek/arduino-playtune
// 2019 - Marcelo Maximiano   - Maxblitz.com

#include <Playtune.h>

const byte PROGMEM avengers[]   = {
0x90,0x3E,0x00,0x7A,0x80,0x00,0x02,0x90,0x3E,0x00,0x7A,0x80,0x00,0x02,0x90,0x3E,
0x00,0x7A,0x80,0x01,0x79,0x90,0x3E,0x00,0x7A,0x80,0x00,0x02,0x90,0x3E,0x00,0x7A,
0x80,0x00,0x02,0x90,0x3E,0x00,0x7A,0x80,0x01,0x79,0x90,0x3E,0x00,0x7A,0x80,0x00,
0x02,0x90,0x3E,0x00,0x7A,0x80,0x00,0x02,0x90,0x3E,0x00,0x7A,0x80,0x00,0x02,0x90,
0x3E,0x00,0x7A,0x80,0x00,0x02,0x90,0x3F,0x00,0x7A,0x80,0x00,0x02,0x90,0x3F,0x00,
0x7A,0x80,0x00,0x02,0x90,0x3F,0x00,0x7A,0x80,0x01,0x79,0x90,0x3F,0x00,0x7A,0x80,
0x00,0x02,0x90,0x3F,0x00,0x7A,0x80,0x00,0x02,0x90,0x40,0x00,0x7A,0x80,0x01,0x79,
0x90,0x40,0x00,0x7A,0x80,0x00,0x02,0x90,0x40,0x00,0x7A,0x80,0x00,0x02,0x90,0x40,
0x00,0x7A,0x80,0x00,0x02,0x90,0x40,0x00,0x7A,0x80,0x00,0x02,0x90,0x41,0x00,0x7A,
0x80,0x00,0x02,0x90,0x41,0x00,0x7A,0x80,0x00,0x02,0x90,0x41,0x00,0x7A,0x80,0x01,
0x79,0x90,0x41,0x00,0x7A,0x80,0x00,0x02,0x90,0x41,0x00,0x7A,0x80,0x00,0x02,0x90,
0x40,0x00,0x7A,0x80,0x01,0x79,0x90,0x40,0x00,0x7A,0x80,0x00,0x02,0x90,0x40,0x00,
0x7A,0x80,0x00,0x02,0x90,0x40,0x00,0x7A,0x80,0x00,0x02,0x90,0x40,0x00,0x7A,0x80,
0x00,0x02,0x90,0x3F,0x00,0x7A,0x80,0x00,0x02,0x90,0x3F,0x00,0x7A,0x80,0x00,0x02,
0x90,0x3F,0x00,0x7A,0x80,0x01,0x79,0x90,0x3F,0x00,0x7A,0x80,0x00,0x02,0x90,0x3F,
0x00,0x7A,0x80,0x00,0x02,0x90,0x3A,0x00,0xF7,0x80,0x00,0xFC,0x90,0x3C,0x00,0xF7,
0x80,0x00,0xFC,0x90,0x4A,0x91,0x37,0x92,0x4F,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,
0x3E,0x91,0x4A,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x3E,0x91,0x4A,0x00,0x7A,0x80,
0x81,0x01,0x79,0x90,0x3E,0x91,0x4A,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x3E,0x91,
0x4A,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x3E,0x91,0x4A,0x00,0x7A,0x80,0x81,0x01,
0x79,0x90,0x3E,0x91,0x4A,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x3E,0x91,0x4A,0x00,
0x7A,0x80,0x81,0x00,0x02,0x90,0x3E,0x91,0x4A,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,
0x3E,0x91,0x4A,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,0x92,0x4F,0x90,0x3F,0x91,0x4B,
0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x3F,0x91,0x4B,0x00,0x7A,0x80,0x81,0x00,0x02,
0x90,0x3F,0x91,0x4B,0x00,0x7A,0x80,0x81,0x01,0x79,0x90,0x3F,0x91,0x4B,0x00,0x7A,
0x80,0x81,0x00,0x02,0x90,0x3F,0x91,0x4B,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x40,
0x91,0x4C,0x00,0x7A,0x80,0x81,0x01,0x79,0x90,0x40,0x91,0x4C,0x00,0x7A,0x80,0x81,
0x00,0x02,0x90,0x40,0x91,0x4C,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x40,0x91,0x4C,
0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x40,0x91,0x4C,0x00,0x7A,0x82,0x80,0x81,0x00,
0x02,0x92,0x4F,0x90,0x41,0x91,0x4D,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x41,0x91,
0x4D,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x41,0x91,0x4D,0x00,0x7A,0x80,0x81,0x01,
0x79,0x90,0x41,0x91,0x4D,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x41,0x91,0x4D,0x00,
0x7A,0x80,0x81,0x00,0x02,0x90,0x40,0x91,0x4C,0x00,0x7A,0x80,0x81,0x01,0x79,0x90,
0x40,0x91,0x4C,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x40,0x91,0x4C,0x00,0x7A,0x80,
0x81,0x00,0x02,0x90,0x40,0x91,0x4C,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x40,0x91,
0x4C,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,0x92,0x4F,0x90,0x3F,0x91,0x4B,0x00,0x7A,
0x80,0x81,0x00,0x02,0x90,0x3F,0x91,0x4B,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x3F,
0x91,0x4B,0x00,0x7A,0x80,0x81,0x01,0x79,0x90,0x3F,0x91,0x4B,0x00,0x7A,0x80,0x81,
0x00,0x02,0x90,0x3F,0x91,0x4B,0x00,0x7A,0x80,0x81,0x00,0x02,0x90,0x3A,0x91,0x46,
0x00,0xF7,0x80,0x81,0x00,0xFC,0x90,0x3C,0x91,0x48,0x00,0xF7,0x80,0x81,0x00,0xFA,
0x82,0x00,0x02,0x90,0x37,0x91,0x3E,0x92,0x4A,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,
0x3E,0x92,0x4A,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,0x00,0x7A,0x81,
0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,0x00,0x7A,0x81,0x82,
0x00,0x02,0x91,0x3E,0x92,0x4A,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,
0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,0x00,
0x7A,0x81,0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,
0x91,0x3E,0x92,0x4A,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x91,0x3E,0x92,
0x4A,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x90,0x3E,0x91,0x3F,0x92,0x4B,
0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x3F,0x92,0x4B,0x00,0x7A,0x81,0x82,0x00,0x02,
0x91,0x3F,0x92,0x4B,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,
0x00,0x02,0x90,0x3C,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x3C,0x80,
0x00,0x3E,0x82,0x00,0x02,0x91,0x3F,0x92,0x4B,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,
0x00,0x02,0x90,0x3A,0x91,0x3F,0x92,0x4B,0x00,0x3C,0x80,0x00,0x3E,0x81,0x82,0x00,
0x02,0x90,0x3A,0x91,0x40,0x92,0x4C,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4A,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,
0x82,0x00,0x02,0x90,0x3C,0x91,0x40,0x92,0x4C,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,
0x40,0x92,0x4C,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x40,0x92,0x4C,0x00,0x7A,0x80,
0x81,0x82,0x00,0x02,0x90,0x3E,0x91,0x40,0x92,0x4C,0x00,0x7A,0x80,0x81,0x82,0x00,
0x02,0x90,0x3E,0x91,0x41,0x92,0x4D,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x41,0x92,
0x4D,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x41,0x92,0x4D,0x00,0x7A,0x81,0x82,0x00,
0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x37,0x92,0x4F,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x91,0x41,0x92,0x4D,0x00,0x7A,0x81,
0x82,0x00,0x02,0x91,0x41,0x92,0x4D,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x40,0x92,
0x4C,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,0x91,0x40,0x92,
0x4C,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x91,0x40,0x92,0x4C,0x90,0x37,
0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x91,0x40,0x92,0x4C,0x90,0x37,0x00,0x7A,0x81,
0x82,0x80,0x00,0x02,0x91,0x40,0x92,0x4C,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,
0x02,0x90,0x3E,0x91,0x3F,0x92,0x4B,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x3F,0x92,
0x4B,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x3F,0x92,0x4B,0x00,0x7A,0x81,0x82,0x00,
0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x3C,0x92,0x4F,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4A,0x00,0x3C,0x80,0x00,0x3E,0x82,0x00,0x02,0x91,0x3F,0x92,0x4B,
0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x90,0x3A,0x91,0x3F,0x92,0x4B,0x00,
0x3C,0x80,0x00,0x3E,0x81,0x82,0x00,0x02,0x90,0x3A,0x91,0x3A,0x92,0x46,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x39,0x91,0x3C,0x92,0x48,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,
0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x37,0x91,0x3E,0x92,0x4A,0x00,0x7A,0x81,0x82,
0x00,0x02,0x91,0x3E,0x92,0x4A,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,
0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,0x00,
0x7A,0x81,0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,
0x3E,0x92,0x4A,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x91,0x3E,
0x92,0x4A,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,0x00,0x7A,0x80,0x81,
0x82,0x00,0x02,0x91,0x3E,0x92,0x4A,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,0x02,
0x91,0x3E,0x92,0x4A,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x90,0x3E,0x91,
0x3F,0x92,0x4B,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x3F,0x92,0x4B,0x00,0x7A,0x81,
0x82,0x00,0x02,0x91,0x3F,0x92,0x4B,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4F,0x00,
0x7A,0x80,0x82,0x00,0x02,0x90,0x3C,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,
0x00,0x3C,0x80,0x00,0x3E,0x82,0x00,0x02,0x91,0x3F,0x92,0x4B,0x90,0x37,0x00,0x7A,
0x81,0x82,0x80,0x00,0x02,0x90,0x3A,0x91,0x3F,0x92,0x4B,0x00,0x3C,0x80,0x00,0x3E,
0x81,0x82,0x00,0x02,0x90,0x3A,0x91,0x40,0x92,0x4C,0x00,0x7A,0x81,0x82,0x00,0x02,
0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,
0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x3C,0x91,0x40,0x92,0x4C,0x00,0x7A,0x81,0x82,
0x00,0x02,0x91,0x40,0x92,0x4C,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x40,0x92,0x4C,
0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3E,0x91,0x40,0x92,0x4C,0x00,0x7A,0x80,
0x81,0x82,0x00,0x02,0x90,0x3E,0x91,0x41,0x92,0x4D,0x00,0x7A,0x81,0x82,0x00,0x02,
0x91,0x41,0x92,0x4D,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x41,0x92,0x4D,0x00,0x7A,
0x81,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x37,0x92,0x4F,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x91,0x41,0x92,0x4D,
0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x41,0x92,0x4D,0x00,0x7A,0x81,0x82,0x00,0x02,
0x91,0x40,0x92,0x4C,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,
0x91,0x40,0x92,0x4C,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x91,0x40,0x92,
0x4C,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x91,0x40,0x92,0x4C,0x90,0x37,
0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x91,0x40,0x92,0x4C,0x90,0x37,0x00,0x7A,0x81,
0x82,0x80,0x00,0x02,0x90,0x3E,0x91,0x3F,0x92,0x4B,0x00,0x7A,0x81,0x82,0x00,0x02,
0x91,0x3F,0x92,0x4B,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x3F,0x92,0x4B,0x00,0x7A,
0x81,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x3C,0x92,0x4F,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x3C,0x80,0x00,0x3E,0x82,0x00,0x02,0x91,
0x3F,0x92,0x4B,0x90,0x37,0x00,0x7A,0x81,0x82,0x80,0x00,0x02,0x90,0x3A,0x91,0x3F,
0x92,0x4B,0x00,0x3C,0x80,0x00,0x3E,0x81,0x82,0x00,0x02,0x90,0x3A,0x91,0x3A,0x92,
0x46,0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x39,0x91,0x3C,0x92,0x48,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x4F,0x91,0x37,0x92,0x3E,0x00,
0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,
0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,
0x02,0x92,0x3E,0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,0x7A,0x80,0x81,0x82,0x00,
0x02,0x92,0x3E,0x90,0x4A,0x91,0x37,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,0x92,0x3E,
0x90,0x4A,0x91,0x37,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,0x90,0x56,0x91,0x3E,0x92,
0x3F,0x00,0x7A,0x82,0x00,0x02,0x92,0x3F,0x00,0x7A,0x82,0x00,0x02,0x92,0x3F,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x54,0x91,
0x3C,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x3C,0x80,0x81,0x00,0x3E,
0x82,0x00,0x02,0x92,0x3F,0x90,0x4B,0x91,0x37,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,
0x90,0x52,0x91,0x3A,0x92,0x3F,0x00,0x3C,0x80,0x81,0x00,0x3E,0x82,0x00,0x02,0x90,
0x52,0x91,0x3A,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,
0x02,0x90,0x54,0x91,0x3C,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,
0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x56,0x91,0x3E,
0x92,0x40,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x56,0x91,0x3E,0x92,0x41,0x00,
0x7A,0x82,0x00,0x02,0x92,0x41,0x00,0x7A,0x82,0x00,0x02,0x92,0x41,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x4F,0x91,0x37,0x92,
0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x41,0x00,
0x7A,0x82,0x00,0x02,0x92,0x41,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x92,0x40,0x90,0x4C,0x91,0x37,0x00,
0x7A,0x82,0x80,0x81,0x00,0x02,0x92,0x40,0x90,0x4C,0x91,0x37,0x00,0x7A,0x82,0x80,
0x81,0x00,0x02,0x92,0x40,0x90,0x4C,0x91,0x37,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,
0x92,0x40,0x90,0x4C,0x91,0x37,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,0x90,0x56,0x91,
0x3E,0x92,0x3F,0x00,0x7A,0x82,0x00,0x02,0x92,0x3F,0x00,0x7A,0x82,0x00,0x02,0x92,
0x3F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,
0x54,0x91,0x3C,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x3C,0x80,0x81,
0x00,0x3E,0x82,0x00,0x02,0x92,0x3F,0x90,0x4B,0x91,0x37,0x00,0x7A,0x82,0x80,0x81,
0x00,0x02,0x90,0x52,0x91,0x3A,0x92,0x3F,0x00,0x3C,0x80,0x81,0x00,0x3E,0x82,0x00,
0x02,0x90,0x52,0x91,0x3A,0x92,0x3A,0x00,0x7A,0x00,0x02,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,
0x90,0x51,0x91,0x39,0x92,0x3C,0x00,0x7A,0x00,0x02,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,
0x4F,0x91,0x37,0x92,0x3E,0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,0x7A,0x82,0x00,
0x02,0x92,0x3E,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,
0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,0x00,0x7A,0x82,0x00,0x02,0x92,0x3E,
0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x92,0x3E,0x90,0x4A,0x91,0x37,0x00,0x7A,0x82,
0x80,0x81,0x00,0x02,0x92,0x3E,0x90,0x4A,0x91,0x37,0x00,0x7A,0x82,0x80,0x81,0x00,
0x02,0x90,0x56,0x91,0x3E,0x92,0x3F,0x00,0x7A,0x82,0x00,0x02,0x92,0x3F,0x00,0x7A,
0x82,0x00,0x02,0x92,0x3F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,
0x82,0x00,0x02,0x90,0x54,0x91,0x3C,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,
0x00,0x3C,0x80,0x81,0x00,0x3E,0x82,0x00,0x02,0x92,0x3F,0x90,0x4B,0x91,0x37,0x00,
0x7A,0x82,0x80,0x81,0x00,0x02,0x90,0x52,0x91,0x3A,0x92,0x3F,0x00,0x3C,0x80,0x81,
0x00,0x3E,0x82,0x00,0x02,0x90,0x52,0x91,0x3A,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,
0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x54,0x91,0x3C,0x92,0x40,0x00,0x7A,0x82,
0x00,0x02,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x80,0x81,0x82,
0x00,0x02,0x90,0x56,0x91,0x3E,0x92,0x40,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,
0x56,0x91,0x3E,0x92,0x41,0x00,0x7A,0x82,0x00,0x02,0x92,0x41,0x00,0x7A,0x82,0x00,
0x02,0x92,0x41,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,
0x02,0x90,0x4F,0x91,0x37,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,
0x82,0x00,0x02,0x92,0x41,0x00,0x7A,0x82,0x00,0x02,0x92,0x41,0x00,0x7A,0x82,0x00,
0x02,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x92,
0x40,0x90,0x4C,0x91,0x37,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,0x92,0x40,0x90,0x4C,
0x91,0x37,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,0x92,0x40,0x90,0x4C,0x91,0x37,0x00,
0x7A,0x82,0x80,0x81,0x00,0x02,0x92,0x40,0x90,0x4C,0x91,0x37,0x00,0x7A,0x82,0x80,
0x81,0x00,0x02,0x90,0x56,0x91,0x3E,0x92,0x3F,0x00,0x7A,0x82,0x00,0x02,0x92,0x3F,
0x00,0x7A,0x82,0x00,0x02,0x92,0x3F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,
0x80,0x81,0x82,0x00,0x02,0x90,0x54,0x91,0x3C,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4A,0x00,0x3C,0x80,0x81,0x00,0x3E,0x82,0x00,0x02,0x92,0x3F,0x90,0x4B,0x91,
0x37,0x00,0x7A,0x82,0x80,0x81,0x00,0x02,0x90,0x52,0x91,0x3A,0x92,0x3F,0x00,0x3C,
0x80,0x81,0x00,0x3E,0x82,0x00,0x02,0x90,0x52,0x91,0x3A,0x92,0x3A,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,
0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x51,0x91,0x39,0x92,0x3C,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,
0x80,0x81,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,
0x02,0x91,0x37,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x81,0x82,0x00,0x02,
0x91,0x43,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x81,0x82,0x00,0x02,0x90,0x37,0x92,0x4F,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,
0x00,0x7A,0x82,0x00,0x02,0x91,0x3C,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,
0x02,0x91,0x3E,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x81,0x82,
0x00,0x02,0x91,0x3A,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x81,
0x82,0x00,0x02,0x91,0x37,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x81,0x82,
0x00,0x02,0x91,0x43,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x81,0x82,0x00,0x02,0x90,0x3F,0x91,
0x3C,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3E,0x91,0x3B,0x92,
0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,0x92,0x4A,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x48,0x91,0x4C,0x92,0x54,0x00,
0x7A,0x81,0x00,0x02,0x91,0x48,0x00,0x7A,0x81,0x00,0x02,0x91,0x48,0x00,0x7A,0x81,
0x00,0x02,0x91,0x4C,0x00,0x7A,0x81,0x00,0x02,0x91,0x3C,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x00,0x02,0x91,0x48,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x00,0x02,0x91,
0x4C,0x00,0x7A,0x81,0x00,0x02,0x91,0x48,0x00,0x7A,0x81,0x00,0x02,0x91,0x48,0x00,
0x7A,0x81,0x00,0x02,0x91,0x4C,0x00,0x7A,0x81,0x00,0x02,0x91,0x41,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x00,0x02,0x91,0x4D,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x00,0x02,0x91,0x48,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x82,0x80,0x81,0x00,0x02,0x91,0x3E,0x92,0x56,0x90,0x4A,0x01,0xF4,0x01,0xF1,
0x00,0x02,0x03,0xE5,0x80,0x81,0x82,0x00,0x02,0x90,0x4C,0x92,0x4C,0x91,0x3B,0x01,
0xF4,0x01,0xF1,0x80,0x82,0x81,0x00,0x02,0x90,0x4B,0x92,0x4B,0x91,0x3B,0x03,0xE5,
0x80,0x82,0x81,0x00,0x02,0x92,0x43,0x91,0x43,0x90,0x40,0x00,0x7A,0x82,0x81,0x00,
0x02,0x92,0x43,0x91,0x43,0x00,0x7A,0x82,0x81,0x00,0x02,0x92,0x40,0x91,0x40,0x00,
0x7A,0x82,0x81,0x00,0x02,0x92,0x40,0x91,0x40,0x00,0x7A,0x82,0x81,0x00,0x02,0x92,
0x40,0x91,0x40,0x00,0x7A,0x82,0x81,0x00,0x02,0x92,0x40,0x91,0x40,0x00,0x7A,0x82,
0x81,0x00,0x02,0x92,0x43,0x91,0x43,0x00,0x7A,0x82,0x81,0x00,0x02,0x92,0x43,0x91,
0x43,0x00,0x7A,0x82,0x81,0x00,0x02,0x92,0x43,0x91,0x43,0x00,0x7A,0x82,0x81,0x00,
0x02,0x92,0x43,0x91,0x43,0x00,0x7A,0x82,0x81,0x00,0x02,0x92,0x40,0x91,0x40,0x00,
0x7A,0x82,0x81,0x00,0x02,0x92,0x40,0x91,0x40,0x00,0x7A,0x82,0x81,0x00,0x02,0x92,
0x40,0x91,0x40,0x00,0x7A,0x82,0x81,0x00,0x02,0x92,0x40,0x91,0x40,0x00,0x7A,0x82,
0x81,0x00,0x02,0x92,0x43,0x91,0x43,0x00,0x7A,0x82,0x81,0x00,0x02,0x92,0x43,0x91,
0x43,0x00,0x7A,0x80,0x82,0x81,0x00,0x02,0x90,0x3C,0x91,0x40,0x92,0x43,0x00,0x7A,
0x82,0x00,0x02,0x92,0x43,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x82,0x00,
0x02,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x82,0x00,0x02,0x92,0x47,0x00,0x7A,0x00,0x02,0x00,0x7A,0x80,0x81,
0x82,0x00,0x02,0x90,0x3D,0x91,0x40,0x92,0x45,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3C,0x91,0x40,
0x92,0x43,0x00,0x7A,0x82,0x00,0x02,0x92,0x43,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,
0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,
0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,0x92,0x43,0x00,0x7A,0x82,0x00,
0x02,0x92,0x43,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3E,0x91,0x42,0x92,0x43,
0x00,0x7A,0x82,0x00,0x02,0x92,0x43,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,
0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,0x92,0x40,0x00,0x7A,0x82,0x00,
0x02,0x92,0x40,0x00,0x7A,0x82,0x00,0x02,0x92,0x43,0x00,0x7A,0x82,0x00,0x02,0x92,
0x43,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x40,0x91,0x43,0x92,0x4F,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3C,
0x91,0x40,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4C,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x82,0x00,0x02,0x92,0x53,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3D,0x91,0x40,0x92,0x51,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x80,0x81,0x82,
0x00,0x02,0x90,0x3C,0x91,0x40,0x92,0x53,0x00,0x7A,0x82,0x00,0x02,0x92,0x53,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4E,0x00,0x7A,0x82,0x00,0x02,0x92,0x4E,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4E,0x00,0x7A,0x82,0x00,0x02,0x92,0x4E,0x00,0x7A,0x82,0x00,0x02,
0x92,0x53,0x00,0x7A,0x82,0x00,0x02,0x92,0x53,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,
0x90,0x3B,0x91,0x3F,0x92,0x53,0x00,0x7A,0x82,0x00,0x02,0x92,0x53,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4E,0x00,0x7A,0x82,0x00,0x02,0x92,0x4E,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4E,0x00,0x7A,0x82,0x00,0x02,0x92,0x4E,0x00,0x7A,0x82,0x00,0x02,0x92,0x53,
0x00,0x7A,0x82,0x00,0x02,0x92,0x53,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3C,
0x91,0x43,0x92,0x40,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x42,
0x92,0x3E,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x43,0x92,0x40,0x00,0x7A,0x80,0x81,
0x82,0x00,0x02,0x90,0x3E,0x91,0x45,0x92,0x42,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3C,0x91,0x56,
0x92,0x3E,0x00,0x7A,0x80,0x81,0x82,0x00,0x7F,0x90,0x3C,0x91,0x58,0x92,0x40,0x00,
0x7A,0x80,0x81,0x82,0x02,0x73,0x90,0x3C,0x91,0x58,0x92,0x40,0x00,0x7A,0x80,0x81,
0x82,0x00,0x7F,0x90,0x3E,0x91,0x5A,0x92,0x42,0x00,0x7A,0x80,0x81,0x82,0x02,0x73,
0x90,0x40,0x91,0x40,0x92,0x40,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x80,0x00,0x02,0x90,0x3C,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x40,0x92,0x4C,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x82,0x00,
0x02,0x91,0x40,0x92,0x4C,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,
0x47,0x92,0x53,0x00,0x7A,0x00,0x02,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3D,
0x91,0x45,0x92,0x51,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3C,0x91,0x43,0x92,0x4F,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,
0x90,0x3E,0x91,0x42,0x92,0x4E,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x40,0x91,0x40,0x92,0x4C,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x80,0x00,0x02,
0x90,0x3C,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x81,0x82,0x00,0x02,0x91,0x40,0x92,0x4C,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x40,0x92,0x4C,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,
0x00,0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,0x47,0x92,0x53,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3D,0x91,0x49,0x92,0x55,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,
0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x81,0x82,0x00,0x02,0x91,
0x45,0x92,0x51,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x80,0x81,0x82,0x00,0x02,0x90,0x3C,0x91,0x47,0x92,0x53,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,
0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x80,0x00,0x02,0x90,0x3B,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,
0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x00,0x02,0x00,0x7A,0x80,0x81,0x82,
0x00,0x02,0x90,0x43,0x92,0x4F,0x91,0x58,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4F,0x00,0x7A,0x80,0x82,0x00,0x02,0x90,0x40,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,
0x00,0x7A,0x82,0x81,0x00,0x02,0x92,0x4C,0x91,0x58,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,
0x7A,0x82,0x81,0x00,0x02,0x92,0x4F,0x91,0x58,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x81,
0x00,0x02,0x92,0x4F,0x91,0x5F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x80,
0x82,0x81,0x00,0x02,0x90,0x40,0x92,0x4F,0x91,0x5D,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,
0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,
0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,
0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4F,0x00,0x7A,0x80,0x82,0x81,0x00,0x02,0x90,0x40,0x92,0x4F,0x91,0x5B,
0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4F,0x00,0x7A,0x80,0x82,0x81,0x00,0x02,0x90,0x42,0x92,0x4F,0x91,0x5A,0x00,0x7A,
0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,
0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,
0x4C,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,0x7A,0x82,0x00,0x02,0x92,0x4F,0x00,
0x7A,0x80,0x82,0x81,0x00,0x02,0x90,0x3E,0x92,0x4F,0x91,0x58,0x00,0x7A,0x82,0x80,
0x00,0x02,0x92,0x4F,0x90,0x43,0x00,0x7A,0x82,0x80,0x00,0x02,0x90,0x40,0x92,0x4C,
0x00,0x7A,0x82,0x80,0x00,0x02,0x92,0x4C,0x90,0x40,0x00,0x7A,0x82,0x80,0x00,0x02,
0x92,0x4C,0x90,0x40,0x00,0x7A,0x82,0x80,0x00,0x02,0x92,0x4C,0x90,0x40,0x00,0x7A,
0x82,0x80,0x00,0x02,0x92,0x4F,0x90,0x43,0x00,0x7A,0x82,0x80,0x00,0x02,0x92,0x4F,
0x90,0x43,0x00,0x7A,0x82,0x80,0x00,0x02,0x90,0x40,0x92,0x4F,0x00,0x7A,0x82,0x80,
0x00,0x02,0x92,0x4F,0x90,0x43,0x00,0x7A,0x82,0x80,0x00,0x02,0x90,0x42,0x92,0x4C,
0x00,0x7A,0x82,0x80,0x00,0x02,0x92,0x4C,0x90,0x40,0x00,0x7A,0x82,0x80,0x00,0x02,
0x92,0x4C,0x90,0x40,0x00,0x7A,0x82,0x80,0x00,0x02,0x92,0x4C,0x90,0x40,0x00,0x7A,
0x82,0x80,0x00,0x02,0x92,0x4F,0x90,0x43,0x00,0x7A,0x82,0x80,0x00,0x02,0x92,0x4F,
0x90,0x43,0x00,0x7A,0x82,0x81,0x80,0x00,0x02,0x90,0x3E,0x92,0x4A,0x91,0x56,0x00,
0x7A,0x82,0x81,0x80,0x00,0x7F,0x92,0x4C,0x91,0x58,0x90,0x4C,0x00,0x7A,0x82,0x81,
0x80,0x02,0x73,0x92,0x4C,0x91,0x58,0x90,0x4C,0x00,0x7A,0x82,0x81,0x80,0x00,0x7F,
0x92,0x4E,0x91,0x5A,0x90,0x4E,0x00,0x7A,0x82,0x81,0x80,0x02,0x73,0x92,0x4C,0x91,
0x58,0x90,0x4C,0x0F,0x9D,0x82,0x81,0x80,0xF0};

Playtune   p;

void setup() {
  p.tune_initchan(10);
  p.tune_initchan(11);
   p.tune_initchan(12);
}

void loop() {
  p.tune_playscore(avengers);   // start
  while (p.tune_playing);     // wait while playing
  p.tune_delay(3000);          // do not use Arduino delay
}
