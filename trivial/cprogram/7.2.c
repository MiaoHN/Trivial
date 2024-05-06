#include <stdio.h>  
  
struct Mooncake {  
    double inventory;  
    double total_price; 
    double price_per_ton; 
};  
  
int main() {  
    int n, d;
	d=0;  
    scanf("%d %d", &n, &d); 
  
    struct Mooncake mooncakes[n];  
    for (int i = 0; i < n; ++i) {  
        scanf("%lf", &mooncakes[i].inventory);  
    }  
    for (int i = 0; i < n; ++i) {  
        scanf("%lf", &mooncakes[i].total_price);  
        mooncakes[i].price_per_ton = mooncakes[i].total_price / mooncakes[i].inventory; 
    }  
  
    double dp[d + 1] = {0};  
    for (int i = 0; i < n; ++i) {   
        for (int j = d; j >= 0; --j) {  
            double max_profit_so_far = dp[j]; 
            for (double k = 0; k <= mooncakes[i].inventory && k <= j; k ++) {  
                double profit_with_k = dp[j - (int)k] + k * mooncakes[i].price_per_ton;  
                if (profit_with_k > max_profit_so_far) {  
                    max_profit_so_far = profit_with_k;  
                }  
            }  
            dp[j] = max_profit_so_far;  
        }  
    }  
  
    printf("%.2lf\n", dp[d]);  
  
    return 0;  
}
