
#include <iostream>
#include <mpi.h>

const int tag = 10;

using namespace std;

int main(int argc, char **argv)
{
  int pid, nprocs,n;
  int *tab;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);


  if(argc!=2)
  {
    cout<<"Usage: "<< argv[0] << " " << "<taille du tableau>"<<"\n";
    MPI_Finalize();
    return 1 ;
  }
  else
  {
    n=atoi(argv[1]);
    if(n<=0){
        cout<<"Erreur : taille invalide \n";
        MPI_Finalize();
        return 2 ;
    }
    tab=(int*)malloc(n*sizeof(int));
    if(tab==NULL){
        cout<<"Erreur : alocation mémoire échoué \n";
        free(tab);
        MPI_Finalize();
        return 3;
        
    }
    else{
        for(int i=0; i<n; i++){
            tab[i]=pid;
        }
        MPI_Sendrecv_replace(tab,n,MPI_INT,(pid+1)%nprocs,tag,(pid-1+nprocs)%nprocs,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        cout << "Bonjour ! Je suis le processus " 
       << pid << " sur " << nprocs <<" processus.[";
       for(int i=0; i<n; i++){
        cout<< tab[i];
        if(i<n-1)cout<<", ";
       }
       cout<<"]\n";
       free(tab);
    }
 }
  MPI_Finalize();
  return 0;
}