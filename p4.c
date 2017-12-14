#include <stdio.h>
#include <process.h>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
HANDLE evast[4];
int v[] = {3,1,2,4,-2,6,22,11,-1};
int n = 9;
void aduna(void* args);
struct pass
{
	int start,end;
	int s;
	int nr_fir;
};
int suma = 0;
HANDLE hMutex1, hMutex2;
void aduna(void *p)
{
    int i;

    struct pass *pp=(struct pass*)p;
	pp->s=0;
	for(i= pp->start; i<pp->end; i++)
		pp->s +=*(v+i);

    WaitForSingleObject(hMutex1, INFINITE);
    printf("firul %d cu %d elemente de adunat\n", pp->nr_fir, pp->end-pp->start);
    printf("\tElementele sunt:");
    for (int i = pp->start; i < pp->end; i++)
        printf(" %d ", v[i]);
    printf("\n");
    ReleaseMutex(hMutex1);

    int temp = 0;
    for ( i = pp->start; i <  pp->end; i++)
        temp += v[i];

    WaitForSingleObject(hMutex2, INFINITE);
    suma += temp;
    ReleaseMutex(hMutex2);
    SetEvent(evast[pp->nr_fir]);
}

int main()
{
    struct pass v[4];
    int i;
    // Create a mutex with no initial owner.
    hMutex1 = CreateMutex(
        NULL, // no security attributes
        FALSE, // initially not owned
        "mutex pentru printf"); // name of mutex
    if (hMutex1 == NULL)
    {
        ExitProcess(0);
        // Check for error.
    }
    hMutex2 = CreateMutex(
        NULL, // no security attributes
        FALSE, // initially not owned
        "mutex pentru suma"); // name of mutex
    if (hMutex2 == NULL)
    {
        ExitProcess(0);
        // Check for error.
    }
    int nrFire = 3;
    for(i=0; i<nrFire; i++){
		v[i].start=i*(n/nrFire);
		if(i==2 && (i+1)*(n/nrFire)<n)
			v[i].end=n;
		else
			v[i].end=(i+1)*(n/nrFire);
        v[i].nr_fir=i;
	}
    for( int i=0; i< nrFire; i++){
        evast[i]= CreateEvent(
        NULL, // no security attributes
        TRUE, // manual-reset event object
        FALSE, // initial state is nonsignaled
        NULL); // unnamed object
        if (evast[i] == NULL) {
            printf("CreateEvent error: %d\n", (int)GetLastError() );
            ExitProcess(0);
        }
        _beginthread(aduna, 0,  &v[i]);
    }
    WaitForMultipleObjects(
        nrFire, // number of objects in array
        evast, // array of objects
        TRUE, // wait for all
        INFINITE);
    printf("suma este %d\n", suma);
    return 0;
}
