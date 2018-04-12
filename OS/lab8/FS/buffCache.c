#define NULL 0
enum BufferStatus {LOCKED, VALID, DELAYED_WRITE, BUSY, WAITING_FREE};
struct BuffHeader {
        int deviceNum, blockNum;
        enum BufferStatus status;
        char *data;
        struct BuffHeader *prev, *next, *prevFree, *nextFree;
};
struct FreeList {
        struct BuffHeader *head, *tail;
};
void freeListInit(struct FreeList *list){
        list->head = list->tail = NULL;
}
void freeListInsert(struct FreeList *list, struct BuffHeader *header){
        if(list->tail == NULL) {
                list->head = list->tail = header;
                header->nextFree = header->prevFree = header;
        }
        else{
                header->nextFree = list->head;
                list->head->prevFree = header;
                header->prevFree = list->tail;
                list->tail->nextFree = header;
                list->tail = header;
        }
}
struct BuffHeader* freeListRemove(struct FreeList *list){
        struct BuffHeader *tmp = list->head;
        if(list->head == NULL)
                return NULL;
        if(list->head == list->tail) {
                list->head = list->tail = NULL;
                return tmp;
        }
        list->tail->nextFree = list->head->nextFree;
        list->head->nextFree->prevFree = list->tail;
        list->head = list->head->nextFree;
        tmp->nextFree = tmp->prevFree = NULL;
        return tmp;
}

#define HQSIZE 4
struct HashQueue {
        struct Queue {
                struct BuffHeader *head, *tail;
        } Q[HQSIZE];
};
void hashQueueInit(struct HashQueue *hq){
        for(int i=0; i<HQSIZE; ++i)
                hq->Q[i].head = hq->Q[i].tail = NULL;
}
void hashQueueInsert(struct HashQueue *hq, struct BuffHeader *header){
        int index = (header->deviceNum + header->blockNum) %HQSIZE;
        struct Queue *q = &hq->Q[index];
        if(q->tail == NULL) {
                q->head = q->tail = header;
                header->prev = header->next = NULL;
        }
        else{
                q->tail->next = header;
                header->prev = q->tail;
                header->next = NULL;
                q->tail = header;
        }
}
int main(){
        return 0;
}
