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
void rose_draw_line(struct rose_canvas *c, int x0, int y0, int x1, int y1);
void rose_fill_rect(struct rose_canvas *c, int rect_w, int rect_h, int x0, int y0, uint32_t color);
void rose_fill_circle(struct rose_canvas *c, int cx, int cy, int r, uint32_t color);
int rose_dump_to_ppm(struct rose_canvas *c, const char *file_path);

#endif
