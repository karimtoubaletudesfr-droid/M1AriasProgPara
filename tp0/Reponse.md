## Q1 — Signification de `-np`
<br>
### Question
Que représente l'argument `-np 4` dans la commande suivante ?

```bash
mpirun -np 4 ./hello
``` 
<br>
### Réponse 
Apres l'exuction du programme l'argument <code>-np 4</code> indique a MPI de lancer 4 processus MPI exécutant le programme <code>./hello</code><br>

### Obsérvation 
les processus auront alors des identifiants allant de 0 à 3 . <br>
l'ordre d'affichage des processus n'est pas forcément 0,1,2,3 car les processus s'exécutent en parallèle et leur ordre n'est pas déterministe . <br>