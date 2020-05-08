//?????????????????????????????????????????§Ö????????
#include <cmath>
#include <iostream>
class Prime {
  public:
  	Prime():number(0) {
	}
  	Prime(int n):number(n) {
	}
	~Prime() {
	}
  	bool isPrime() { 
  	  for (int i = 2; i <= floor(sqrt(number) + 0.5); i++)
      if (number % i == 0)
        // number split into N
        return false;
    return true;
	};
  int getNum() { return number; };
  private:
  	const int number;
}; 
class PrimeSet {
  public:
  	PrimeSet(int size) {
  	  //???????????? 
  	  N = new Prime*[size];
  	  this->size = size;
  	  index = 0;
	}
	~PrimeSet() {
  	  for (int i = 0; i < index; ++i)  //??????? 
		delete N[i]; 
	  delete[] N;
	}
	bool add(int n) {
	  if(index == size)  return false;
	  Prime *p = new Prime(n);
	  N[index] = p;
	  index += 1;
	  return true;
	}
	bool isAllPrime() {
    calcSum();
    calcSquareSum();
	  for(int i = 0; i < index; i++)
	    if (!N[i]->isPrime())
	      return false;
	  return true;
	} 
  void calcSum() {
    int sum = 0;
    for(int i = 0; i < index; i++)
      sum += N[i]->getNum();
    add(sum);
  }
  void calcSquareSum() {
    int squareSum = 0;
    for(int i = 0; i < index; i++)
      squareSum += N[i]->getNum() * N[i]->getNum();
    add(squareSum);
  }
  private:
  	Prime **N;
	int size, index;
};
class SuperPrime {
  public:
  	SuperPrime():number(0), pset(3) {  //????????§µ? 
  	}
  	SuperPrime(int n):number(n), pset(3) {
  	  split();  //???????????? 
	}
  	~SuperPrime() {
	}
  	bool isSuperPrime() {
  	  //??????pset?? 
  	  Prime p(number);
	  if (p.isPrime() && pset.isAllPrime())
	    return true; 
  	  return false;
	}
  private:
  	const int number;
  	PrimeSet pset;
	void split() {   //????????????? 
	  // number split into N
	  int temp = number;
	  while(temp > 0) {
	  	int n = temp % 10;
	  	temp /= 10;
	  	pset.add(n);  //??????????????????????/??/?????????? 
	  } 
	}
};
class SuperPrimeSet {
  public:
  	SuperPrimeSet(int from, int to) {
  	  size = to - from;
  	  for (int i = from; i < to; i++)
  	    set[i-from] = new SuperPrime(i);
	}
  	~SuperPrimeSet() {
  	  for(int i = 0; i < size; i++)
  	    delete set[i];
	}
  	int count() {
  	  int count = 0;
  	  for (int i = 0; i < size; i++)
  	    if(set[i]->isSuperPrime())
  	      count += 1;
	  return count; 
	}
  	int sum() {
  	  int sum = 0;
  	  /*
  	  for (int i = 0; i < size; i++)
  	    if(set[i].isSuperPrime())
  	      sum += set[i];
  	      */ 
	  return sum; 
	}
  private:
  	SuperPrime **set;
  	int size, index;
};
int main() {
  SuperPrime sp(113);
  if (sp.isSuperPrime())
    std::cout << "113 is SuperPrime" << std::endl;
  else
    std::cout << "113 is NOT SuperPrime" << std::endl;
  return 0;
}
