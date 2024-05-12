
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
char stuID[10];
char name[20];
char sex;
int age;
};


int main()
{
	int n;//输入操作次数 
	int i,j,k=0;
	char order[2];
	char m[2]={'i'};
	char t[2]={'s'};
	struct student stu[100];
	scanf("%d",&n);
	while(n--){
		scanf("%s",order);
			if(order[0] == 'i'){
				scanf("%s %c %d %s",stu[k].name,&stu[k].sex,&stu[k].age,stu[k].stuID);
				k++;
				continue;
			}
			else if(order[0] == 's'){
				if(k==0){
					printf("null\n");
				}
				else{
					for(j=0;j<k;j++){
						printf("%s %s %c %d\n",stu[j].stuID,stu[j].name,stu[j].sex,stu[j].age);
					}
				}
			}
	}
	return 0;
}