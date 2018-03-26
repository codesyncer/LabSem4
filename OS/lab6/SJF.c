#include <stdio.h>
#include <limits.h>
#define  HEAPSIZE 20

struct Record {
        int pid, arrivalTime, burstTime;
        int compTime, turnTime, waitTime;
        int index;
} smallest = {-1,-1, -1};
/*
 Min-heap datastructure implementation taken from https://www.sanfoundry.com/c-program-implement-heap/
 and customized to personal code-style.
*/
struct MinHeap {
        struct Record* heap[HEAPSIZE+1];
        int heapSize, index;
};
void init(struct MinHeap *h) {
        h->heapSize = 0;
        h->heap[0] = &smallest;
}
void insert(struct MinHeap *h, struct Record *element) {
        h->heapSize++;
        h->heap[h->heapSize] = element;
        int now = h->heapSize;
        while (h->heap[now / 2]->burstTime > element->burstTime) {
                h->heap[now] = h->heap[now / 2];
                now /= 2;
        }
        h->heap[now] = element;
}
struct Record* getMin(struct MinHeap *h) {
        struct Record *minElement, *lastElement;
        int child, now;
        minElement = h->heap[1];
        lastElement = h->heap[h->heapSize--];
        for (now = 1; now * 2 <= h->heapSize; now = child) {
                child = now * 2;
                if (child != h->heapSize && h->heap[child + 1]->burstTime < h->heap[child]->burstTime) {
                        child++;
                }
                if (lastElement->burstTime > h->heap[child]->burstTime) {
                        h->heap[now] = h->heap[child];
                } else
                        break;
        }
        h->heap[now] = lastElement;
        return minElement;
}
int empty(struct MinHeap *h){
        return h->heapSize == 0;
}
void simulate(int tq, int n, struct Record records[]){
        // sort by arrivalTime
        int processorTime=0, arriveCounter=0;
        struct MinHeap h;
        init(&h);
        for (int i=0; i<n; ++i)
                records[i].index = i;
        while(arriveCounter < n) {
                processorTime= records[arriveCounter].arrivalTime;
                while(arriveCounter < n && records[arriveCounter].arrivalTime == processorTime)
                        insert(&h, &records[arriveCounter++]);
                while(!empty(&h)) {
                        struct Record* shortest = getMin(&h);
                        processorTime += shortest->burstTime;
                        records[shortest->index].compTime = processorTime;
                        while(arriveCounter < n && records[arriveCounter].arrivalTime <= processorTime)
                                insert(&h, &records[arriveCounter++]);
                }
        }
        printf("|%-5s\t|%-5s\t|%-5s\t|%-5s\t|%-5s\t|%-5s\t|\n","PID","AT","BT","CT","TAT","WT");
        for(int i=0; i<n; ++i) {
                records[i].turnTime = records[i].compTime-records[i].arrivalTime;
                records[i].waitTime = records[i].turnTime-records[i].burstTime;
                printf("|%-5d\t|%-5d\t|%-5d\t|%-5d\t",records[i].pid,records[i].arrivalTime,records[i].burstTime,records[i].compTime);
                printf("|%-5d\t|%-5d\t|\n",records[i].turnTime,records[i].waitTime);
        }
}
int main(){
        struct Record records[] = {{1,0,2},{2,1,4},{3,2,1},{4,3,5},{5,4,3},{6,20,5}};
        simulate(2, sizeof(records)/sizeof(records[0]), records);
        return 0;
}
