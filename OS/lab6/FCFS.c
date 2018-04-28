// First Come First Serve

#include <stdio.h>
struct Record {
        int pid, arrivalTime, burstTime;
        int compTime, turnTime, waitTime;
};
void simulate(int n, struct Record records[]){
        // sort by arrivalTime
        int processorTime, arriveCounter=0;

        while(arriveCounter < n) {
                processorTime= records[arriveCounter].arrivalTime;
                while(arriveCounter < n && records[arriveCounter].arrivalTime <= processorTime) {
                        processorTime+= records[arriveCounter].burstTime;
                        records[arriveCounter].compTime = processorTime;
                        arriveCounter++;
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
        simulate(sizeof(records)/sizeof(records[0]), records);
        return 0;
}
