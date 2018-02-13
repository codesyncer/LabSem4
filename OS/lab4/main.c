#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define left(i) (2*i+1)
#define right(i) (2*i+2)
#define parent(i) ((i-1)/2)
#define SPLIT -2
#define UNOCCUPIED -1

const int blockSize= 64;
const int size= 1024;
int maxOrder, maxN;
short *tree;
void* alloc(int size){
  int order= size/blockSize;
  if(tree[0] == UNOCCUPIED){

  }
}

void init(){
  maxOrder= floor(log(size/blockSize)/log(2));
  maxN= pow(2, maxOrder+1)-1;
  tree= (short*)malloc(maxN*sizeof(short));
  memset(tree, UNOCCUPIED, maxN);
}
int main(){
  init();
  return 0;
}
