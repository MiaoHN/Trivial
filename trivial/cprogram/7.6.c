#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Triangle
{
	float x;
	float y;
};

float area(struct Triangle* t)
{
	float area;
	float a,b,c,p;//三条边长的长度 
	a=sqrt(pow(t->x-(t+1)->x,2)+pow(t->y-(t+1)->y,2));
	b=sqrt(pow(t->x-(t+2)->x,2)+pow(t->y-(t+2)->y,2));
	c=sqrt(pow((t+2)->x-(t+1)->x,2)+pow((t+2)->y-(t+1)->y,2));
	p=(a+b+c)/2;
	area=sqrt(p*(p-a)*(p-b)*(p-c));
	return area;
}

int main()
{
	struct Triangle triangle[3];
	int i;
	float square;
	for(i=0;i<3;i++){
		scanf("%f%f",&triangle[i].x,&triangle[i].y);
	}
	struct Triangle *t=triangle;
	square=area(t);
	printf("%.2f",square);
	return 0;
}