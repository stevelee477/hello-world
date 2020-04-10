//作业：面向对象设计以下框架的代码细节，程序能编译运行得到正确结果
#include <cmath>
#include <iostream>
class SuperPrime {
public:
  SuperPrime() : number(0) { //为什么必须有？
    size = 0;
  }
  SuperPrime(int n) : number(n) {
    size = 0;
    split(); //它就是构造对象
  }
  ~SuperPrime() {
    for (int i = 0; i < size; ++i) //销毁对象
      delete N[i];
  }
  bool isSuperPrime() {
    SuperPrime a(sum()); //将普通整数转变为对象
    SuperPrime b(multi());
    SuperPrime c(squareSum());
    if (isPrime() && a.isPrime() && b.isPrime() && c.isPrime())
      return true;
    return false;
  }

  int getNum() { return number; }

private:
  const int number;
  SuperPrime *N[100];
  int size;
  bool isPrime() {
    // 2到number-1的因子
    for (int i = 2; i <= floor(sqrt(number) + 0.5); i++)
      if (number % i == 0)
        // number split into N
        return false;
    return true;
  }
  void split() { //工厂方法设计模式
    // number split into N
    if (number < 10) {
      size = 1;
      return;
    }
    int temp = number;
    while (temp > 0) {
      int n = temp % 10;
      temp /= 10;
      N[size] = new SuperPrime(n); //构造对象
      size += 1;
    }
  }
  int sum() {
    int ans = 0;
    for (int i = 0; i < size; i++)
      ans += N[i]->number;
    return ans;
  }
  int multi() { return 0; }
  int squareSum() {
    int ans = 0;
    for (int i = 0; i < size; i++)
      ans += N[i]->number * N[i]->number;
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
  SuperPrime sp(113);
  if (sp.isSuperPrime())
    std::cout << "113 is SuperPrime" << std::endl;
  else
    std::cout << "113 is NOT SuperPrime" << std::endl;
  return 0;
}
