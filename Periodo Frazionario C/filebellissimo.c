  #include <stdio.h>
  #include <time.h>

  void string_gen (int n, char *B);

  int main() {
    char B[101];
    string_gen(101,B);
    printf("%d %d", PeriodNaive(B,100), PeriodSmart(B,100));
    return 0;
  }

  void string_gen (int n, char *B) {
    srand(time(NULL));
    int j, q=rand()%(n+1);
    printf("%d ", q);
    for (j=1; j<=n; j++) {
      if (j<=q) B[j]=rand()%3+97;
      else {
        B[j]=B[j-q];
      }
    }
    for (j=1; j<=n; j++) putchar(B[j]);
  }

  int PeriodNaive (char *X, int size) {       //fare partire X da 1
    int p,j;
    for (p=1; p<=size; p++) {
        for (j=p+1; j<=size && X[j]==X[j-p]; j++) {
            if ( j==size ) return p;
        }
    }
    return p-1;
}

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
