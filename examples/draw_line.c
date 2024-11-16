#include "../include/rose.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (2 < argc)
  {
    fprintf(stderr, "[ERROR] Provide out filename. Usage: ./%s out.ppm", argv[0]);
    return -1;
  }

  struct rose_canvas canvas = {
      .width  = 800,
      .height = 600,
      .pixels = malloc(sizeof(uint32_t) * (800 * 600)),
  };

  // set background
  rose_fill(&canvas, 0xFF232623);

  rose_draw_line(&canvas, 50, 50, 250, 400);

  int res = rose_dump_to_ppm(&canvas, argv[1]);

  return res;
}
