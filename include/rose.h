#ifndef ROSE_GRAPHICS
#define ROSE_GRAPHICS

#include <stddef.h>
#include <stdint.h>

#define ROSE_COLOR_RED 0xFF0000FF
#define ROSE_COLOR_GREEN 0xFF00FF00
#define ROSE_COLOR_BLUE 0xFFFF0000

struct rose_canvas
{
  size_t width;
  size_t height;
  uint32_t *pixels;
};

void rose_fill(struct rose_canvas *c, uint32_t color);
void rose_fill_rect(struct rose_canvas *c, size_t rect_w, size_t rect_h, size_t x0, size_t y0, uint32_t color);
void rose_fill_circle(struct rose_canvas *c, size_t cx, size_t cy, size_t r, uint32_t color);
int rose_dump_to_ppm(struct rose_canvas *c, const char *file_path);

#endif
