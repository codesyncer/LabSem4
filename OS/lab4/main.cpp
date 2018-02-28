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
    return alloc_order(order);
  int offset= free_list[order]->front();
  free_list[order]->pop();
  return offset;
}
bool merge(int offset, int order){
    queue<int> *q = free_list[order];
    for(int j=0; j<q->size(); ++j){
        if(offset == q->front()){
            q->pop();
            return true;
        }
        q->push(q->front());
        q->pop();
    }
    return false;
}
void dealloc(int size, int offset){
    int order= (int)ceil(log(size)/log(2)) - log(block_size);
    int buddy_order= order= max(0, order);
    size= pow(2, order)*block_size;
    int buddy_offset= offset - size;
    if(buddy_offset >= 0 && merge(buddy_offset, buddy_order)){
            dealloc(2*size, buddy_offset);
            return;
    }
    buddy_offset= offset + size;
    if(buddy_offset < mem_size && merge(buddy_offset, buddy_order)){
            dealloc(2*size, offset);
            return;
    }
    free_list[order]->push(offset);
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
    delete free_list[i];
  delete free_list;
}
void print(){
    printf("\nFree Partitions");
    for (int i= 0; i<= max_order; ++i){
        int qsize= free_list[i]->size();
        if (qsize)
            printf("\n%dkb @ ", (int)pow(2,i)*block_size);
        for(int j=0; j<qsize; ++j){
            printf("%d ", free_list[i]->front());
            free_list[i]->push(free_list[i]->front());
            free_list[i]->pop();
        }
    }
    printf("\n");
}
int main(){
    init();
    print();
    int o2= alloc(500);
    int o1= alloc(20);
    print();
    dealloc(20, o1);
    print();
    deinit();
}
