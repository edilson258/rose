#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../include/rose.h"

void rose_fill(struct rose_canvas *c, uint32_t color)
{
  for (size_t cursor = 0; cursor < c->width * c->height; ++cursor)
  {
    c->pixels[cursor] = color;
  }
}

void rose_fill_rect(struct rose_canvas *c, size_t rect_w, size_t rect_h, size_t x0, size_t y0, uint32_t color)
{
  for (size_t dy = 0; dy < rect_h; ++dy)
  {
    size_t y = y0 + dy;
    if (y < c->height)
    {
      for (size_t dx = 0; dx < rect_w; ++dx)
      {
        size_t x = x0 + dx;
        if (x < c->width)
        {
          c->pixels[y * c->width + x] = color;
        }
      }
    }
  }
}

void rose_fill_circle(struct rose_canvas *c, size_t cx, size_t cy, size_t r, uint32_t color)
{
  for (int y = cy - r; y <= (int)(cy + r); y++)
  {
    for (int x = cx - r; x <= (int)(cx + r); x++)
    {
      if (x >= 0 && x < (int)c->width && y >= 0 && y < (int)c->height)
      {
        if (sqrt((x - cx) * (x - cx) + (y - cy) * (y - (int)cy)) <= r)
        {
          c->pixels[y * c->width + x] = color;
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

  for (size_t cursor = 0; cursor < c->width * c->height; ++cursor)
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
