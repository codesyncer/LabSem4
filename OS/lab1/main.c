#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define p_n (sizeof(p_sizes)/sizeof(int))

void *mem = 0;
size_t mem_size = 100;
int multiplier = 1024;

// Fixed Size Partitioning
int p_sizes[] = {1, 10, 40, 30, 10, 5, 2, 2};
int p_offset[p_n] = {0};
int p_occupied[p_n] = {0};
int p_sizes_sorted[p_n];
int p_virtual_to_real_i[p_n];

void *first_fit(int size) {
    for (int i = 0; i < p_n; ++i) {
        if (p_occupied[i] == 0 && p_sizes[i] >= size) {
            p_occupied[i] = size;
            return mem + p_offset[i];
        }
    }
    return NULL;
}

int ge_x(const int *arr, int n, int x) {
    int low = 0, mid, end = n - 1;
    do {
        mid = (low + end) / 2;
        if (arr[mid] < x)
            low = mid + 1;
        else if (arr[mid] >= x)
            end = mid;
    } while (low < end);
    mid = (low + end) / 2;
    return arr[mid] < x ? -1 : mid;
}

int e_x(const int *arr, int n, int x) {
    int low = 0, mid, end = n - 1;
    do {
        mid = (low + end) / 2;
        if (arr[mid] < x)
            low = mid + 1;
        else if (arr[mid] > x)
            end = mid - 1;
        else
            return mid;
    } while (low <= end);
    return -1;
}

void *best_fit(int size) {
    int start_scan = ge_x(p_sizes_sorted, p_n, size);
    if (start_scan == -1)
        return NULL;
    int ri;
    for (int i = start_scan; i < p_n; ++i) {
        ri = p_virtual_to_real_i[i];
        if (p_occupied[ri] == 0 && p_sizes[ri] >= size) {
            p_occupied[ri] = size;
            return mem + p_offset[ri];
        }
    }
    return NULL;
}

void *worst_fit(int size) {
    int ri;
    for (int i = p_n - 1; i >= 0; --i) {
        ri = p_virtual_to_real_i[i];
        if (p_occupied[ri] == 0 && p_sizes[ri] >= size) {
            p_occupied[ri] = size;
            return mem + p_offset[ri];
        }
    }
    return NULL;
}


void *alloc(int size, void *(*fitter)(int)) {
    return fitter(size);
}

void dealloc(void *ptr) {
    int offset = (int) (ptr - mem);
    int p_index = e_x(p_offset, p_n, offset);
    if (p_index == -1)
        return;
    p_occupied[p_index] = 0;
}

void swap(int *a, int *b) {
    *a += *b;
    *b = *a - *b;
    *a = *a - *b;
}

void prepare_tables() {
    for (int i = 0; i < p_n; ++i)
        p_virtual_to_real_i[i] = i;
    for (int i = 1; i < p_n; ++i)
        p_offset[i] = p_offset[i - 1] + p_sizes[i];
    memcpy(p_sizes_sorted, p_sizes, p_n * sizeof(int));
    for (int i = 0; i <= p_n - 2; ++i)
        for (int j = 0; j <= p_n - i - 2; ++j)
            if (p_sizes_sorted[j] > p_sizes_sorted[j + 1]) {
                swap(p_sizes_sorted + j, p_sizes_sorted + j + 1);
                swap(p_virtual_to_real_i + j, p_virtual_to_real_i + j + 1);
            }
}

//void arrPrint(int *arr, int n) {
//    for (int i = 0; i < n; ++i)
//        printf("%5d", arr[i]);
//    printf("\n");
//}

void pPrint() {
    for (int i = 0; i < p_n; ++i) {
        printf("| s:%d o:%d ", p_sizes[i], p_occupied[i]);
    }
    printf("|\n");
}

//Variable Size Partitioning

struct Partition {
    int size;
    bool occupied;
    struct Partition *next;
};

void initPartition(struct Partition *part, int size, struct Partition *next) {
    part->size = size;
    part->occupied = false;
    part->next = next;
}

struct Partition *head;

void *v_alloc(int size) {
    int offset = 0;
    struct Partition *part = head;
    while (part != NULL) {
        if (part->occupied == false) {
            if (part->size > size) {
                struct Partition *new = (struct Partition *) malloc(sizeof(struct Partition));
                if (new == NULL)
                    return NULL;
                initPartition(new, part->size - size, part->next);
                part->size = size;
                part->occupied = true;
                part->next = new;
                return mem + offset;
            }
            if (part->size == size) {
                part->occupied = true;
                return mem + offset;
            }
        }
        offset += part->size;
        part = part->next;
    }
    return NULL;
}

void v_dealloc(void *ptr) {
    int dest_offset = (int) (ptr - mem), offset = 0;
    struct Partition *part = head, *prevPart = NULL;
    while (part != NULL) {
        if (offset == dest_offset) {
            struct Partition *nextPart = part->next;
            if (prevPart != NULL && prevPart->occupied == false && nextPart != NULL && nextPart->occupied == false) {
                prevPart->size += part->size + nextPart->size;
                prevPart->next = nextPart->next;
                free(part);
                free(nextPart);
                return;
            }
            if (prevPart != NULL && prevPart->occupied == false) {
                prevPart->size += part->size;
                prevPart->next = nextPart;
                free(part);
                return;
            }
            if (nextPart != NULL && nextPart->occupied == false) {
                part->size += nextPart->size;
                part->next = nextPart->next;
                part->occupied = false;
                free(nextPart);
                return;
            }
            part->occupied = false;
        }
        offset += part->size;
        prevPart = part;
        part = part->next;
    }
}

void v_pPrint() {
    struct Partition *part = head;
    while (part != NULL) {
        printf("| s:%d o:%d ", part->size, part->occupied ? part->size : 0);
        part = part->next;
    }
    printf("|\n");
}

int testFixedPart() {
    prepare_tables();
    pPrint();
    void *p1 = alloc(30, first_fit);
    void *p2 = alloc(10, best_fit);
    void *p3 = alloc(10, worst_fit);
    dealloc(p1);
    dealloc(p3);
    dealloc(p2);
    pPrint();
}

int testVariablePart() {
    head = (struct Partition *) malloc(sizeof(struct Partition));
    initPartition(head, (int) mem_size, NULL);
    v_pPrint();
    void *p1 = v_alloc(30);
    void *p2 = v_alloc(10);
    void *p3 = v_alloc(10);
    v_dealloc(p1);
    v_dealloc(p3);
    v_dealloc(p2);
    v_pPrint();
}

int main() {
    mem = malloc(mem_size * multiplier);
    if (mem == NULL)
        return 1;
    testVariablePart();
    testFixedPart();
    free(mem);
    return 0;
}