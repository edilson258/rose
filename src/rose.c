#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/rose.h"

#include <stdio.h>

void rose_fill(struct rose_canvas *c, uint32_t color)
{
  for (int cursor = 0; cursor < (int)(c->width * c->height); ++cursor)
  {
    c->pixels[cursor] = color;
  }
}

void rose_draw_line(struct rose_canvas *c, int x0, int y0, int x1, int y1)
{
  int dx  = abs(x1 - x0);
  int dy  = abs(y1 - y0);
  int sx  = (x0 < x1) ? 1 : -1;
  int sy  = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while (1)
  {
    c->pixels[y0 * c->width + x0] = ROSE_COLOR_GREEN;
    if (x0 == x1 && y0 == y1)
    {
      break;
    }
    int err2 = 2 * err;
    if (err2 > -dy)
    {
      err -= dy;
      x0 += sx;
    }
    if (err2 < dx)
    {
      err += dx;
      y0 += sy;
    }
  }
}

void rose_fill_rect(struct rose_canvas *c, int rect_w, int rect_h, int x0, int y0, uint32_t color)
{
  for (int dy = 0; dy < rect_h; ++dy)
  {
    int y = y0 + dy;
    if (0 <= y && y < (int)c->height)
    {
      for (int dx = 0; dx < rect_w; ++dx)
      {
        int x = x0 + dx;
        if (0 <= x && x < (int)c->width)
        {
          c->pixels[y * c->width + x] = color;
        }
      }
    }
  }
}

void rose_fill_circle(struct rose_canvas *c, int cx, int cy, int r, uint32_t color)
{
  for (int y = cy - r; y <= (int)(cy + r); y++)
  {
    if (0 <= y && y < (int)c->height)
    {
      for (int x = cx - r; x <= (int)(cx + r); x++)
      {
        if (0 <= x && x < (int)c->width)
        {
          if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r)
          {
            c->pixels[y * c->width + x] = color;
          }
        }
      }
    }
  }
}

int rose_dump_to_ppm(struct rose_canvas *c, const char *file_path)
{
  FILE *ppm_file = fopen(file_path, "wb");
  if (NULL == ppm_file)
  {
    fprintf(stderr, "[ROSE_ERROR] Couldn't open file '%s' to dump canvas as ppm: %s\n", file_path, strerror(errno));
    return -1;
  }

  // write ppm header
  fprintf(ppm_file, "P6\n%zu %zu 255\n", c->width, c->height);
  if (ferror(ppm_file))
  {
    fprintf(stderr, "[ROSE_ERROR] Couldn't write ppm header to file '%s': %s\n", file_path, strerror(errno));
    fclose(ppm_file);
    return -1;
  }

  for (int cursor = 0; cursor < (int)(c->width * c->height); ++cursor)
  {
    /**
     * Extract RGB channels and ignore A (alpha) because ppm format doesn't support it.
     * from '0xAABBGGRR' to 'RGB'
     */
    uint32_t pixel   = c->pixels[cursor];
    uint8_t bytes[3] = {
        (pixel >> (8 * 0)) & 0xFF,
        (pixel >> (8 * 1)) & 0xFF,
        (pixel >> (8 * 2)) & 0xFF,
    };
    fwrite(bytes, 1, sizeof(bytes), ppm_file);
    if (ferror(ppm_file))
    {
      fprintf(stderr, "[ROSE_ERROR] Couldn't write ppm body to file '%s': %s\n", file_path, strerror(errno));
      fclose(ppm_file);
      return -1;
    }
  }

  fclose(ppm_file);
  return 0;
}
