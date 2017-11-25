#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int v[9] ={2, 3, 1, 4, 3, 3, 6, 7, 1}, nr=3, poz[9], ind=0,x[9],n_x=0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *cauta(void *arg)
{
	int i,p = *(int *)arg;

      	for(i=p*3; i<p*3+3; i++)
		if(n_x==0){
			pthread_mutex_lock(&m);
			x[0]=v[i];
			n_x++;
			pthread_mutex_unlock(&m);
		}else{
			
			int j=0;
			while((v[i]>x[j])&&(j<n_x))
				j++;
			pthread_mutex_lock(&m);
			int k;
			n_x++;			
			for(k=n_x;k>j;k--)
				x[k]=x[k-1];
			x[j]=v[i];
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
	for(i=0; i<9; i++){
		printf("%d ",x[i]);
	}
	return 0;
}
