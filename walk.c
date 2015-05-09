//By Akshay Thakare, Jeet and Monish

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#define SIZE 20

int main(int argc ,char **argv)
{
	int domain[SIZE]={0},start_pos,end_pos,world_rank,world_size,subdomain,cur_pos;
	int i,n,count=0;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	if(world_rank==0)
	{
		printf("\nEnter size of domain from 1 to %d: ",SIZE);
		scanf("%d",&n);
	}
	
	subdomain=n/world_size; 		//check
	start_pos=world_rank*subdomain;
	if(world_rank==(world_size-1))
		end_pos=n;
	else
		end_pos=start_pos+subdomain-1;
	
	while(count!=2)
	{
		if(world_rank==0)		//check
		{
			srand(time(NULL));
			cur_pos= rand() % n;
	
			if(start_pos<cur_pos && cur_pos<=end_pos)
			{
				for(i=cur_pos;i<=end_pos;i++);
				cur_pos=(cur_pos+1)%n;
				MPI_Send(&cur_pos,1,MPI_INT,1,100,MPI_COMM_WORLD);
			}
		}
		else if(world_rank>0 && world_rank!=(world_size-1))
		{
			MPI_Status status;
			MPI_Recv(&cur_pos,1,MPI_INT,0,100,MPI_COMM_WORLD,&status);
			printf("\nProcess %d received",world_rank);
			if(start_pos<cur_pos && cur_pos<=end_pos)
			{
				for(i=cur_pos;i<=end_pos;i++);
				cur_pos=(cur_pos+1)%n;
				MPI_Send(&cur_pos,1,MPI_INT,2,101,MPI_COMM_WORLD);
			}
		}
		else
		{
			MPI_Status status;
			MPI_Recv(&cur_pos,1,MPI_INT,0,100,MPI_COMM_WORLD,&status);
			if(start_pos<cur_pos && cur_pos<=end_pos)
			{
				for(i=cur_pos;i<=end_pos;i++);
				cur_pos=(cur_pos+1)%n;
				count++;
			}
		}
		cur_pos=0;
	}
	MPI_Finalize();
	return 0;
}
