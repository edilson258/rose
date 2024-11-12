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

  size_t tile_w = 100;
  size_t tile_h = 100;

  for (size_t y = 0; y < (canvas.height / tile_h); ++y)
  {
    for (size_t x = 0; x < (canvas.width / tile_w); ++x)
    {
      if ((y + x) % 2 == 0)
      {
        rose_fill_rect(&canvas, tile_w, tile_h, x * tile_w, y * tile_h, ROSE_COLOR_GREEN);
      }
    }
  }

  int res = rose_dump_to_ppm(&canvas, argv[1]);

  return res;
}
