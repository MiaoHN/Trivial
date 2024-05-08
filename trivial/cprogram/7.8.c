#include<stdio.h>
#include<string.h>
struct People{
char id[8];
int ids;
int de;
int cai;
int all;
}person[105];
 
void swap(struct People *a,struct People *b)
{struct People temp=*a;
 *a=*b;
 *b=temp;
}
 
void change(int *str,int a,int b)
{int temp=str[a];
str[a]=str[b];
str[b]=temp;
}
 
int pai(int n,int l,int h)
{int i,j,sum1,sum2,sum3,sum4,max,t,sum;
 int tong1[n],tong2[n],tong3[n],tong4[n];
 sum1=0;
 sum2=0;
 sum3=0;
 sum4=0;
 for(i=0;i<n;i++)
   {if(person[i].de>=h&&person[i].cai>=h)
      {tong1[i]=1;
       sum1+=1;
      }
    else if(person[i].de>=h&&person[i].cai>=l)
      {tong2[i]=1;
       sum2+=1;
      }
    else if(person[i].de>=l&&person[i].cai>=l&&person[i].de>=person[i].cai)
      {tong3[i]=1;
       sum3+=1;
      }
    else if(person[i].de>=l&&person[i].cai>=l)
      {tong4[i]=1;
       sum4+=1;
      }
   }
 for(i=0;i<sum1;i++)
   {max=0;
    t=i;
    for(j=i;j<n;j++)
      {if(tong1[j]==1&&person[j].all>max)
         {t=j;
          max=person[j].all;
         }
      }
    if(t!=i)
    {swap(&person[i],&person[t]);
     change(tong2,i,t);
     change(tong3,i,t);
     change(tong4,i,t);
    }
   }
 for(i=0;i<sum2;i++)
   {max=0;
    t=i+sum1;
    for(j=i+sum1;j<n;j++)
      {if(tong2[j]==1&&person[j].all>max)
         {t=j;
         max=person[j].all;
         }
      }
    if(t!=(i+sum1))
      {swap(&person[i+sum1],&person[t]);
      change(tong3,(i+sum1),t);
     change(tong4,(i+sum1),t);
      }
   }
 for(i=0;i<sum3;i++)
   {max=0;
    t=i+sum1+sum2;
    for(j=i+sum1+sum2;j<n;j++)
      {if(tong3[j]==1&&person[j].all>max)
         {t=j;
         max=person[j].all;
         }
      }
    if(t!=(i+sum1+sum2))
      {swap(&person[i+sum1+sum2],&person[t]);
      change(tong4,(i+sum1+sum2),t);
      }
   }
 for(i=0;i<sum4;i++)
   {max=0;
    t=i+sum1+sum2+sum3;
    for(j=i+sum1+sum2+sum3;j<n;j++)
      {if(tong4[j]==1&&person[j].all>max)
         {t=j;
         max=person[j].all;
         }
      }
    if(t!=(i+sum1+sum2+sum3))
      {swap(&person[i+sum1+sum2+sum3],&person[t]);
      }
   }
 sum=sum1+sum2+sum3+sum4;
 for(i=0;i<sum;i++)
   {for(j=0;j<sum-1;j++)
      {if(person[j].all==person[j+1].all&&person[j].de<person[j+1].de)
         {swap(&person[j],&person[j+1]);
         }
       else if(person[j].all==person[j+1].all&&person[j].de==person[j+1].de&&person[j].ids>person[j+1].ids)
         {swap(&person[j],&person[j+1]);
         }
      }
   }
 return sum;
}
 
int main()
{int i,j,n,l,h,sum;
 scanf("%d %d %d",&n,&l,&h);
 for(i=0;i<n;i++)
   {scanf("%s %d %d",&person[i].id,&person[i].de,&person[i].cai);
    person[i].all=person[i].cai+person[i].de;
    person[i].ids=(person[i].id[6]-'0')*10+(person[i].id[7]-'0');
   }
 sum=pai(n,l,h);
 printf("%d\n",sum);
 for(i=0;i<sum;i++)
   {for(j=0;j<8;j++)
      {printf("%c",person[i].id[j]);
      }
    printf(" %d",person[i].de);
    printf(" %d\n",person[i].cai);
   }
 return 0;
}