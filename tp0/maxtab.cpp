#include<iostream>
#include<mpi.h>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<cmath>
const int TAG_TAILLE=10;
const int TAG_DATA=11;
void repartion(int* &tab, int taille, int root){
    int pid, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int r_logic = (pid - root + nprocs) % nprocs;
    int taille_courante = taille;
    int nb_etapes= std::ceil(log((double)nprocs)/log(2.0));

    for(int i=0 ; i<nb_etapes; i++){
        int distance = std::pow(2,nb_etapes-1-i);

        if(r_logic % (2 * distance) == 0){

            int dest_logic = r_logic + distance;
            if(dest_logic < nprocs){
                int dest = (dest_logic + root) % nprocs;
                int taille_locale = taille / nprocs;
                int nb_blocs_a_envoyer = std::min(distance, nprocs - dest_logic);
                int taille_a_envoyer= nb_blocs_a_envoyer * taille_locale;
                MPI_Send(&taille_a_envoyer,1,MPI_INT,dest,TAG_TAILLE,MPI_COMM_WORLD);
                MPI_Send(tab + (taille_courante - taille_a_envoyer),taille_a_envoyer,MPI_INT,dest,TAG_DATA,MPI_COMM_WORLD);
                taille_courante -= taille_a_envoyer;
            }
        }
        else if(r_logic % (2 * distance) == distance){
            int source_logic = r_logic - distance;
            int source = (source_logic + root) % nprocs;
            int taille_a_recevoir;
            MPI_Recv(&taille_a_recevoir,1,MPI_INT,source,TAG_TAILLE,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            tab = (int*) malloc(taille_a_recevoir * sizeof(int));
            if(tab == NULL){
                std::cerr << "Erreur d'allocation mémoire.\n";
                MPI_Finalize();
                exit(4);
            }
            MPI_Recv(tab,taille_a_recevoir,MPI_INT,source,TAG_DATA,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            taille_courante = taille_a_recevoir;
        }
    }
}
int main(int argc,char** argv){
    int pid , nprocs,n;
    int *tab;
    int* maxtab;
    int root = 0;// juste en attendant de la valeur de root
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if(argc!=3){
        std::cerr<<"Usage : ./maxtab <taille du tableau> <valeur de root>\n";
        MPI_Finalize();
        return 1;
    }
    n=atoi(argv[1]);
    root=atoi(argv[2]);
    if (n % nprocs!=0){
        std::cerr<<"La taille du tableau dois être divisible sur le nombre de processus de l'exécution parallèle.\n";
        MPI_Finalize();
        return 2;
    } 
    if(n<=0){
        std::cerr<<"La taille du tableau doit être strictement positive. \n";
        MPI_Finalize();
        return 3;
    }
    if(root<0 || root>=nprocs){
        std::cerr<<"La valeur de root doit être comprise entre 0 et "<< nprocs-1 <<".\n";
        MPI_Finalize();
        return 6;
    }

    // jusque à la touts c'est bien passeé 
    if(pid==root){
    // le proc root 
    tab=(int*)malloc(n*sizeof(int));
        if(tab==NULL){
            std::cerr<<"Ereur d' allocation mémoire. ";
            MPI_Finalize();
            return 4;
        }
    srand(42);// pour avoir les mêmes valeurs à chaque exécution
    for(int i=0 ; i<n ; i++) tab[i]=rand();// je m'en fous de la plage de valeur 
    maxtab = (int*)malloc(nprocs*sizeof(int));
    if(maxtab==NULL){
        std::cerr<<"Ereur d' allocation mémoire. ";
        MPI_Finalize();
        return 4;
        
    }
}
    MPI_Barrier(MPI_COMM_WORLD);
    double debut = MPI_Wtime();
    repartion(tab,n,root);  
    int taille_locale = n / nprocs;
    int max_local = *std::max_element(tab, tab + taille_locale);
    if(pid==root){
        maxtab[0] = max_local;
        for(int i=1; i<nprocs; i++){
            MPI_Recv(&maxtab[i],1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
        int max_global = *std::max_element(maxtab, maxtab + nprocs);
        std::cout << "Le maximum global est : " << max_global << std::endl;
        free(maxtab);
    }else{
        MPI_Send(&max_local,1,MPI_INT,root,0,MPI_COMM_WORLD);
    }
    free(tab);  
    MPI_Barrier(MPI_COMM_WORLD);
    double fin = MPI_Wtime();    
    if(pid == root){
    std::cout << "Temps d'execution : "
              << fin - debut
              << " secondes\n";
    }
    MPI_Finalize();
    return 0;
    
    


    
}