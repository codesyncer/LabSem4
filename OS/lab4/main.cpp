#include <cstdio>
#include <math.h>
#include <queue>
using namespace std;

int mem_size= 1024;
int block_size= 4;
int max_order;
queue<int>** free_list= NULL;
int alloc_order(int order){
  if(order > max_order)
    return -1;
  if (free_list[order]->empty()){
      int offset = alloc_order(order+1);
      if(offset == -1)
        return -1;
      free_list[order]->push(offset+pow(2,order)*block_size);
      return offset;
  }
  else{
    int offset= free_list[order]->front();
    free_list[order]->pop();
    return offset;
  }
}
int alloc(int size){
  int order= (int)ceil(log(size)/log(2)) - log(block_size);
  order= max(0, order);
  if (free_list[order]->empty())
    if(alloc_order(order)==-1)
      return -1;
  int offset= free_list[order]->front();
  free_list[order]->pop();
  return offset;
}

void dealloc(int offset){

}
void init(){
  max_order= (int)(log(mem_size/block_size)/log(2));
  free_list= new queue<int>*[max_order+1];
  for(int i= 0; i<=max_order; ++i)
    free_list[i]= new queue<int>();
  free_list[max_order]->push(0);
}
void deinit(){
  for(int i= 0; i<=max_order; ++i)
    delete &free_list[i];
  delete free_list;
}
int main(){
}
