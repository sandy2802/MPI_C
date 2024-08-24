//Prime numbers between 1-1000
#include<stdio.h>
#include "mpi.h"
#include<stdlib.h>
#include<math.h>
#define MAX 500

int checkPrime(int n)
{
    if(n==1)
        return 0;
    else
    {
        for(int i=2;i<=sqrt(n);i++)
        {
            if(n%i==0)
                return 0;
        }
        return 1;
    }
}

void PrintPrime(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        if(checkPrime(arr[i]))
            printf("%d, ",arr[i]);
    }
    
}

int main(int argc, char **argv)
{
    int num[MAX], total=0, MyRank, Numprocs, i, elements_per_proc;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);
    elements_per_proc=MAX/Numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
    int *subset = malloc(sizeof(int) * elements_per_proc);
    if(MyRank==0)
    {
        for(i=0;i<MAX;i++)
            num[i]=i+1;
    }
    MPI_Scatter(num, elements_per_proc, MPI_INT, subset, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Prime numbers from processor %d - ",MyRank);
    PrintPrime(subset,elements_per_proc);
    
    if(MyRank==0)
        free(subset);
    MPI_Finalize();


}
