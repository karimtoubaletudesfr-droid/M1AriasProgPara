
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
    int pid, nprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if (argc <2){
        cout << "Usage " << argv[0] << " message " << endl;
    }
    else{
    
    if(pid%2==0){
      cout << "Bonjour ! Je suis le processus " 
       << pid << " sur " << nprocs <<" processus.\n le message est : " << argv[1]
       << endl;
    }
    }

  MPI_Finalize();
  return 0;
}

