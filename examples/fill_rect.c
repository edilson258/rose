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

  size_t rect_w        = 200;
  size_t rect_h        = 200;
  size_t rect_x_center = canvas.width / 2 - rect_w / 2;
  size_t rect_y_center = canvas.height / 2 - rect_h / 2;
  rose_fill_rect(&canvas, rect_w, rect_h, rect_x_center, rect_y_center, ROSE_COLOR_GREEN);

  int res = rose_dump_to_ppm(&canvas, argv[1]);

  return res;
}
