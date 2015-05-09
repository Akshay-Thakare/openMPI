//By Akshay Thakare

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

#define MAX_NUMBERS 100

int main(int argc, char ** argv)
{
	MPI_Init(&argc,&argv);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);

	if(world_size!=2)
	{
		fprintf(stderr,"Must have two processes atleast");
		MPI_Abort(MPI_COMM_WORLD,1);
	}

	int rank;
	int numbers[MAX_NUMBERS];
	int number_amount;

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0)
	{
		srand(time(NULL));		//Intial seed for random generator
		number_amount = (rand()/(float)RAND_MAX)*MAX_NUMBERS;

		MPI_Send(numbers,number_amount,MPI_INT,1,0,MPI_COMM_WORLD);
		printf("0 sent %d numbers to 1\n",number_amount);
	}
	if(rank==1)
	{
		MPI_Status status;
		MPI_Recv(numbers,MAX_NUMBERS,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		MPI_Get_count(&status,MPI_CHAR,&number_amount);
		printf("1 recieved %d numbers from 0. Message source = %d, tag = %d\n", number_amount,status.MPI_SOURCE,status.MPI_TAG);
	}

	//MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
