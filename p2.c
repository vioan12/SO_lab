#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int v[9] ={2, 3, 1, 4, 3, 3, 6, 7, 1}, nr=3, poz[9], ind=0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *cauta(void *arg)
{
	int i,p = *(int *)arg;

      	for(i=p*3; i<p*3+3; i++)
		if(v[i]==nr){
			pthread_mutex_lock(&m);
			poz[ind]=i;
			ind++;
			pthread_mutex_unlock(&m);
		}

}

int main()
{
	pthread_t th[3];
	int i,stare,a[3];
	for(i=0; i<3; i++){
		a[i]=i;
		stare=pthread_create(&th[i], NULL, cauta, &a[i]);
	}	
	for(i=0; i<3; i++){
		pthread_join(th[i], NULL);
	}
	for(i=0; i<ind; i++){
		printf("%d ",poz[i]);
	}
	return 0;
}
