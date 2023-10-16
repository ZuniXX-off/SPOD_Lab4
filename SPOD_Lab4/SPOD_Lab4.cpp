#include <iostream>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int processesCount, processRank, receivedRank, N, A = 0, sum;
    MPI_Comm newCommLocal;
    double start, end;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &processesCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    srand(time(NULL) + processRank * processesCount);

    if (processRank == 0) N = 1;
    else N = rand() % 2;

    if (N) A = rand();

    MPI_Comm_split(MPI_COMM_WORLD, N ? 1 : MPI_UNDEFINED, processRank, &newCommLocal);
    if (newCommLocal != MPI_COMM_NULL) {
        MPI_Allreduce(&A, &sum, 1, MPI_INT, MPI_SUM, newCommLocal);
        printf("Sum of all A's is %d (from process %d was A=%d)", sum, processRank, A);
    }

    MPI_Finalize();
}

