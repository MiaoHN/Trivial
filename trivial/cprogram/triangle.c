#include <math.h>
#include <stdio.h>

struct Point {
  float x;
  float y;
};

struct Triangle {
  struct Point a;
  struct Point b;
  struct Point c;
};

float area(struct Triangle* t);

int main(int argc, char const* argv[]) {
  struct Triangle t;
  scanf("%f %f", &t.a.x, &t.a.y);
  scanf("%f %f", &t.b.x, &t.b.y);
  scanf("%f %f", &t.c.x, &t.c.y);
  printf("%.2f\n", area(&t));
  return 0;
}

float area(struct Triangle* t) {
  float a = sqrt((t->a.x - t->b.x) * (t->a.x - t->b.x) +
                 (t->a.y - t->b.y) * (t->a.y - t->b.y));
  float b = sqrt((t->b.x - t->c.x) * (t->b.x - t->c.x) +
                 (t->b.y - t->c.y) * (t->b.y - t->c.y));
  float c = sqrt((t->c.x - t->a.x) * (t->c.x - t->a.x) +
                 (t->c.y - t->a.y) * (t->c.y - t->a.y));
  float s = (a + b + c) / 2;
  return sqrt(s * (s - a) * (s - b) * (s - c));
}

/*
测试用例：
1 1
2 2
3 3
期望输出：
0.00
*/