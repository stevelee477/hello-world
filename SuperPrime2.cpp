//作业：完成以下框架的代码细节，程序能编译运行得到正确结果
#include <cmath>
#include <iostream>
class SuperPrime {
public:
  SuperPrime() : number(0) {}
  SuperPrime(int n) : number(n) {}
  ~SuperPrime() {}
  bool isSuperPrime() {
    split();
    int a = sum();
    int b = multi();
    int c = squareSum();
    if (isPrime(number) && isPrime(a) && isPrime(b) && isPrime(c)) {
      return true;
    }
    return false;
  }
  int getNum() { return number; }

private:
  const int number;
  int N[100], size;
  bool isPrime(int n) {
    for (int i = 2; i <= floor(sqrt(n) + 0.5); i++) {
      if (n % i == 0)
        return false;
    }
    return true;
  }
  void split() {
    // number split into N
    int x = number;
    size = 0;
    while (x > 0) {
      N[size++] = x % 10;
      x /= 10;
    }
  }
  int sum() {
    int ans = 0;
    for (int i = 0; i < size; i++)
      ans += N[i];
    return ans;
  }
  int multi() { return 0; }
  int squareSum() {
    int ans = 0;
    for (int i = 0; i < size; i++)
      ans += (N[i] * N[i]);
    return ans;
  }
};
class Set {
public:
  Set(int from, int to) {
    size = to - from + 1;
    for (int i = 0; i < size; i++) {
      set[i] = new SuperPrime(i + from);
    }
  }
  ~Set() {
    for (int i = 0; i < size; i++)
      delete set[i];
  }
  int count() {
    int count = 0;
    for (int i = 0; i < size; i++)
      if (set[i]->isSuperPrime())
        count += 1;
    return count;
  }
  int sum() {
    int sum = 0;
    for (int i = 0; i < size; i++)
      if (set[i]->isSuperPrime())
        sum += set[i]->getNum();
    return sum;
  }

private:
  SuperPrime *set[1000];
  int size;
};
int main() {
  Set ss(100, 999);
  std::cout << "How Many: " << ss.count() << std::endl;
  std::cout << "Sum is " << ss.sum() << std::endl;
  return 0;
}
