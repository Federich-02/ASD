//progetto laboratorio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//#define MAX_LINE_SIZE 10000   // maximum size of a line of input
#define A  100.0
#define RIPETIZIONI  5  //numero di ripetizioni del secondo ciclo for (quello per poi prendere la mediana)


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

void printArray(double a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%f ", a[i]);
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
    int q = rand()%(n)+1;
    //printf("q random:%d ", q);
    for (j=1; j<=n; j++) {
      if (j<=q)
        B[j]=rand()%3+'a'; //prendere le lettere possibili a b c
      else {
        B[j]=B[j-q]; // j - q
      }
    }
}

void string_peggiore(char str[],int n){
    for(int i=0; i<n; i++){
        str[i]='a';
    }
    str[n]='b';
}

//INSERCTIONSORT
void inserctionSort(double vett[]){
    for(int i=0;i<RIPETIZIONI;i++){
        vett[i] = vett[i]*(pow(10,8));
    }
    double chiave;
    int i;
     for(int j=2;j<RIPETIZIONI;j++){
            chiave=vett[j];
            i=j-1;
            while(i>=0 && vett[i]>chiave){
                vett[i+1]=vett[i];
                i=i-1;
            }
            vett[i+1]=chiave;
     }
    for(int i=0;i<RIPETIZIONI;i++){
        vett[i] = vett[i]/(pow(10,8));
    }
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
    struct timespec start_time;
    struct timespec end_time;
    int n=0;
    char stringaNuova[50000];
    double tempiMediana[RIPETIZIONI];
     
	for(int i=0; i<100; i++){
		n=floor(A*pow(1.06478598,i));

        for(int j=0;j<RIPETIZIONI;j++){
           	int count=0;
            string_gen(n,stringaNuova);
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            do{
                periodNaive(stringaNuova,n);
                count ++;
                clock_gettime(CLOCK_MONOTONIC, &end_time);
            }while(duration(start_time,end_time) <= (resolution*(1.0+1.0/0.001)));

            double tempo = duration(start_time,end_time) / (double)count;
            //printf("%f\n",tempo);
            tempiMediana[j]=tempo;
        }
        //ordinamento tempiMEdiana[]
        inserctionSort(tempiMediana);
        printArray(tempiMediana,RIPETIZIONI);
        printf("%d\t%d\t%f\n",i,n,tempiMediana[RIPETIZIONI/2]);
	}
/*
    printf("\n\n switch algoritm \n\n");
	for(int i=0; i<100; i++){

		n=floor(A*pow(1.06478598,i));

        for(int j=0;j<RIPETIZIONI;j++){
           	int count=0;
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            do{
                periodSmart(stringaNuova,n);
                count ++;
                clock_gettime(CLOCK_MONOTONIC, &end_time);
            }while(duration(start_time,end_time) <= (resolution*(1.0+1.0/0.001)));

            double tempo = duration(start_time,end_time) / (double)count;
            tempiMediana[j]=tempo;

        }
        inserctionSort(tempiMediana);
        printf("%d\t%d\t%f\n",i,n,tempiMediana[RIPETIZIONI/2]);
	}
    */
    printf("fine");
    return 0;
}
