#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int a[n],*p=a;
    for(int i=0;i<n;i++,p++)
        scanf("%d",p);
    int *min=a,*max=a,*q=a;
    for(int i=0;i<n;i++,q++)
    {
        if(*q<*min)
        {
            min=q;
        }
        if(*q>*max)
        {
            max=q;
        }
    }
    int temp=*min;
    *min=*a;
    *a=temp;
    temp=*max;
    *max=*(a+n-1);
    *(a+n-1)=temp;
    p=a;
    for(int i=0;i<n;i++,p++)
        printf("%d ",*p);
    return 0;
}