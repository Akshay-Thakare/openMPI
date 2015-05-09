//By Akshay Thakare

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char ** argv)
{
	MPI_Init(&argc,&argv);

	int rank,size;
	char hostname[20];

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	//MPI_GET_PROCESSOR_NAME(PROCESSOR_NAME,&name);
	gethostname(hostname,20);

	printf("HI %d\t%d\t%s\n",rank,size,hostname);

	MPI_Finalize();
	return 0;
}
