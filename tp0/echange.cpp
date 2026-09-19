
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
  switch (pid)
  {
    case 1:
        MPI_Send(&a,1,MPI_INT,2,tag,MPI_COMM_WORLD);//envoyer à 2
        MPI_Recv(&a,1,MPI_INT,0,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// recevoir de 0
      break;
    case 2:
        MPI_Send(&a,1,MPI_INT,3,tag,MPI_COMM_WORLD);//envoyer à 3
        MPI_Recv(&a,1,MPI_INT,1,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// recevoir de 1
      break;
    case 3:
        MPI_Send(&a,1,MPI_INT,0,tag,MPI_COMM_WORLD);//envoyer à 0 
        MPI_Recv(&a,1,MPI_INT,2,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// recevoir de 2
      break;
    default:
        MPI_Send(&a,1, MPI_INT, 1, tag, MPI_COMM_WORLD);// envoyer à 1 
        MPI_Recv(&a,1,MPI_INT,3,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// recevoir de 3 
      break;
  }

  cout << "je suis " << pid << " et a=" << a << endl;

  MPI_Finalize();
  return 0;
}