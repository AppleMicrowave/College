#include "console.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "rk_structs.h"

int cell = 0;
memBuffer_t membuffer[4] = { 0 };
int bc[][2] = {
  { 0xE7E7FFFF, 0xFFFFE7E7 }, // 0  |
  { 0x1CDC7C3C, 0xFFFF1C1C }, // 1  |
  { 0xFF07FFFF, 0xFFFFE0FF }, // 2  |
  { 0xFF07FFFF, 0xFFFF07FF }, // 3  |
  { 0xFFE7E7E7, 0x070707FF }, // 4  |
  { 0xFFE0FFFF, 0xFFFF07FF }, // 5  |
  { 0xFFE0FFFF, 0xFFFFE7FF }, // 6  |
  { 0x1C0EFFFE, 0x3838FE38 }, // 7  |
  { 0x7EE7FF7E, 0x7EFFE77E }, // 8  |
  { 0xFFE7FFFF, 0xFFFF07FF }, // 9  |
  { 0xFFE7FF7E, 0xE7E7E7FF }, // A  |
  { 0xFEE7FFFE, 0xFEFFE7FE }, // B  |
  { 0xE0E7FF7E, 0x7EFFE7E0 }, // C  |
  { 0xE7E7FFF8, 0xF8FFE7E7 }, // D  |
  { 0xFFE0FFFF, 0xFFFFE0FF }, // E  |
  { 0xFFE0FFFF, 0xE0E0E0FF }, // F  |
  { 0x7E180000, 0x00000018 }, // +  |
  { 0x7E000000, 0x00000000 }, // -  |
  { 0x1CDC7C3C, 0xFFFF1C1C }  // 1  |
};
bool flagUi;
