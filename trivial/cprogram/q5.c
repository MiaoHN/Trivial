#include <stdio.h>
#include <stdlib.h>

struct point {
	float x;
	float y;
	float z;
	char color[20];
};

void load(struct point* p, int n)
{
	for (int i = 0; i < n; i++)
	{
		scanf("%f%f%f", &p[i].x ,&p[i].y, &p[i].z);
		scanf(" %s", p[i].color);
	}
	/*for (int i = 0; i < n; i++)
	{
		printf("%.2f %.2f %.2f %s\n", p[i].x, p[i].y, p[i].z, p[i].color);
	}*/
}

void Print(struct point* p, int n)
{
	int temp = 0;
	char tem[3]; tem[0] = 'r'; tem[1] = 'e'; tem[2] = 'd';

	for (int i = 0; i < n; i++)
	{
		temp = 0;
		for (int j = 0; j < 3; j++)//检查颜色
		{
			if (p[i].color[j] != tem[j] || p[i].color[j] == '\0')
			{
				temp = 1;
				break;
			}
		}

		if (temp == 0)
		{
			printf("%.2f %.2f %.2f %s\n", p[i].x, p[i].y, p[i].z, p[i].color);
		}
	}
}

float ComputeBoundBoxArea(struct point* p, int n)
{
	float x1, x2, y1, y2, z1, z2;
	x1 = 1000;
	for (int i = 0; i < n; i++)
	{
		if (x1 > p[i].x)
		{
			x1 = p[i].x;
		}
	}
	x2 = -1000;
	for (int i = 0; i < n; i++)
	{
		if (x2 < p[i].x)
		{
			x2 = p[i].x;
		}
	}
	y1 = 1000;
	for (int i = 0; i < n; i++)
	{
		if (y1 > p[i].y)
		{
			y1 = p[i].y;
		}
	}
	y2 = -1000;
	for (int i = 0; i < n; i++)
	{
		if (y2 < p[i].y)
		{
			y2 = p[i].y;
		}
	}
	z1 = 1000;
	for (int i = 0; i < n; i++)
	{
		if (z1 > p[i].z)
		{
			z1 = p[i].z;
		}
	}
	z2 = -1000;
	for (int i = 0; i < n; i++)
	{
		if (z2 < p[i].z)
		{
			z2 = p[i].z;
		}
	}
	printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,", x1,x2,y1,y2,z1,z2);
	float sum;
	sum = (x2 - x1) * (y2 - y1) * 2 + (x2 - x1) * (z2 - z1) * 2 + (z2 - z1) * (y2 - y1) * 2;
	return sum;
}

int main()
{
	int n;
	scanf("%d", &n);
	struct point p[6];
	load(p, n);
	Print(p, n);
	printf("%.2f", ComputeBoundBoxArea(p, n));
	return 0;
}