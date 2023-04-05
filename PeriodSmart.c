int PeriodSmart (char *S, int size) {
    int B[size], i, x;
    B[1]=0;
    for (i=2; i<=size; i++) {
        x=B[i-1];
        while (x>0 && S[x+1]!=S[i]) x=B[x];
        if (S[x+1]==S[i]) x++, B[i]=x;
        else B[i]=x;
    }
    return size-B[size];
}
