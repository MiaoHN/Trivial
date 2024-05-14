#include <stdio.h>  
#include <string.h>  
  
struct book {  
    char name[50];  
    float price;  
};  
  
int main() {  
    int n;  
    scanf("%d", &n);  
    getchar(); 
    struct book a[n];  
    for (int i = 0; i < n; i++) {  
        fgets(a[i].name, sizeof(a[i].name), stdin);   
        a[i].name[strcspn(a[i].name, "\n")] = 0;  
        scanf("%f", &a[i].price);  
        getchar();  
    }  
    for(int i=0;i<n-1;i++){
		for(int j=0;j<n-1-i;j++){
		    struct book temp;
			if(a[j].price<a[j+1].price){
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	printf("%s %.2f\n",a[0].name,a[0].price);
	printf("%s %.2f",a[n-1].name,a[n-1].price); 
    return 0;  
}