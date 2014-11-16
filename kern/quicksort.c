#include "random.h"

int partition(int s[], int l, int h);

void
quicksort(int s[], int l, int h) {
    int p;

    if ((h - l) > 0) {
        p = partition(s, l, h);
        quicksort(s, l, p - 1);
        quicksort(s, p + 1, h);
    }
}

int pivot(int, int);
void swap(int *, int *);

int
partition(int s[], int l, int h) {
    int i;
    int p;
    int v;
    int firsthigh;

    p = pivot(l, h);
    v = s[p];
    swap(&s[h], &s[p]);
    firsthigh = l;
    for(i = l; i < h; i++) {
        if (s[i] < v) {
            swap(&s[i], &s[firsthigh]);
            firsthigh++; 
        }
    }
    swap(&s[h], &s[firsthigh]);
    return firsthigh;
}

int pivot(int l, int h) {
    return (get_random(4) % (h - l)) + l ;
}

void swap(int * l, int * r) {
    int s = *l;
    *l = *r;
    *r = s;
}
