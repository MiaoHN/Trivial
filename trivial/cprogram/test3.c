#include <stdio.h>
#include <math.h>
 
int x=0;//数组res的项 
int r;//判断是两位一起还是单独一位 
 
int main()
{
    void DigiTran(int k,char res[]);
    int k;
    char res[100]={0};
    scanf("%d",&k);
    while(k!=-1)
    {
        if(k!=0)
        {
            DigiTran(k,res);
            res[x+1]='0';//用作插入空格 
            x=x+2;
        }
        else
        {
            res[x]='A';
            res[x+1]='0';
            x=x+2;
        }
        scanf("%d",&k);
    }
    for(int i=0;i<x;i++)
    {
        if(res[i]!='0' && res[i] != '\0')
            printf("%c",res[i]);
        else if (i < x - 1 && res[i] == '0' && res[i + 1] != '0' && res[i + 1] != '\0')
            printf(" ");
    }
    return 0;
}
 
void DigiTran(int k,char res[])
{
    //先判断k有几位，然后先选前两位，设置函数判断是否
    //符合字母变换，若符合则直接变换，接着选后续两位，若不符合
    //则只变换前者，然后让后者与再后一位组成两位，接着函数判断 
    //通过全局变量x来对res数组赋值 
    void Judge(int k,char res[]);
    void change(int k,char res[]);
    int d=1;int t=k;
    while(t/10!=0)
    {
        d++; //d是输入数字k的位数 
        t=t/10;
    }
    int p;
    while(d!=0)
    {
        if(d!=1) 
        {
            p=k/(pow(10,d-2));
            Judge(p,res);
            if(r==1)
            {
                k=k%(int)(pow(10,d-2));
                d=d-2;
            }
            else
            {
                k=k%(int)(pow(10,d-1));
                d=d-1;
            }
        }
        else
        {
            change(k,res);
            d=d-1;
        }
    }
 
}
 
void Judge(int k,char res[])
{
    void change(int k,char res[]);
    if(k<=25)
    {
        change(k,res);  
        x++;
        r=1;
    }
    else
    {
        k=k/10;
        change(k,res);
        x++;
        r=0;
    }
}
 
void change(int k,char res[])
{
    switch(k)
        {
            case 0:res[x]='A';break;
            case 1:res[x]='B';break;
            case 2:res[x]='C';break;
            case 3:res[x]='D';break;
            case 4:res[x]='E';break;
            case 5:res[x]='F';break;
            case 6:res[x]='G';break;
            case 7:res[x]='H';break;
            case 8:res[x]='I';break;
            case 9:res[x]='J';break;
            case 10:res[x]='K';break;
            case 11:res[x]='L';break;
            case 12:res[x]='M';break;
            case 13:res[x]='N';break;
            case 14:res[x]='O';break;
            case 15:res[x]='P';break;
            case 16:res[x]='Q';break;
            case 17:res[x]='R';break;
            case 18:res[x]='S';break;
            case 19:res[x]='T';break;
            case 20:res[x]='U';break;
            case 21:res[x]='V';break;
            case 22:res[x]='W';break;
            case 23:res[x]='X';break;
            case 24:res[x]='Y';break;
            case 25:res[x]='Z';break;
        }
}