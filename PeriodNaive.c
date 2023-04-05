int PeriodNaive (char *X, int size) {       //fare partire X da 1
    int p,j;
    for (p=1; p<=size; p++) {
        for (j=p+1; j<=size; j++) {
            if ( X[j]!=X[j-p]) break;
        }
        if (j==size) return p;
    }
    return p;
}
