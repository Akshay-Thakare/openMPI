//By Akshay Thakare

#include<mpi.h>
#include<stdio.h>

int main(int argc, char ** argv)
{
	MPI_Init(&argc,&argv);

	int rank;
	char a[6]="HELLO";

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0)
		MPI_Send(&a,5,MPI_CHAR,1,0,MPI_COMM_WORLD);
	else
	{
		char p[6];
		MPI_Recv(&p,5,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("%s\n",p);
	}

	MPI_Finalize();
	return 0;
}
