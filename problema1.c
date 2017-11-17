#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int *sir;

struct pass{
	int start,end;
	int s;
};

void* add(void *p)
{
	int i;
	struct pass *pp=(struct pass*)p;
	pp->s=0;
	for(i= pp->start; i<pp->end; i++)
		pp->s +=*(sir+i);
}

int main()
{

 	pthread_t th[4];
	struct pass v[4];
 	int i,suma=0,stare,m;

	scanf("%d",&m);
	sir=(int *)malloc(m*sizeof(int));
	for(i=0; i<m; i++)
		*(sir+i)=i;
	for(i=0; i<4; i++){
		v[i].start=i*(m/4);
		if(i==3 && (i+1)*(m/4)<m)
			v[i].end=m;
		else
			v[i].end=(i+1)*(m/4);
	}
		
	for(i=0; i<4; i++)
		stare=pthread_create(&th[i], NULL, add, &v[i]); 	
	for(i=0; i<4; i++){
		pthread_join(th[i], NULL);
		suma+=v[i].s;
	}
	printf("Suma este:%d",suma);
	return 0;
		
}
