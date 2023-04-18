//progetto laboratorio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


//#define MAX_LINE_SIZE 10000   // maximum size of a line of input
#define A  1000
#define RIPETIZIONI  2  //numero di ripetizioni del secondo ciclo for (quello per poi prendere la mediana)


/*
int scanArray(char *a) {
    // scan line of text
    char line[MAX_LINE_SIZE];
    scanf("%[^\n]", line);

    getchar();
    // convert text into array
    int size = 0, offset = 0, numFilled, n;
    do {
        numFilled = sscanf(line + offset, "%c%n", &(a[size]), &n);
        if (numFilled > 0) {
            size++;
            offset += n;
        }
    } while (numFilled > 0);

    return size;
}*/

void printArray(char *a, int n) {
    for (int i = 0; i < n; i++)
        printf("%c ", a[i]);
}

double duration(struct timespec start, struct timespec end) {
    return end.tv_sec - start.tv_sec
         + ((end.tv_nsec - start.tv_nsec ) / (double) 1000000000.0);
}

double getResolution(){
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while (duration(start, end) == 0.0);
    return duration(start, end);
}

int periodNaive (char s[], int size) {       
    int p,j;
    for (p=1; p<=size; p++) {

        for (j=p+1; j<=size && s[j]==s[j-p]; j++) {
            if ( j==size ) 
                return p;
        }
    }
    return p-1;
}


int periodSmart(char s[],int n){
    int vettore[n+1];
    vettore[1]=0;
    int x;
    for(int i=2; i<=n; i++){
        x = vettore[i-1];
        while(x>0 && s[x+1]!=s[i]){
            x = vettore[x];
        }

        if(s[x+1] == s[i]) 
        {
            x++;
        }
        vettore[i] = x;
    }
    return (n - vettore[n]);
}

void string_gen (int n, char *B) {
    srand(time(NULL));
    int j;
    int q = rand()%(10+1);
    printf("%d ", q);
    for (j=1; j<=n; j++) {
      if (j<=q) 
        B[j]=rand()%3+97; //prendere le lettere possibili a b c
      else {
        B[j]=B[ (j-1)%q +1]; // j - q
      }
    }
    //visualizziamo la stringa
    /*for (j=1; j<=n; j++) 
        putchar(B[j]);*/
}

int main()
{
    /*
    char array[100];
    char arrayGiusto[100];
    int n = scanArray(array);
    for(int i=0;i<n;i++){
        arrayGiusto[i+1] = array[i];
    }
    int valore = periodSmart(arrayGiusto,n);
    printf("%d",n);
    printf("\n%d",valore);
    */

    //VARIABILI:
    double vettValoriRipetuti[100*RIPETIZIONI]; //vettore dove salvare i tempi e cercare la mediana
    double vettTempo[100];//vettore dove salvare il tempo mediano

    double resolution=getResolution();
    int n=0;
	struct timespec timeNow;
	struct timespec start_time;
	struct timespec end_time;

	for(int i=0; i<100; i++){
        printf("ciclo i: %d\n",i);
		n=floor(A*pow(1.06478598,i));
		int count=0;
        //for per misurare piu' volte  
       for(int j=0;j<RIPETIZIONI;j++){
           printf("ciclo ripetizione: %d\n",j);
            char stringaNuova[n]; 
            string_gen(n,stringaNuova);
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            do{
                //printf("dentro il while con count: %d\n",count);
                periodSmart(stringaNuova,n);
                count ++;
                clock_gettime(CLOCK_MONOTONIC, &end_time);
            }while( duration(start_time, end_time) <= (resolution*(1+1/0.001)) );
            
            double tempo = duration (start_time, end_time) / count;
            printf("%d%f \n",n,tempo);
       }
	}

    //codice per calcolare la mediana dei tempi, considerare 'RIPETIZIONI' 
    printf("fine");
    return 0;
}
