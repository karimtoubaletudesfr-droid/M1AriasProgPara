
#include <iostream>
#include <mpi.h>

const int tag = 10;

using namespace std;

int main(int argc, char **argv)
{
  int pid, nprocs;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  int a = pid;

  if (pid == 0)
    MPI_Send(&a, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
  if (pid == 1)
    MPI_Recv(&a, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  cout << "je suis " << pid << " et a=" << a << endl;

  MPI_Finalize();
  return 0;
}