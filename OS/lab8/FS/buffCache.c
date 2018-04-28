#include <stdlib.h>
#define BUFFSIZE 8
#define BUFFCOUNT 10
enum BufferStatus { LOCKED, VALID, DELAYED_WRITE, BUSY, WAITING_FREE };
struct BuffHeader {
  int deviceNum, blockNum;
  enum BufferStatus status;
  char *data;
  struct BuffHeader *prev, *next, *prevFree, *nextFree;
};
struct FreeList {
  struct BuffHeader *head, *tail;
} freeList;
void freeListInit(struct FreeList *list) { list->head = list->tail = NULL; }
void freeListInsert(struct FreeList *list, struct BuffHeader *header) {
  if (list->tail == NULL) {
    list->head = list->tail = header;
    header->nextFree = header->prevFree = header;
  } else {
    header->nextFree = list->head;
    list->head->prevFree = header;
    header->prevFree = list->tail;
    list->tail->nextFree = header;
    list->tail = header;
  }
}
struct BuffHeader *freeListRemove(struct FreeList *list) {
  struct BuffHeader *tmp = list->head;
  if (list->head == NULL)
    return NULL;
  if (list->head == list->tail) {
    list->head = list->tail = NULL;
    return tmp;
  }
  list->tail->nextFree = list->head->nextFree;
  list->head->nextFree->prevFree = list->tail;
  list->head = list->head->nextFree;
  tmp->nextFree = tmp->prevFree = NULL;
  return tmp;
}
int freeListEmpty(struct FreeList *list) { return list->head == NULL; }

#define HQSIZE 4
struct HashQueue {
  struct Queue {
    struct BuffHeader *head, *tail;
  } Q[HQSIZE];
} hashQ;
void hashQueueInit(struct HashQueue *hq) {
  for (int i = 0; i < HQSIZE; ++i)
    hq->Q[i].head = hq->Q[i].tail = NULL;
}
void hashQueueInsert(struct HashQueue *hq, struct BuffHeader *header) {
  int index = (header->deviceNum + header->blockNum) % HQSIZE;
  struct Queue *q = &hq->Q[index];
  if (q->tail == NULL) {
    q->head = q->tail = header;
    header->prev = header->next = NULL;
  } else {
    q->tail->next = header;
    header->prev = q->tail;
    header->next = NULL;
    q->tail = header;
  }
}
struct BuffHeader *hashQueueGet(struct HashQueue *hq, int deviceNum,
                                int blockNum) {
  int index = (deviceNum + blockNum) % HQSIZE;
  struct BuffHeader *header = hq->Q[index].head;
  while (header != NULL) {
    if (header->deviceNum == deviceNum && header->blockNum == blockNum)
      return header;
    header = header->next;
  }
  return NULL;
}

void init() {
  freeListInit(&freeList);
  hashQueueInit(&hashQ);
  struct BuffHeader *header;
  for (int i = 0; i < BUFFCOUNT; ++i) {
    header = (struct BuffHeader *)malloc(sizeof(struct BuffHeader));
    header->data = (char *)malloc(BUFFSIZE * sizeof(char));
    freeListInsert(&freeList, header);
  }
}
void deinit() {
  while (!freeListEmpty(&freeList))
    free(freeListRemove(&freeList));
  struct BuffHeader *header;
  for (int i = 0; i < HQSIZE; ++i)
    while (hashQ.Q[i].head != NULL) {
      header = hashQ.Q[i].head;
      hashQ.Q[i].head = header->next;
      free(header);
    }
}
void fakeOpen(int deviceNum, int blockNum) {
  if (hashQueueGet(&hashQ, deviceNum, blockNum) != NULL)
    return;
  if (freeListEmpty(&freeList)) {
    return;
  }
  struct BuffHeader *header = freeListRemove(&freeList);
  header->deviceNum = deviceNum;
  header->blockNum = blockNum;
  hashQueueInsert(&hashQ, header);
}
void fakeClose(int deviceNum, int blockNum) {}
void fakeWrite(int deviceNum, int blockNum, char *data, int index, int length) {

}
void fakeRead(int deviceNum, int blockNum, char *data, int index, int length) {}

int main() {
  init();
  deinit();
  return 0;
}
