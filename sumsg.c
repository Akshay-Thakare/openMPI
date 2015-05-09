#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int world_size,world_rank;

int main(int argc,char **argv)
{
	int *mydata,*send_data,*back_data;
	int count;
	int size,mysize,i,k,j,sum;

	MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &world_size );
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	count=4;
	mydata=(int*)malloc(count*sizeof(int));

	if(world_rank == 0)
	{
	    size=count*world_size;
		send_data=(int*)malloc(size*sizeof(int));
		back_data=(int*)malloc(world_size*sizeof(int));
		for(i=0;i<size;i++)
			send_data[i]=i;
	}

	MPI_Scatter(send_data , count , MPI_INT , mydata , count , MPI_INT , 0 , MPI_COMM_WORLD);
	sum=0;
	for(i=0;i<count;i++)
	    sum=sum+mydata[i];
	printf("For world_rank= %d ---> Sum= %d\n ",world_rank,sum);

    MPI_Gather(&sum, 1 , MPI_INT , back_data , 1 , MPI_INT , 0 , MPI_COMM_WORLD);

	if(world_rank == 0)
	{
	  sum=0;
	  for(i=0;i<world_size;i++)
	    sum+=back_data[i];
	  printf("Results from all processors= %d \n ",sum);
	}
    MPI_Finalize();
    return 0;
}
