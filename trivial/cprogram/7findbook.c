#include<stdio.h>
struct Book
{char name[50];
 float price;
}books[10];

int main()
{int n,i,min,max;
 scanf("%d",&n);
 i=0;
 
 for(i=0;i<n;i++)
   {
   scanf(" %[^\r\n]",books[i].name);
    scanf("%f",&books[i].price);
   }
 min=max=0;
 for(i=0;i<n;i++)
   {if(books[i].price>books[max].price)
      {max=i;
	  }
	if(books[i].price<books[min].price)
      {min=i;
	  }
   }
 printf("%s %.2f\n",books[max].name,books[max].price);
 printf("%s %.2f",books[min].name,books[min].price);
 
}