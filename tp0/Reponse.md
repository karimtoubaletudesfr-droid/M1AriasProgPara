## Q1 — Signification de `-np`
### Question
Que représente l'argument `-np 4` dans la commande suivante ?
```bash
mpirun -np 4 ./hello
``` 
### Réponse 
Apres l'exuction du programme l'argument <code>-np 4</code> indique a MPI de lancer 4 processus MPI exécutant le programme <code>./hello</code><br>

### Obsérvation 
les processus auront alors des identifiants allant de 0 à 3 . <br>
l'ordre d'affichage des processus n'est pas forcément 0,1,2,3 car les processus s'exécutent en parallèle et leur ordre n'est pas déterministe . <br>
## Q2 — modification du programme
### Question
Modifiez le programme précédent pour que seuls les processus avec un identifiant pair affichent le message 'Bonjour'.
### Réponse 
```C++
if(pid%2==0){
      cout << "Bonjour ! Je suis le processus " 
       << pid << " sur " << nprocs
       << " processus." << endl;
   }
```   
## Q3 — modification du programme
### Question
Q3. Modifiez votre programme pour que tous les processus d'identifiant pair affiche un message donné en ligne de commande et exécutez le avec 

```bash
$ mpirun -np 4 ./hello "Jeudi 7 oct"
```

Comment s'effectue la diffusion des arguments en ligne de commande sur les différents processus ?
### Réponse 
Les arguments passés en ligne de commande sont accessibles aux
processus après l'initialisation de MPI avec :

```cpp
MPI_Init(&argc, &argv);
``` 
### Observation

Les différents processus MPI s'exécutent de manière concurrente.
Lorsqu'ils écrivent tous sur la sortie standard avec `cout`, l'ordre
des affichages n'est donc pas garanti.