#include <stdio.h>
#include <stdbool.h>
//n*n*n
bool isPrime(int n){
  for(int i=2; i<n; ++i)
    if(n%i == 0)
      return false;
  return true;
}
int calc(int n){
  int prime;
  for(int i=2, count=0; count< n; ++i){
    if (isPrime(i)){
      prime = i;
      count++;
    }
  }
  return prime;
}
int main(){
  printf("%d\n", calc(100000));
}
