//MAX of N numbers
#include<stdio.h>
#include "mpi.h"
#include<stdlib.h>
#include<time.h>
#define MAX 1000

int max(int arr[], int size)
{
    int m=arr[0];
    for(int i=1; i<size; i++)
        if(arr[i]>m)
            m=arr[i];
    return m;
}
int main(int argc, char **argv)
{
    int num[MAX], final_max, MyRank, Numprocs;
    int u, l, i, elements_per_proc;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);
    elements_per_proc=MAX/Numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
    int *subset = malloc(sizeof(int) * elements_per_proc);
    if(MyRank==0)
    {
        //Generate N random numbers 
        srand(time(0));
        for(i=0;i<MAX;i++)
        {
            l=1,u=1000;
            num[i]=(rand()%(u-l+1))+l;
        }
    }
    MPI_Scatter(num, elements_per_proc, MPI_INT, subset, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
    int partial_max=max(subset,elements_per_proc);
    MPI_Reduce(&partial_max,&final_max,Numprocs,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
    if(MyRank==0)
    {
        printf("Overall maximum using all processors=%d",final_max);
        free(subset);
    }

    MPI_Finalize();
}
