//By Akshay Thakare

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

#define MAX_NUMBER 100

int main(int argc, char ** argv)
{
	MPI_Init(&argc,&argv);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);

	if(world_size!=2)
	{
		fprintf(stderr,"Input size should be 2");
		MPI_Abort(MPI_COMM_WORLD,1);
	}

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);

	int number_amount;
	
	if(world_rank==0)
	{
		int numbers[MAX_NUMBER];
		srand(time(NULL));
		number_amount = (rand()/(float)RAND_MAX)*MAX_NUMBER;
		MPI_Send(numbers,number_amount,MPI_INT,1,0,MPI_COMM_WORLD);
		printf("0 sent %d numbers to 1\n",number_amount);
	}
	if(world_rank==1)
	{
		MPI_Status status;
		MPI_Probe(0,0,MPI_COMM_WORLD,&status);
		MPI_Get_count(&status,MPI_INT,&number_amount);

		int *buff;
		buff = (int *)malloc(number_amount * sizeof(int));
		MPI_Recv(buff,number_amount,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("1 dynamically recieved %d numbers from 0.\n",number_amount);
		free(buff);
	}

	MPI_Finalize();
	return 0;
}
