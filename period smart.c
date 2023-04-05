//versione smart
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int *a, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}

#define MAX_LINE_SIZE 10000   // maximum size of a line of input

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
}



int periodSmart(char s[],int n){
    int vettore[n];
    vettore[1]=0;
    int x;
    printf("prima del for");
    for(int i=2; i<abs(n); i++){
        printf("dentro del for di %d: ",i);

        x = vettore[i-1];
        while(x>0 && s[x+1]!=s[i]){
            printf("dentro del while");
            x = vettore[x];
        }

        if(s[x+1] == s[i]) //controllare se il confronto va bene
        {
            printf("siamo nell'if");
            x++;
        }else{
            vettore[i] = x;
            printf("siamo nell'else");

        }
    }
    printf("prima del return");
    return 4;//abs(*s) - vettore[abs(*s)];
}

int main(){
    char array[100];
    int n = scanArray(array);
    int valore = periodSmart(array,n);
    printf("%d",n);
    //printf("\n %d",valore);
    return 0;
}