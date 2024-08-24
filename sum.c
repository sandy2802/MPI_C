//Sum of N numbers
#include<stdio.h>
#include "mpi.h"
#include<stdlib.h>
#include<time.h>
#define MAX 10000

int sum(int arr[], int size)
{
    int res=0;
    for(int i=0; i<size; i++)
        res=res+arr[i];
    return res;
}

int main(int argc, char **argv)
{
    int num[MAX], total=0, MyRank, Numprocs, i;
    int u, l, elements_per_proc;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
    elements_per_proc=MAX/Numprocs;
    int *subset = malloc(sizeof(int) * elements_per_proc);
    if(MyRank==0)
    {   //Generate N random numbers 
        srand(time(0));
        for(i=0;i<MAX;i++)
        {
            l=1,u=100;
            num[i]=(rand()%(u-l+1))+l;
        }
    }
    MPI_Scatter(num, elements_per_proc, MPI_INT, subset, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
    int partial_sum=sum(subset,elements_per_proc);
    MPI_Reduce(&partial_sum,&total,Numprocs,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(MyRank==0)
    {
        printf("Final sum using %d processors=%d",Numprocs,total);
        free(subset);
    }     
    MPI_Finalize();
}
