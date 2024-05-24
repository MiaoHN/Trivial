#include<stdio.h>
int main()
{
    typedef struct
    {
        char title[51];
        float price;
    }Book;
    int n;
    scanf("%d",&n);
    Book books[n];
    for(int i=0;i<n;i++)
      scanf(" %[^\n] %f",books[i].title,&books[i].price);
    Book *max=books,*min=books; 
    for(int i=1;i<n;i++)
    {
        max=(max->price<books[i].price)?books+i:max;
        min=(min->price>books[i].price)?books+i:min;
    }
    printf("%s %.2f\n%s %.2f",max->title,max->price,min->title,min->price);
    return 0;
}