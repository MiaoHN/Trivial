#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
typedef struct fruitinfo
{
	int no;
	char name[20];
	float num;
	float price;
	float sum;
}fruitinfo;
void set(struct fruitinfo* t);
void print(struct fruitinfo* t);
void sortfruit(struct fruitinfo* t);
int main()
{
	int i;
	fruitinfo kinds[6];
	set(kinds);
	sortfruit(kinds);
	print(kinds);
	return 0;
}
void set(struct fruitinfo* t)
{
	int i;
	for (i = 0; i < 6; i++,t++)
	{
		scanf("%d", &(*t).no);
		scanf("%s", (*t).name);
		scanf("%f", &(*t).num);
		scanf("%f", &(*t).price);
		(*t).sum = (*t).num * (*t).price;
	}

}
void print(struct fruitinfo* t)
{
	int i;
	for (i = 0; i < 6; i++, t++)
	{
		printf("%d ", (*t).no);
		printf("%s ", (*t).name);
		printf("%f ", (*t).num);
		printf("%f", (*t).price);
		printf("\n");
	}
}
void sortfruit(struct fruitinfo* t)
{
	int i, j;
	fruitinfo temp;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 5 - i; j++)
		{
			if ((*(t + j)).sum > (*(t + j + 1)).sum)
			{
				temp = *(t + j); *(t + j) = *(t + j + 1); *(t + j + 1) = temp;
			}
		}
	}
}