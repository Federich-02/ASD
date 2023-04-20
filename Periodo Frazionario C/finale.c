//progetto laboratorio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//#define MAX_LINE_SIZE 10000   // maximum size of a line of input
#define A  100.0
#define RIPETIZIONI  20  //numero di ripetizioni del secondo ciclo for (quello per poi prendere la mediana)

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
    double chiave;
    int i;
     for(int j=1;j<RIPETIZIONI;j++){
            chiave=vett[j];
            i=j-1;
            while(i>=0 && vett[i]>chiave){
                vett[i+1]=vett[i];
                i=i-1;
            }
            vett[i+1]=chiave;
     }
}

void  periodoFrazionario(int algoritmo,int caso,double resolution,struct timespec start_time,struct timespec end_time,int n,char stringaNuova[],double tempiMediana[]){ 
    for(int i=98; i<100; i++){
            n=floor(A*pow(1.06478598,i));

            for(int j=0;j<RIPETIZIONI;j++){
                int count=0;
                if(caso != 0) //caso medio o peggiore
                    string_gen(n,stringaNuova);
                else
                    string_peggiore(n,stringaNuova);

                clock_gettime(CLOCK_MONOTONIC, &start_time);
                do{
                    
                    if(algoritmo==1) //naive o smart
                        periodNaive(stringaNuova,n);
                    else
                        periodSmart(stringaNuova,n);
                    count ++;
                    clock_gettime(CLOCK_MONOTONIC, &end_time);
                }while(duration(start_time,end_time) <= (resolution*(1.0+1.0/0.001)));

                double tempo = duration(start_time,end_time) / (double)count;
                tempiMediana[j]=tempo;
            }
            //ordinamento del vettore
            inserctionSort(tempiMediana);
            printf(" %d\t%d\t%f\n",i,n,tempiMediana[RIPETIZIONI/2]);

        }

}

int main()
{
    //VARIABILI:
    double resolution=getResolution();
    struct timespec start_time;
    struct timespec end_time;
    int n=0;
    char stringaNuova[50000];
    double tempiMediana[RIPETIZIONI];
    
        printf("\n\n naive pessimo \n\n");
    periodoFrazionario(1,0,resolution,start_time,end_time,n,stringaNuova,tempiMediana); //naive pessimo
        printf("\n\n nave medio \n\n");
    periodoFrazionario(1,1,resolution,start_time,end_time,n,stringaNuova,tempiMediana); //naive medio
        printf("\n\n smart pessimo \n\n");
    periodoFrazionario(2,0,resolution,start_time,end_time,n,stringaNuova,tempiMediana); //smart pessimo
        printf("\n\n smart medio \n\n");
    periodoFrazionario(2,1,resolution,start_time,end_time,n,stringaNuova,tempiMediana); //smart medio
    
    printf("fine");
    return 0;
}
