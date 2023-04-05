int PeriodSmart (char *X, int size) {
    int B[size], i, x;
    B[1]=0;
    for (i=2; i<=size; i++) {
        x=B[i-1];
        while (x>0 && X[x+1]!=X[i]) x=B[x];
        if (X[x+1]==X[i]) x++, B[i]=x;
        else B[i]=x;
    }
    return size-B[size];
}
