#include <stdlib.h>
struct Node {
        int val;
        struct Node* next;
};
struct Queue {
        struct Node *head, *tail;
};
void init(struct Queue *q){
        q->head = q->tail = NULL;
}
int empty(struct Queue *q){
        return q->head == NULL;
}
int pop(struct Queue *q){
        if (q->head == NULL)
                return -1;
        int val = q->head->val;
        struct Node *tmp = q->head;
        q->head = q->head->next;
        free(tmp);
        return val;
}
void push(struct Queue *q, int val){
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node->val = val;
        node->next = NULL;
        if(q->head == NULL)
                q->head=node;
        else
                q->tail->next = node;
        q->tail=node;
}
void destroy(struct Queue *q){
        struct Node *tmp;
        while(q->head != NULL) {
                tmp = q->head;
                q->head = q->head->next;
                free(tmp);
        }
}
