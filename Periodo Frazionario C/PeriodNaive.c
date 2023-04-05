int PeriodNaive (char *X, int size) {       //fare partire X da 1
    int p,j;
    for (p=1; p<=size; p++) {
        for (j=p+1; j<=size && X[j]==X[j-p]; j++) {
            if ( j==size ) return p;
        }
    }
    return p-1;
}
