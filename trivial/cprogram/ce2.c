#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct book {
	char arr[50];
	float pri;
};

int main()
{
	int n;
	scanf("%d", &n);
	getchar(); // 消耗换行符
	struct book* p = (struct book*)malloc(n * sizeof(struct book));
	for (int i = 0; i < n; i++)
	{
		scanf(" %[^\r\n]", p[i].arr);
		getchar();
		scanf("%f", &p[i].pri);
		getchar();
	}

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (p[j].pri > p[j + 1].pri)
			{
				struct book temp;
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}

	printf("%s %.2f\n", p[n - 1].arr, p[n - 1].pri);
	printf("%s %.2f\n", p[0].arr, p[0].pri);

	free(p);
	return 0;
}