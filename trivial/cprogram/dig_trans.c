#include <stdio.h>
 
char chrs[200] = {'\0'};
int step=0;
 
int main()
{
    void DigiTran( int k, char res[]);
 
    int list[100] = {0};
    int i;
    for(i=0;i<100;i++)
    {
        scanf("%d",list+i);
        if(list[i] == -1)
        {
            break;
        }
    }
     
 
     
    i = 0;
    while (list[i] != -1)
    {
        DigiTran(list[i], chrs);
        i++;
    }
     
    printf("%s",chrs);
 
    return 0;
}
 
void DigiTran( int k, char res[])
{
    int i=0;
    int r=k,d=0;
    while (r != 0)
    {
        d++;
        r=r/10;
    }
 
    int num[d];
    r = k;
    for(i;i<d;i++)
    {
        num[i]=r%10;
        r=r/10;
    }
 
    // i = d - 1;
    while (i != -1)
    {
        int n;
        if((i!=0)&&(10*num[i]+num[i-1] <= 25))
        {
            n = 10*num[i]+num[i-1];
            i = i - 2;
        }
        else
        {
            n = num[i];
            i--;
        }
        *(res + step) = 'A' + n;
        step++;
    }
    *(chrs + step) = ' ';
    step++;
}