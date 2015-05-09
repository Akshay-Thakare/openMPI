//By Akshay Thakare

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

float compute_avg(float *array, int num_elements)
{
	float sum = 0.f;
  	int i;
  	for (i = 0; i < num_elements; i++)
	{
    		sum += array[i];
  	}
  	return sum / num_elements;
}

int main(int argc, char ** argv)
{
	MPI_Init(&argc,&argv);

	srand(time(NULL));		//Initial seed

	int num_elements_per_proc = 100;	//hard coded
	int world_rank,world_size;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);

	float *rand_nums = NULL;
	if(world_rank==0)
	{
		rand_nums = (float *) malloc(sizeof(float) * num_elements_per_proc * world_size);
		int i;
		for(i=0;i<(num_elements_per_proc*world_size);i++)
			rand_nums[i] = (rand()/ (float)RAND_MAX);
	}

	float *sub_rand_nums = (float *)malloc(sizeof(float) * num_elements_per_proc);

	MPI_Scatter(rand_nums,num_elements_per_proc,MPI_FLOAT,sub_rand_nums,num_elements_per_proc,MPI_FLOAT,0,MPI_COMM_WORLD);

	float sub_avg = compute_avg(sub_rand_nums, num_elements_per_proc);

	float *sub_avgs = NULL;
  	if (world_rank == 0)
	{
    		sub_avgs = (float *)malloc(sizeof(float) * world_size);
	}

	MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

	if (world_rank == 0)
	{
    		float avg = compute_avg(sub_avgs, world_size);
    		printf("Avg of all elements is %f\n", avg);
    		float original_data_avg = compute_avg(rand_nums, num_elements_per_proc * world_size);
    		printf("Avg computed across original data is %f\n", original_data_avg);
  	}

  	if (world_rank == 0)
	{
    		free(rand_nums);
    		free(sub_avgs);
  	}

	free(sub_rand_nums);

  	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();
	return 0;
}
