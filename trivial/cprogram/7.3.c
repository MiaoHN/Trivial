#include<stdio.h>
 
int runnian(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return 1;
            } else
                return 0;
        } else
            return 1;
    } else
        return 0;
}
 
void adddays(int k, int *year, int *month, int *day) {
    while (k > 0) {
        switch (*month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (*day + k > 31) {
                    k -= 31 - *day + 1;
                    *day = 1;
                    (*month)++;
                } else {
                    *day += k;
                    k = 0;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (*day + k > 30) {
                    k -= 30 - *day + 1;
                    *day = 1;
                    (*month)++;
                } else {
                    *day += k;
                    k = 0;
                }
                break;
            case 2:
                if (runnian(*year)) {
                    if (*day + k > 29) {
                        k -= 29 - *day + 1;
                        *day = 1;
                        (*month)++;
                    } else {
                        *day += k;
                        k = 0;
                    }
                } else {
                    if (*day + k > 28) {
                        k -= 28 - *day + 1;
                        *day = 1;
                        (*month)++;
                    } else {
                        *day=*day+k;
                        k = 0;
                    }
                }
                break;
             
                return;
        }
        if (*month > 12) {
            *month = 1;
            (*year)++;
        }
    }
    
}
 
int main() {
    int k, year, month, day;
    scanf("%d %d %d", &year, &month, &day);
    scanf("%d", &k);
    adddays(k, &year, &month, &day);
    printf("%d-%d-%d", year, month, day);
    return 0;
}