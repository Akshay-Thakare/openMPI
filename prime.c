#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc ,char **argv)
{
	int id,nop;
	int i,j,n,f=0,s;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nop);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	
	int m=999;

	if(id==0)
	{
		n = m/2;
		//n=9999;
		//printf("\nEnter range of nos to check for prime: ");
		//scanf("%d",&n);
		for(i=2;i<=n;i++)
		{
			f=0;
			for(j=2;j<=n/2;j++)
			{
				if(i%j==0)
				{
					f=1;
					break;
				}
			}
			if(f==0)
				printf("\n%d\t",i);
		}
	}

	else
	{
		n = m-n/2;
		for(i=2;i<=n;i++)
                {
                        f=0;
                        for(j=2;j<=n/2;j++)
                        {
                                if(i%j==0)
                                {
                                        f=1;
                                        break;
                                }
                        }
                        if(f==0)
                                printf("\n%d\t",i);
                }
	}

	MPI_Finalize();
	return 0;
}	
