#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdio.h>
#include <stdlib.h>

int
sc_memorySave (char *filename)
{
  FILE *addressData = fopen (filename, "wb");
  if (addressData == NULL)
    {
      perror ("Error opening file");
      return -1;
    }

  if (fwrite (RAM, sizeof (int), 128, addressData) != 128)
    {
      fprintf (stderr, "Error writing to file\n");
      fclose (addressData);
      return -1;
    }

  fclose (addressData);
  return 0;
}
