
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
    tab=(int*)malloc(atoi(argv[1])*sizeof(int));
    if(tab==NULL){
        cout<<"Erreur : alocation mémoire échoué \n";
        MPI_Finalize();
        return 3;
        
    }
    else{
        for(int i = 0 ; i<n ; i++)tab[i]=pid;
        switch (pid)
        {
            case 1:
                MPI_Send(tab,n,MPI_INT,2,tag,MPI_COMM_WORLD);//envoyer à 2
                MPI_Recv(tab,n,MPI_INT,0,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// recevoir de 0
                break;
            case 2:
                MPI_Send(tab,n,MPI_INT,3,tag,MPI_COMM_WORLD);//envoyer à 3
                MPI_Recv(tab,n,MPI_INT,1,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// recevoir de 1
            break;
            case 3:
                MPI_Send(tab,n,MPI_INT,0,tag,MPI_COMM_WORLD);//envoyer à 0 
                MPI_Recv(tab,n,MPI_INT,2,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// recevoir de 2
            break;
            default:
                MPI_Send(tab,n, MPI_INT, 1, tag, MPI_COMM_WORLD);// envoyer à 1 
                MPI_Recv(tab,n,MPI_INT,3,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// recevoir de 3 
            break;
        }
        cout << "Bonjour ! Je suis le processus " 
       << pid << " sur " << nprocs <<" processus.[";
       for(int i=0; i<n; i++){
        cout<< tab[i];
        if(i<n-1)cout<<", ";
       }
       cout<<"]\n";

    }
 }
  MPI_Finalize();
  return 0;
}