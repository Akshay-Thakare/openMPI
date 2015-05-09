#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc ,char **argv)
{
	int id,nop;
	int i,n;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nop);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	if(id==0)
	{
		printf("\nEnter no to check: ");
		scanf("%d",&n);
	
		if(n%2==0)
			printf("\n%d is even ",n);
		else
			printf("\n%d is odd ",n);
	}
	MPI_Finalize();
	return 0;
}
