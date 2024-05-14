#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
typedef struct
{
	char stuID[10];
	char name[20];
	char sex;
	int age;
}student;
int main()
{
	student students[20];
	int n, i, j;
	int sum = 0;
	scanf("%d\n", &n);
	for (i = 0; i < n; i++)
	{
		char a;
		scanf(" %c", &a);
		if (a == 'i')
		{
			scanf("%s", students[sum].name);
			scanf(" %c", &students[sum].sex);
			scanf(" %d", &students[sum].age);
			scanf(" %s\n", students[sum].stuID);
			sum++;
		}
		else if (a == 's')
		{
			if (sum == 0)
			{
				printf("null");
			}
			else
			{
				for (j = 0; j < sum; j++)
				{
					printf("%s ", students[j].stuID);
					printf("%s ", students[j].name);
					printf("%c ", students[j].sex);
					printf("%d", students[j].age);
					printf("\n");
				}
			}
		}
	}
	return 0;
}