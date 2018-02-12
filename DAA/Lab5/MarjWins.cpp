#include <stdio.h>
bool equal(int x, int y){
  return x == y;
}
int majority(int A[], int i, int j, bool (*eq)(int,int)){
  if( i==j )
    return A[i];
  int count= 0;
  int m1= majority(A,i,(i+j)/2, eq);
  if (m1 != -1)
  for(int k=i; k<=((i+j)/2); ++k){
    if(eq(A[k], m1))
      count++;
    if(count> (j-i+1)/2)
      return m1;
  }
  int m2= majority(A,(i+j)/2+1, j, eq);
  count=0;
  if (m2 != -1)
  for(int k=i; k<=((i+j)/2); ++k){
    if(eq(A[k], m2))
      count++;
    if(count> (j-i+1)/2)
      return m2;
  }
  return -1;
}
int main(){
  int A[]={1,3,1,2,1,1,5,1};
  printf("%d\n", majority(A, 0, sizeof(A)-1, equal));
  return 0;
}
