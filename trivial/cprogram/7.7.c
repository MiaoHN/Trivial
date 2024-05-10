#include<stdio.h>
 
struct Student
{
    char stuID[10];
    char name[20];
    char sex;
    int age;
};
 
 
int main()
{
    int n;
    scanf("%d",&n);
    char action[n];
    struct Student student[n];
    getchar();
    int j=0;
    for(int k=0;k<n;k++)
    {
        scanf("%c",&action[k]);
             
            if(action[k]=='i')
            {
                scanf("%19s %c %d %9s",student[j].name,&student[j].sex,&student[j].age,student[j].stuID);
                j++;
            }
            else if(action[k]=='s')
            {
                if(k==0)
                printf("null");
                else
                for(int j=0;j<k;j++)
                {
                    printf("%s %s %c %d",student[j].stuID,student[j].name,student[j].sex,student[j].age);
                    if(j!=k-1)
                    printf("\n");
                }
            }
            getchar();
        }
     
    return 0;
}