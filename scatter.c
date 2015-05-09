//By Akshay Thakare

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char ** argv)
{
	MPI_Init(&argc,&argv);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);

	MPI_Barrier(MPI_COMM_WORLD);

	int b[4];

	if(world_rank==0)
	{
		int a[4]={5,7,4,3};
		MPI_Scatter(&a,2,MPI_INT,&b,4,MPI_INT,0,MPI_COMM_WORLD);
	}
	else
	{
		MPI_Scatter(&b,2,MPI_INT,&b,4,MPI_INT,0,MPI_COMM_WORLD);
		printf("%d %d\n",b[0],b[1]);
	}

	MPI_Finalize();
	return 0;
}
