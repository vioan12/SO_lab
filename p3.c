#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
     
int vector[20];
int childnr=5;
int nr=20;
int suma=0;
     
void childProc(int readPipe, int writePipe) 
{
	int sum1=0;
	int i;
	int j=0;
	read(readPipe, &i,4);
	for(j=i*(nr/childnr);j<(i+1)*(nr/childnr);j++){
		if(j<nr){
			sum1=sum1+vector[j];
		}
	}
      	write(writePipe, &sum1, 4);
      	printf("suma partiala este %d \n",sum1);
      	exit(1);
}
     
void parentProc(int readPipe, int writePipe) 
{
        int rez,j;
        for(j=0;j<nr;j++){
        	write(writePipe, &j, 4);
	}
    	for(j=0;j<childnr;j++){
        	read(readPipe, &rez, 4);
        	suma=suma+rez;
	}
}
     
int main()
{
	int i;
    	int firstPipe[2];
	int secondPipe[2];
      	int pid;
     
    	for(i=0;i<20;i++){
      		vector[i]=i;
    	}
      	if (pipe(firstPipe)){
        	printf("Nu am putut crea conducta!\n");
        	exit(-1);
      	}
      	if (pipe(secondPipe)){
        	printf("Nu am putut crea conducta!\n");
        	exit(-1);
      	}
     
    	for(i=0;i<childnr;i++){
        	pid=fork();
        	if(pid){
           		if(pid==-1){  
                  		printf("Nu am reusit crearea procesului copil.\n");
                  		exit(-1);
              		}
         	} else {
               		childProc(firstPipe[0], secondPipe[1]);
             	}
    	}
    	parentProc(secondPipe[0], firstPipe[1]);
     	wait(NULL);
      	printf("Procesul principal gata!\n");
      	printf("suma totala este %d\n",suma);
    	wait(NULL);
	return 0;
}


