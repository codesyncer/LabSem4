#include "Queue.c"
#include <stdio.h>
struct Record {
        int pid, arrivalTime, burstTime;
        int compTime, turnTime, waitTime;
};
void simulate(int tq, int n, struct Record records[]){
        // sort
        int conSwitch = 0, processorTime=0, arriveCounter=0;
        struct Queue q;
        init(&q);
        int *burstTimes = (int*)malloc(sizeof(int)*n);
        for (int i=0; i<n; ++i)
                burstTimes[i] = records[i].burstTime;
        while(!empty(&q) || arriveCounter < n) {
                int i;
                if(empty(&q)) {
                        processorTime=records[arriveCounter].arrivalTime;
                        i=arriveCounter++;
                }
                else
                        i = pop(&q);
                if (burstTimes[i] <= tq) {
                        processorTime+=burstTimes[i];
                        records[i].compTime = processorTime;
                        while(arriveCounter<n && records[arriveCounter].arrivalTime <= processorTime )
                                push(&q, arriveCounter++);
                }
                else{
                        processorTime+=tq;
                        burstTimes[i] -= tq;
                        while(arriveCounter<n &&records[arriveCounter].arrivalTime <= processorTime)
                                push(&q, arriveCounter++);
                        push(&q,i);
                }
                conSwitch++;
        }
        free(burstTimes);
        destroy(&q);
        printf("|%-5s\t|%-5s\t|%-5s\t|%-5s\t|%-5s\t|%-5s\t|\n","PID","AT","BT","CT","TAT","WT");
        for(int i=0; i<n; ++i) {
                records[i].turnTime = records[i].compTime-records[i].arrivalTime;
                records[i].waitTime = records[i].turnTime-records[i].burstTime;
                printf("|%-5d\t|%-5d\t|%-5d\t|%-5d\t",records[i].pid,records[i].arrivalTime,records[i].burstTime,records[i].compTime);
                printf("|%-5d\t|%-5d\t|\n",records[i].turnTime,records[i].waitTime);
        }
        printf("Context Switches: %d\n", conSwitch);
}
int main(){
        struct Record records[] = {{1,0,2},{2,1,4},{3,2,1},{4,3,5},{5,4,3},{6,20,5}};
        simulate(2, sizeof(records)/sizeof(records[0]), records);
        return 0;
}
