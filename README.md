# Rose Graphics

This a simple and naive implementation a low level graphics library in C.

I'm building this just to help me understand the fundamentals graphics primitives and U know that i don't have to tell to NOT use this in real world projects.

## Screenshots

1. [Draw line](./examples/draw_line.c) [(Bresenham's line algorithm)](https://youtu.be/CceepU1vIKo?si=SEfWOO-ldti5Dt6_)

![Line screenshot](./screenshots/line.png)

3. [Fill Rect](./examples/fill_rect.c)

![Rect screenshot](./screenshots/rect.png)

3. [Fill circle](./examples/fill_circle.c)

![Circle screenshot](./screenshots/circle.png)

4. [Checker pattern](./examples/checker_pattern.c)

![Checker screenshot](./screenshots/checker-pattern.png)


## Build and run examples

```shell
git clone https://github.com/edilson258/rose.git
cd rose 
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/examples/draw_line out.ppm
```
