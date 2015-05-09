//By Akshay Thakare

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

void my_bcast(void *data,int count, MPI_Datatype datatype, int root, MPI_Comm communicator)
{
	int world_rank;
	MPI_Comm_rank(communicator,&world_rank);

	int world_size;
	MPI_Comm_size(communicator,&world_size);

	if(world_rank==root)
	{
		int i;
		for(i=0;i<world_size;i++)
		{
			if(i!=world_rank)
			{
				MPI_Send(data,count,datatype,i,0,communicator);
			}
		}
	}
	else
	{
		MPI_Recv(data,count,datatype,root,0,communicator,MPI_STATUS_IGNORE);
	}
}

int main(int argc, char ** argv)
{
	MPI_Init(&argc,&argv);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);

	double total_my_bcast_time = 0.0;
	double total_mpi_bcast_time=0.0;

	int i;
	int *data = (int *)malloc (sizeof(int) * 1000);	//num_elements

	for(i=0;i<10;i++)		//num_trials
	{
		MPI_Barrier(MPI_COMM_WORLD);
		total_my_bcast_time -=MPI_Wtime();
		my_bcast(data,1000,MPI_INT,0,MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		total_my_bcast_time +=MPI_Wtime();

		MPI_Barrier(MPI_COMM_WORLD);
		total_mpi_bcast_time -= MPI_Wtime();
		MPI_Bcast(data,1000,MPI_INT,0,MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		total_mpi_bcast_time += MPI_Wtime();
	}

	if(world_rank == 0)
	{
		printf("Avg my_bcast time = %lf\n",total_my_bcast_time/10);
		printf("Avg MPI_Bcast time = %lf\n",total_mpi_bcast_time/10);
	}

	MPI_Finalize();
	return 0;
}
