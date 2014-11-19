int insertion_sort(int s[], int l) {
    int i, x, j;

    for(i = 1; i < l; i++) {
        x = s[i];
        j = i;
        while((j > 0) && s[j - 1] > x)) {
            s[j] = s[j - 1];
            j--; 
        } 
        s[j] = x;
    }
}
