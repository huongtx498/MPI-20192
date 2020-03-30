// This program is to caculate PI using MPI
// The algorithm is based on integral representation of PI. If f(x)=4/(1+x^2), then PI is the intergral of f(x) from 0 to 1

#include <stdio.h>
#include <time.h>
#include <mpi.h>

#define N 1E6    //10^6
#define d 1E-6   //10^-6
#define d2 1E-12 //10^-12

int main(int argc, char *argv[])
{
    int rank, size, i;
    double pi = 0.0, result = 0.0, sum = 0.0, begin = 0.0, end = 0.0, x2;

    MPI_Init(&argc, &argv);

    //Get process ID
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Get processes Number
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Synchronize all processes and get the begin time
    MPI_Barrier(MPI_COMM_WORLD);
    begin = MPI_Wtime();

    //Each process will caculate a part of the sum, N/size in a part : Round roll bin
    for (i = rank; i < N; i += size)
    {
        x2 = d2 * i * i;
        result += 1.0 / (1.0 + x2);
    }

    //Sum up all results
    MPI_Reduce(&result, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    //Synchronize all processes and get the end time
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    //Caculate and print PI
    if (rank == 0)
    {
        pi = 4 * d * sum;
        printf("np=%2d;    Time=%fs;    PI=%lf\n", size, end - begin, pi);
    }

    MPI_Finalize();
    // Caculate PI in single process

    return 0;
}