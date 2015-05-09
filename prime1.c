#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define N 1000

int rank, size;
int i, x, y, port1, port2;
int flag =0;

MPI_Status status;
MPI_Request request;

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv); //initialize MPI operations
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //get the rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); //get number of processes

	if(rank == 0)				// master process divides work and also does initial  work itself
	{                  
		printf("2\n");                 
		
		//considering only 2 process.
		port1 = N/2;		         // calculating the suitable amount of work per process
		port2 = port1+1;		
		
		MPI_Isend(&port2, 1, MPI_INT, 1, 100, MPI_COMM_WORLD, &request);

		for(x = 3; x < port1; x=x+2)
		{    							// master doing initial work by itself
			flag = 0;
			for(y = 3; y <= x/2; y=y+2)
			{
				if(x%y == 0) 
				{
					flag=1; 
					break;
				}
			}
			if(flag==0) 
				printf("%d\t", x);
		}
	}
	else
	{                    // slave working part
		MPI_Recv(&port2,1,MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
		if (port2%2 == 0) 
			port2++;              // changing the even argument to odd to make the calculation fast because even number is never a prime except 2.
		for(x=port2; x<=N; x=x+2)
		{
			flag = 0;
			for(y = 3; y <= x/2; y=y+2)
			{
				if(x%y == 0) 
				{
					flag=1; 
					break;
				}
			}
			if (flag==0) 
				printf("%d\t",x);
		}
	}
  	 if(rank>1)
		continue;
   	MPI_Finalize();
   	return 0;
} 
