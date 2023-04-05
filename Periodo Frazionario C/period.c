#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

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

double calculateTmin(double resolution){
	return resolution*(1+1/0.001);
}

/*double calculateA(int n,int i){
	
}*/

double calculateB(int A, int n, int i){
	return pow(n/A,1/99);
}


int periodNaive(){
	
}

int peroidSmart(){
	
}

int main(){
	
	double resolution=getResolution();
	
	for(int i=0;i<100;i++){
		int A=1000;
		int B=calculateB(A,500000,i);
		n=floor(A*pow(B,i));
		int count=0;
		double start_time=clock_gettime((CLOCK_MONOTONIC, &timeNow);
		do{
			
		}while(end_time-start_time<=calculateTmin(resolution))
		
	}
	
}