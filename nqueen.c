#include<stdio.h>
#include<mpi.h>
#include<math.h>

int board[10][10];		// if program gives wrong ans change size here.
int n,count=1;

void display()
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(board[i][j]==1)
				printf("Q ");
			else
				printf(". ");
		}
		printf("\n");
	}
}

int place(int row,int col)
{
	int i,j;
	for(i=0;i<row;i++)
	{
		if(board[i][col])
			return 0;
		for(j=0;j<n;j++)
			if(abs(row-i)==abs(col-j) && board[i][j]==1)
				return 0;
	}
	return 1;
}
void nqueen(int row)
{
	int col,j;
	if(row<n)
	{
		for(j=0;j<n;j++)
			board[row][j]=0;
		for(col=0;col<n;col++)
		{
			board[row][col-1]=0;
			if(place(row,col))
			{
				board[row][col]=1;
				nqueen(row+1);
			}
		}
	}
	else
	{
		printf("\nSolution %d\n",count++);
		display();
	}
}

int main(int argc, char **argv)
{
	int id,nop;
	int i,j;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nop);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	if(id==0)
	{
		printf("\nEnter no of Queens: ");
		scanf("%d",&n);
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				board[i][j]=0;
	}
	else
		nqueen(0);
	MPI_Finalize();
	return 0;
}

