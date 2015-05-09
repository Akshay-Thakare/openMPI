//By Akshay Thakare

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char ** argv)
{
	MPI_Init(&argc,&argv);

	int rank;

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank == 0)
		printf("HI");
	else
		printf("HELLO");

	MPI_Finalize();
	return 0;
}
