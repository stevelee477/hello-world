//超级素数：它本身，各位数字的和，各位数字的平方和，都是素数。
//求 100~10000 内的所有超级素数，及它们的平均数。

#include <stdio.h>
#include <math.h>

#define MAX_DIGIT 10

int isPrime(int x);
int splitNum(int x, int num[]);
int identity(int x);
int square(int x);
int forEachSum(int length, int num[], int(*func)(int));

int isSuperPrime(int x);

int main()
{
    int sum = 0, i, count = 0;
    for (i = 100; i <= 10000; i++) {
        if (isSuperPrime(i)) {
            printf("%d\n", i);
            sum += i;
            count++;
        }
    }
    printf("Avg is: %.2lf\n", 1.0*sum/count);
    return 0;
}

int splitNum(int x, int num[]) {
    int length = 0;
    while(x > 0) {
        num[length++] = x%10;
        x /= 10;
    }
    return length;
}

int isPrime(int x) {
    for (int i = 2; i <= floor(sqrt(x)+0.5); i++) {
        if (x % i == 0)
            return 0;
    }    
    return 1;
}

int identity(int x) {
    return x;
}

int square(int x) {
    return x*x;
}

int forEachSum(int length, int num[], int(*func)(int)) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += func(num[i]);
    }
    return sum;
}

int isSuperPrime(int x) {
    int num[MAX_DIGIT];
    int length = splitNum(x, num);
    
    return isPrime(x) && isPrime(forEachSum(length, num, identity)) && isPrime(forEachSum(length, num, square));
}