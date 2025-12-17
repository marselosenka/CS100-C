#include <stdio.h>

void Fibonacci(int n) {

    int sum_prev = 0;
    int sum = 1;
    int sum2 = 0;
	if(n==1) {
        printf("%d\n",sum_prev);
    } else {
        printf("%d\n",sum_prev);
        printf("%d\n",sum);
        for(int i=0;i<n-1;i++) {
            sum2 = sum + sum_prev;
            sum_prev = sum;
            sum = sum2;
            printf("%d\n",sum2);
        }
    }
}

int main() {
    int n;
    scanf("%d",&n);
    Fibonacci(n);
    return 0;
    
}

