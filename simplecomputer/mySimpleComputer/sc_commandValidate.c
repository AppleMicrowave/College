#include "mySimpleComputer.h"
#include "sc_variables.h"
#include <stdio.h>

int
sc_commandValidate (int command)
{
  switch (command)
    {
    case 0x0:
      return true;
      break;
    case 0x1:
      return true;
      break;
    case 0xa:
      return true;
      break;
    case 0xb:
      return true;
      break;
    case 0x14:
      return true;
      break;
    case 0x15:
      return true;
      break;
    case 0x1e:
      return true;
      break;
    case 0x1f:
      return true;
      break;
    case 0x20:
      return true;
      break;
    case 0x21:
      return true;
      break;
    case 0x28:
      return true;
      break;
    case 0x29:
      return true;
      break;
    case 0x2a:
      return true;
      break;
    case 0x2b:
      return true;
      break;
    case 0x33:
      return true;
      break;
    case 0x34:
      return true;
      break;
    case 0x35:
      return true;
      break;
    case 0x36:
      return true;
      break;
    case 0x37:
      return true;
      break;
    case 0x38:
      return true;
      break;
    case 0x39:
      return true;
      break;
    case 0x3a:
      return true;
      break;
    case 0x3b:
      return true;
      break;
    case 0x3c:
      return true;
      break;
    case 0x3d:
      return true;
      break;
    case 0x3e:
      return true;
      break;
    case 0x3f:
      return true;
      break;
    case 0x40:
      return true;
      break;
    case 0x41:
      return true;
      break;
    case 0x42:
      return true;
      break;
    case 0x43:
      return true;
      break;
    case 0x44:
      return true;
      break;
    case 0x45:
      return true;
      break;
    case 0x46:
      return true;
      break;
    case 0x47:
      return true;
      break;
    case 0x48:
      return true;
      break;
    case 0x49:
      return true;
      break;
    case 0x4a:
      return true;
      break;
    case 0x4b:
      return true;
      break;
    case 0x4c:
      return true;
      break;
    default:
      return false;
    }
}
