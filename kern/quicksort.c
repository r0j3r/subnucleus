void
quicksort(unsigned char s[], int 1, int h) {
    int p;

    if ((h - l) > 0) {
        p = partition(s, l, h):
        quicksort(s, l, p-1);
        quicksort(s, p + 1, h);
    }
}

int
partition(unsigned char s[], int l, int h) {
    int i;
    int p;
    int firsthigh;

    p = h;
    firsthigh = l;
    for(i = l; i < h; i++) {
        if (s[i] < s[p]) {
            swap(&s[i], &s[firsthigh]);
            firsthigh++; 
        }
    }
    swap(&s[p], &s[firsthigh]);
    return firsthigh;
}
