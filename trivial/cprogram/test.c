#include<stdio.h>
struct Singer
{
    char num[5];
    int point[6];
    float score;
};
int main()
{
    struct Singer singer[5]={{"001",{0},0},{"002",{0},0},{"003",{0},0},{"004",{0},0},{"005",{0},0}};
    struct Singer temp;
    int i,j,k,max[5],min[5],sum[5]={0};
    for(i=0;i<5;i++)
    {
        for(j=0;j<6;j++)
        {
            scanf("%d",&singer[i].point[j]);
            sum[i]=sum[i]+singer[i].point[j];
        }
    }//输入得分 
    for(i=0;i<5;i++)
    {
        max[i]=singer[i].point[0];
        min[i]=singer[i].point[0];
        for(j=1;j<6;j++)
        {
        if(singer[i].point[j]>max[i])
            max[i]=singer[i].point[j];
        if(singer[i].point[j]<min[i])
            min[i]=singer[i].point[j];
        }
    }
    for(i=0;i<5;i++)
        singer[i].score=(sum[i]-max[i]-min[i])/4;//计算平均分 
    
    for(i=0;i<4;i++)
    {
        for(j=i+1;j<5;j++)
        {
            if(singer[j].score>singer[i].score)
            {
                temp=singer[j];
                singer[j]=singer[i];
                singer[i]=temp;
            }    
        }
    }
    for(i=0;i<5;i++)
    {
        printf("%s %.2f\n",singer[i].num,singer[i].score);
    }
    return 0;
}