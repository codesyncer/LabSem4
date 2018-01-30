#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

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
int frag = 0;

// Finds first value in array >= x
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

// Finds value in array == x
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

void *first_fit(int size) {
    for (int i = 0; i < p_n; ++i) {
        if (p_occupied[i] == 0 && p_sizes[i] >= size) {
            p_occupied[i] = size;
            frag += p_sizes[i] - size;
            return mem + p_offset[i];
        }
    }
    return NULL;
}

// Best fits by binary-searching scan start point
void *best_fit(int size) {
    int start_scan = ge_x(p_sizes_sorted, p_n, size);
    if (start_scan == -1)
        return NULL;
    int ri;
    for (int i = start_scan; i < p_n; ++i) {
        ri = p_virtual_to_real_i[i];
        if (p_occupied[ri] == 0 && p_sizes[ri] >= size) {
            p_occupied[ri] = size;
            frag += p_sizes[ri] - size;
            return mem + p_offset[i];
        }
    }
    return NULL;
}

// Worst fits by reverse traversing sorted p_sizes
void *worst_fit(int size) {
    int ri;
    for (int i = p_n - 1; i >= 0; --i) {
        ri = p_virtual_to_real_i[i];
        if (p_occupied[ri] == 0 && p_sizes[ri] >= size) {
            p_occupied[ri] = size;
            frag += p_sizes[ri] - size;
            return mem + p_offset[ri];
        }
    }
    return NULL;
}


void *alloc(int size, void *(*fitter)(int)) {
    return fitter(size);
}

bool dealloc(void *ptr) {
    int offset = (int) (ptr - mem);
    int p_index = e_x(p_offset, p_n, offset);
    if (p_index == -1 || p_occupied[p_index] == 0)
        return false;
    frag -= (p_sizes[p_index] - p_occupied[p_index]);
    p_occupied[p_index] = 0;
    return true;
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
        p_offset[i] = p_offset[i - 1] + p_sizes[i-1];
    memcpy(p_sizes_sorted, p_sizes, p_n * sizeof(int));
    for (int i = 0; i <= p_n - 2; ++i)
        for (int j = 0; j <= p_n - i - 2; ++j)
            if (p_sizes_sorted[j] > p_sizes_sorted[j + 1]) {
                swap(p_sizes_sorted + j, p_sizes_sorted + j + 1);
                swap(p_virtual_to_real_i + j, p_virtual_to_real_i + j + 1);
            }
}


void pPrint() {
    int int_frag = 0;
    for (int i = 0; i < p_n; ++i) {
        printf("| %d/%d ", p_occupied[i], p_sizes[i]);
        if (p_occupied[i] != 0)
            int_frag += p_sizes[i] - p_occupied[i];
    }
    printf("|\n");
    printf("Internal fragmentation: %d KiB", int_frag);
}

//Variable Size Partitioning

struct Partition {
    int size;
    bool occupied;
    struct Partition *next;
};
int v_allocated = 0;

void initPartition(struct Partition *part, int size, struct Partition *next) {
    part->size = size;
    part->occupied = false;
    part->next = next;
}

struct Partition *head;

// Partially occupy a partition by splitting it into occupied and vacant partitions
struct Partition *partially_occupy(struct Partition *part, int size) {
    struct Partition *new = (struct Partition *) malloc(sizeof(struct Partition));
    if (new == NULL)
        return NULL;
    initPartition(new, part->size - size, part->next);
    part->size = size;
    part->occupied = true;
    part->next = new;
    return new;
}

// Traverse LL to find suitable partition
void *v_first_fit(int size) {
    int offset = 0;
    struct Partition *part = head;
    while (part != NULL) {
        if (part->occupied == false) {
            if (part->size > size) {
                partially_occupy(part, size);
                v_allocated += size;
                return mem + offset;
            }
            if (part->size == size) {
                part->occupied = true;
                v_allocated += size;
                return mem + offset;
            }
        }
        offset += part->size;
        part = part->next;
    }
    return NULL;
}

// Traverse LL to find partition have min extra capacity
void *v_best_fit(int size) {
    int offset = 0;
    struct Partition *part = head, *best_part = NULL;
    int min_diff = INT_MAX, best_offset = 0;
    while (part != NULL) {
        if (part->occupied == false) {
            if (part->size == size) {
                part->occupied = true;
                v_allocated += size;
                return mem + offset;
            }
            if (part->size > size && part->size - size < min_diff) {
                best_part = part;
                min_diff = part->size - size;
                best_offset = offset;
            }
        }
        offset += part->size;
        part = part->next;
    }
    if (best_part != NULL) {
        partially_occupy(best_part, size);
        v_allocated += size;
        return mem + best_offset;
    }
    return NULL;
}

// Traverse LL to find partition having max extra capacity
void *v_worst_fit(int size) {
    int offset = 0;
    struct Partition *part = head, *worst_part = NULL;
    int max_diff = -1, worst_offset = 0;
    while (part != NULL) {
        if (part->occupied == false) {
            if (part->size >= size && part->size - size > max_diff) {
                worst_part = part;
                max_diff = part->size - size;
                worst_offset = offset;
            }
        }
        offset += part->size;
        part = part->next;
    }
    if (worst_part != NULL) {
        if (worst_part->size == size) {
            worst_part->occupied = true;
            v_allocated += size;
            return mem + worst_offset;
        } else {
            partially_occupy(worst_part, size);
            v_allocated += size;
            return mem + worst_offset;
        }
    }
    return NULL;
}

void *v_alloc(int size, void *(*fitter)(int)) {
    return fitter(size);
}

// Deallocate partition and merge with vacant neighbours if any
bool v_dealloc(void *ptr) {
    int dest_offset = (int) (ptr - mem), offset = 0;
    struct Partition *part = head, *prevPart = NULL;
    while (part != NULL) {
        if (offset == dest_offset) {
            v_allocated -= part->size;
            struct Partition *nextPart = part->next;
            if (prevPart != NULL && prevPart->occupied == false && nextPart != NULL && nextPart->occupied == false) {
                prevPart->size += part->size + nextPart->size;
                prevPart->next = nextPart->next;
                free(part);
                free(nextPart);
                return true;
            }
            if (prevPart != NULL && prevPart->occupied == false) {
                prevPart->size += part->size;
                prevPart->next = nextPart;
                free(part);
                return true;
            }
            if (nextPart != NULL && nextPart->occupied == false) {
                part->size += nextPart->size;
                part->next = nextPart->next;
                part->occupied = false;
                free(nextPart);
                return true;
            }
            part->occupied = false;
            return true;
        }
        offset += part->size;
        prevPart = part;
        part = part->next;
    }
    return false;
}

void v_pPrint() {
    struct Partition *part = head;
    while (part != NULL) {
        printf("| %d/%d ", part->occupied ? part->size : 0, part->size);
        part = part->next;
    }
    printf("|\n");
}

int testFixedPart() {
    prepare_tables();
    int option = 0, size;
    void *loc;
    while (option != 6) {
        printf("\n\n1) First Fit Allocate\n2) Best Fit Allocate\n3) Worst Fit Allocate\n4) Deallocate\n5) Show Partitioning\n6) Quit");
        printf("\nEnter option: ");
        scanf("%d", &option);
        printf("\n");
        switch (option) {
            case 1:
            case 2:
            case 3:
                printf("Enter size of process: ");
                scanf("%d", &size);
                loc = alloc(size, option == 1 ? first_fit : option == 2 ? best_fit : worst_fit);
                if (loc == NULL)
                    printf("Unable to allocate");
                else printf("Allocated %d KiB at %p, offset %d", size, loc, (int) (loc - mem));
                break;
            case 4:
                printf("Enter offset of process: ");
                scanf("%d", &size);
                if (dealloc(mem + size))
                    printf("Deallocated!");
                else
                    printf("Failed!");
                break;
            case 5:
                pPrint();
                break;
            case 6:
                break;
            default:
                break;
        }
    }
}

int testVariablePart() {
    head = (struct Partition *) malloc(sizeof(struct Partition));
    initPartition(head, (int) mem_size, NULL);
    int option = 0, size;
    void *loc;
    while (option != 6) {
        printf("\n\n1) First Fit Allocate\n2) Best Fit Allocate\n3) Worst Fit Allocate\n4) Deallocate\n5) Show Partitioning\n6) Quit");
        printf("\nEnter option: ");
        scanf("%d", &option);
        printf("\n");
        switch (option) {
            case 1:
            case 2:
            case 3:
                printf("Enter size of process: ");
                scanf("%d", &size);
                loc = v_alloc(size, option == 1 ? v_first_fit : option == 2 ? v_best_fit : v_worst_fit);
                if (loc == NULL)
                    printf("Unable to allocate %s",
                           v_allocated + size <= mem_size ? "due to external fragmentation" : "");
                else printf("Allocated %d KiB at %p, offset %d", size, loc, (int) (loc - mem));
                break;
            case 4:
                printf("Enter offset of process: ");
                scanf("%d", &size);
                if (v_dealloc(mem + size))
                    printf("Deallocated!");
                else
                    printf("Failed!");
                break;
            case 5:
                v_pPrint();
                break;
            case 6:
                break;
            default:
                break;
        }
    }
}

int main() {
    mem = malloc(mem_size * multiplier);
    if (mem == NULL)
        return 1;
//    Uncomment any ONE tester to test
//    testVariablePart();
    testFixedPart();
    free(mem);
    return 0;
}